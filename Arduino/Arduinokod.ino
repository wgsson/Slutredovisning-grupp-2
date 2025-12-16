#include <ESP8266WiFi.h>
#include <DHT.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoMqttClient.h>


#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


const char* ssid = "MDU_guest";
const char* password = "Frozen202512";

WiFiClient espClient;
MqttClient mqttClient(espClient);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// ---- NTP ----
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;  // Sverige UTC+1
const int daylightOffset_sec = 0;
const char broker[] = "test.mosquitto.org";
int port = 1883;
const char topic[] = "Gsson";
const char topic2[] = "Gsson/temp";
const char topic3[] = "Gsson/RH";

const long interval = 30000;
unsigned long previousMillis = 0;

int count = 0;

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Kunde inte hämta tid");
    return;
  }
  char buffer[64];
  strftime(buffer, sizeof(buffer), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(buffer);
}


void setup() {
  Serial.begin(115200);
  timeClient.begin();

  // Starta DHT
  dht.begin();
  delay(2000);

  // Anslut WiFi
  WiFi.begin(ssid, password);
  Serial.print("Ansluter till WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi ansluten!");

  // Starta NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("NTP tid konfigurerad!");

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code =");
    Serial.println(mqttClient.connectError());

    while (1)
    ;
  }
  Serial.println("You've connected to the MQTT broker!");
  Serial.println();

}
void loop() {
  mqttClient.poll();
  timeClient.update();
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Läs av DHT11
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Fel vid läsning av DHT11!");
      return;
    }
    
    // Skriv tid och sensorvärden
    printLocalTime();
    Serial.printf("Fukt: %.1f%%  Temp: %.1f°C\n", humidity, temperature);

    // Skicka data till MQTT
    mqttClient.beginMessage(topic3);
    mqttClient.print(humidity);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic2);
    mqttClient.print(temperature);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic);
    mqttClient.printf("Tid: ");
    mqttClient.print(timeClient.getFormattedTime());
    mqttClient.endMessage();
  }
}

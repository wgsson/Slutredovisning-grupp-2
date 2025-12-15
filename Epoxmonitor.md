# EpoxMonitor - step by step guide

## Projektöversikt

Projektet undersöker hur luftfuktighet påverkar arbete med epoxi i hantverks- och industrimiljöer. Genom kontinuerlig mätning av relativ luftfuktighet (RH) skapas ett enkelt beslutsstöd för när epoxi kan appliceras och när nästa lager kan läggas.

## Bill of Materials
### Material
* Dator
* Plusivokit
  - DHT11 - RH-sensor
  - ESP8266 – mikrokontroller med WiFi
  - Batteri + DC-sladd
  - Breadboard
  - Kopplingskablar
<img width="205" height="182" alt="image" src="https://github.com/user-attachments/assets/cf9015f9-0a62-4e25-9dac-1f5e90f93b6b" />

### Program
* Arduino IDE 

* Mosquitto Eclipse - MQTT för datakommunikation 

* Visual Studio Code - visualisering av data 

<img width="50" height="50" alt="image" src="https://github.com/user-attachments/assets/15c86fdf-2ee7-46ad-aba9-5888d537b975" /> <img width="80" height="80" alt="image" src="https://github.com/user-attachments/assets/d02ea206-3b95-417e-9c20-4f8fe3a27cc7" /> <img width="80" height="600" alt="image" src="https://github.com/user-attachments/assets/02b8c254-986d-4f0f-ba5d-9cc45071f9b3" />


---

## Användare och kontext

**Användare:** Yrkeshantverkare som arbetar med epoxi (t.ex. golvläggare).

**Kontext:** Industrilokaler och arbetsmiljöer med tidspress, varierande klimat och begränsad möjlighet till manuell mätning.

**Behov:** Snabb och tydlig information om luftfuktighet utan att behöva tolka rådata.

---

## Sensor (DHT11) och konstruktion (ESP8266)
<img width="181" height="160" alt="image" src="https://github.com/user-attachments/assets/03f903f6-3a82-414c-af93-8d2b28bf288d" /> <img width="146" height="244" alt="image" src="https://github.com/user-attachments/assets/97cb8c23-f889-4a9e-b3af-e6768a791448" />


**Koppling:**

* VCC → 3.3V
* GND → GND
* DATA → D4

<img width="272" height="390" alt="image" src="https://github.com/user-attachments/assets/f566f9ec-bb10-43c1-a04c-4eb342e4d932" />



Tips: ESP8266-guide ligger i repot!

---

## Steg 1 – Installera utvecklingsmiljö

1. Ladda ner och installera Arduino IDE
2. Lägg till ESP8266 via Board Manager
3. Välj rätt board (ESP8266) och port
---

## Steg 2 – Installera bibliotek

Följande bibliotek används:

* DHT Sensor Library – för att läsa luftfuktighet
* Adafruit Unified Sensor – beroende för DHT
* ArduinoMqttClient – MQTT-kommunikation
* WiFiUdp.h - WiFi
* PubSubClient.h - 
* NTPClient – tidsstämplar

## Steg 3 – Programmera sensorn

1. Koden "Arduinokod.ino" placeras i Arduino IDE på tomt canvas.
2. Koppla in breadboard med DHT11 och ESP8266 via USB-c till din dator
3. Välj rätt "Port" under "Tools"
4. Tryck "Upload"
5. Öppna Tools och tryck på Serial Monitor
6. Säkerställ att mikrokontrollen är ansluten till Wi-fi
7. Data över luftfuktigheten från DHT11 bör synas och uppdateras kontinuerligt

Följande kommer alltså att ske:

* Initierar WiFi-anslutning
* Läser luftfuktighet från DHT11
* Hämtar aktuell tid via NTP
* Skickar data till MQTT-broker (test.mosquitto.org) 

Mätning sker varannan sekund.

---

## Steg 4- Ladda ned Mosquitto (MQTT-applikation)
Ladda ned Mosquitto på följande länk: ​ https://mosquitto.org/download/

Öppna kommandotolk och skriv in följande för att starta applikationen lokalt: 

->**cd C:"Program Files\mosquitto**
-> **mosquitto.exe** 
-> **mosquitto.exe -v**

Följande för att starta en publisher:
->**mosquitto_pub.exe -h test.mosquitto.org -p 1883 -t Gsson/RH**

Följande för att starta en subscriber: 
-> **mosquitto_sub.exe -h test.mosquitto.org -p 1883 -t Gsson/RH**
I detta fönster bör nu data skickad från sensorn dyka upp. 

<img width="464" height="172" alt="image" src="https://github.com/user-attachments/assets/e3a46d63-448d-453a-937b-eec51f5721a0" />

Sensorn agerar publisher och publicerar data (RH) genom topic Gsson/RH via en MQTT Broker (test.mosquitto.org) och skickar vidare data till en subscriber, vår hemsida (VSC), som prennumererar på samma topic. Subscriber kan då visualisera data och göra den enkel att tolka.

---

## Steg 5 VSC
Ladda ned Visual Studio Code på följande länk: https://code.visualstudio.com/Download
Skapa följande dokument i VSC och klistra in bifogad kod:
- JavaScript (app.js)
- HTML (index.html)
- CSS (style.css)

  Klicka på "Go Live" och säkerställ att Epoxmonitor fungerar.

<img width="260" height="379" alt="image" src="https://github.com/user-attachments/assets/5da648c3-3762-4604-b10d-adea24fe55d3" />


Gränssnittet visar:

* Aktuell luftfuktighet (RH nu)
* Grön zon för optimal RH
* 24-timmars historik i linjediagram

Visualiseringen gör det möjligt att se både nuvarande värde och trender över tid.

---

## Designanpassning

* Endast luftfuktighet visas för att minska kognitiv belastning
* Grön zon ger direkt normativ vägledning
* Mobilanpassat gränssnitt för användning på arbetsplats

---

## Förväntad kunskap och nytta

Systemet ger användaren kunskap om:

* När luftfuktigheten är lämplig för applicering av epoxi
* Om klimatet varit stabilt under de senaste 24 timmarna

Detta minskar risken för felaktig härdning och materialskador.

## Kapsulering

## Presentation av slutresultat


# EpoxMonitor - step by step guide

## Projektöversikt

Projektet undersöker hur luftfuktighet påverkar arbete med epoxi i hantverks- och industrimiljöer. Genom kontinuerlig mätning av relativ luftfuktighet (RH) skapas ett enkelt beslutsstöd för när epoxi kan appliceras och när nästa lager kan läggas.

## Bill of Materials
### Material

| Namn | Antal | Beskrivning |
|------|------- |-----|
| Dator |1|Används för programmering och datahantering |
| Plusivokit |1| Innehåller grundläggande elektronikkomponenter |
| DHT11 |1|Sensor för temperatur och relativ luftfuktighet |
| ESP8266 |1| Mikrokontroller med inbyggt WiFi |
| Batteri |1| Strömförsörjning |
| DC-sladd |1| Anslutning för ström |
| Breadboard |1| Kopplingsdäck för prototypkoppling |
| Kopplingskablar |1| Förbindelser mellan komponenter |

### Program

| Namn | Beskrivning |
|------|-------------|
| Arduino IDE | Programmering av mikrokontroller |
| Mosquitto Eclipse | MQTT-broker för datakommunikation |
| Visual Studio Code | Visualisering och hantering av data |

---

## Steg 1- Sensor (DHT11) och konstruktion (ESP8266)

**Koppling:**

* VCC → 3.3V
* GND → GND
* DATA → D4

<img width="272" height="390" alt="image" src="https://github.com/user-attachments/assets/f566f9ec-bb10-43c1-a04c-4eb342e4d932" />

*Tips: ESP8266-guide ligger i repot!*

---

## Steg 1 – Installera utvecklingsmiljö

1. Ladda ner och installera Arduino IDE
2. Lägg till ESP8266 via Board Manager
3. Välj rätt board (ESP8266) och port
4. Ställ in aktuellt:
   - WiFi SSID
   - WiFi lösenord
   - Korrekt IP-adress
   - Korrekt port
   
---

## Steg 2 – Installera bibliotek

Följande bibliotek används:

* DHT Sensor Library – för att läsa luftfuktighet
* Adafruit Unified Sensor – beroende för DHT
* ArduinoMqttClient – MQTT-kommunikation
* WiFiUdp.h - WiFi
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
## Steg 4 – Ladda ned och använd Mosquitto (MQTT)

### Installera Mosquitto
Ladda ned Mosquitto från följande länk:  
https://mosquitto.org/download/

### Starta Mosquitto lokalt
Öppna Kommandotolken och kör följande kommandon för att hamna i rätt mapp och för att starta Mosquitto:

1. ```cd C:\Program Files\mosquitto```
2. ```mosquitto.exe```

### Starta en publisher
``mosquitto_pub.exe -h test.mosquitto.org -p 1883 -t Gsson/RH``

### Starta en subscriber på samma topic
``mosquitto_sub.exe -h test.mosquitto.org -p 1883 -t Gsson/RH``

I detta fönster ska nu data som skickas från sensorn visas. 
<img width="471" height="196" alt="image" src="https://github.com/user-attachments/assets/7efef7ba-b4aa-4e9e-b798-bf8a7003ce95" />


### Förklaring
Sensorn fungerar som publisher och publicerar mätdata (RH) till topic Gsson/RH via en MQTT-broker (test.mosquitto.org).
Vår webbapplikation fungerar som subscriber och prenumererar på samma topic. Den mottagna datan kan därefter visualiseras och presenteras på ett lättförståeligt sätt.

---

## Steg 5 VSC
Ladda ned Visual Studio Code på följande länk: https://code.visualstudio.com/Download

Skapa följande dokument i VSC och klistra in bifogad kod:
- JavaScript (app.js)
- HTML (index.html)
- CSS (style.css)

  Klicka på "Go Live" och säkerställ att Epoxmonitor fungerar.

<img width="260" height="379" alt="image" src="https://github.com/user-attachments/assets/5da648c3-3762-4604-b10d-adea24fe55d3" />

## Kapsulering
Bild på kapsulering här 

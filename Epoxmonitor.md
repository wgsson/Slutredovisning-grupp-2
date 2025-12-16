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

## Steg 2 – Installera utvecklingsmiljö

1. Ladda ner och installera Arduino IDE på följande länk:
   
   https://docs.arduino.cc/software/ide/#ide-v2

3. Lägg till ESP8266 via Board Manager
4. Välj rätt board (ESP8266) och port
5. Ställ in aktuellt:
   - WiFi SSID
   - WiFi lösenord
   - Korrekt IP-adress
   - Korrekt port
   
---

## Steg 3 – Installera bibliotek i Arduino IDE

Följande bibliotek används:

* DHT Sensor Library – för att läsa luftfuktighet
* Adafruit Unified Sensor – beroende för DHT
* ArduinoMqttClient – MQTT-kommunikation
* WiFiUdp.h - WiFi
* NTPClient – tidsstämplar

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

### Förklaring
Sensorn fungerar som publisher och publicerar mätdata (RH) till topic Gsson/RH via en MQTT-broker (test.mosquitto.org).
Vår webbapplikation fungerar som subscriber och prenumererar på samma topic. Den mottagna datan kan därefter visualiseras och presenteras på ett lättförståeligt sätt.

---

## Steg 5 – Programmera sensorn i Arduino IDE

1. Koden "Arduinokod.ino" placeras i Arduino IDE på tomt canvas.
2. Koppla in breadboard med DHT11 och ESP8266 via USB-c till din dator
3. Välj rätt "Port" under "Tools"
4. Tryck "Upload"
5. Öppna Tools och tryck på Serial Monitor
6. Säkerställ att mikrokontrollen är ansluten till Wi-fi
7. Data över luftfuktigheten från DHT11 bör synas och uppdateras kontinuerligt

BYT UT BILD TILL SERIAL MONITOR
    
<img width="471" height="196" alt="image" src="https://github.com/user-attachments/assets/7efef7ba-b4aa-4e9e-b798-bf8a7003ce95" />

Mätning sker varannan sekund.

---

## Steg 6 VSC
Ladda ned Visual Studio Code på följande länk: https://code.visualstudio.com/Download

Skapa följande dokument i VSC och klistra in bifogad kod:
- JavaScript (app.js)
- HTML (index.html)
- CSS (style.css)

  Klicka på "Go Live" och säkerställ att Epoxmonitor fungerar.
  
  <img width="320" height="558" alt="Skärmbild 2025-12-15 093511" src="https://github.com/user-attachments/assets/362dc2b4-ed9e-469e-9559-ee294901ae73" />



## Kapsulering
Bild på kapsulering här 

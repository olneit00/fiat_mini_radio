# KiCad-Trägerplatine – Prüfstatus v0.1

[PCB-Platzierungsentwurf](fiat_mini_radio_carrier_v01.kicad_pcb) (65 × 65 mm) enthält 2 × 22 ESP32-Sockelkontakte, 1 × 6 PCM5102A-Sockelkontakte sowie **16 beschriftete Lötaugen** (Encoder 1: 4; Encoder 2: 4; ST7789: 8).

**ACHTUNG: NICHT FERTIGEN.** Die PCB-Datei ist eine **unverdrahtete Platzierungsskizze**. GPIO-Netze sind seit Commit 6ca56ff den bekannten ESP32-, DAC-, Encoder- und Display-Steuerpads zugewiesen. **Es sind noch keine Leiterbahnen geroutet.** Offene Stromversorgungs- und SPI-Signale bleiben absichtlich ohne Netz. Die Pin-Nummerierung des ESP32-Footprints ist nur eine Platzhalterzählung, **keine** bestätigte Zuordnung zu GPIO-Labels. Eine DRC-/ERC-Prüfung wurde nicht durchgeführt.

## Bekannte Prüfungen / Risiken
1. HW-678 V0.0.0: 22 Pins pro Reihe, gemessener Reihenabstand 24,5 mm, Pinpitch 2,54 mm vorläufig. **1:1-Passprobe zwingend**.
2. Die Platzierung von Display-Lötaugen und DAC benötigt eine Kollisionsprüfung mit den **realen Modulabmessungen**, Stiftleisten und Kabeln; 65 × 65 mm ist eine Zielgröße, keine geprüfte Passung.
3. Der DAC-Sockel hat die Reihenfolge VIN, GND, LCK, DIN, BCK, SCK; SCK=GND, BCK=GPIO4, DIN=GPIO5, LCK=GPIO6. **VIN-Spannung noch zu prüfen**.
4. Encoder 1: GPIO47,21,7; Encoder 2: GPIO39,40,41. Common=GND.
5. ST7789: CS=GPIO17, DC=GPIO16, RST=GPIO15; SPI-SCLK und SPI-MOSI aus der tatsächlich verwendeten SPI2/HSPI-Konfiguration ermitteln. VCC/BLK nach Modul prüfen.
6. Die PCM5102A-Analogausgänge werden über die **bereits vorhandene Klinkenbuchse** verwendet; keine zusätzlichen Audio-Lötpunkte vorgesehen.
7. Keine aktiven Komponenten, kein Verstärker, keine zusätzliche USB-C-Buchse oder 12-V-Versorgung.

## Weiteres Vorgehen
- Sockel-Pinzuordnung anhand des Nutzerfotos und der Board-Beschriftungen eindeutig festlegen.
- Modul- und Lötaugenkollisionen beseitigen.
- KiCad-Netze zuweisen, routen, 1:1-Ansicht und DRC prüfen.
- Erst danach Fertigungsdaten erzeugen.

## Elektrischer Zwischenstand (08.11.2026)
- DAC: LCK=GPIO6, DIN=GPIO5, BCK=GPIO4, SCK=GND; VIN vorläufig offen.
- Encoder links: A=GPIO47, B=GPIO21, SW=GPIO7, GND=GND.
- Encoder rechts: A=GPIO39, B=GPIO40, SW=GPIO41, GND=GND.
- Display: CS=GPIO17, DC=GPIO16, RST=GPIO15, GND=GND; SCL/SDA/VCC/BLK vorläufig offen.
- DAC-Buchsenleiste ist entlang der kurzen DAC-Seite orientiert (6 Kontakte quer zur Modullängsachse).
- **Nicht routen oder fertigen, bevor die ESP32-Pinbeschriftungen mit dem physischen HW-678 und SPI2/HSPI mit der Firmware abgeglichen sind.**

## Massefläche – Zwischenstand
- Eine **GND-Kupferzone auf B.Cu** wurde angelegt (0,5 mm Abstand zum Platinenrand, 0,3 mm Clearance). Die Zone ist in der PCB-Datei definiert, aber **noch nicht gefüllt** (kein KiCad-DRC/Zone-Fill ausgeführt).
- Signal-Leiterbahnen sind weiterhin **nicht geroutet**. Die Platine darf nicht gefertigt werden.
- Die Anschlüsse aus der anderen Agentenprüfung (GPIO18 SPI-SCLK, GPIO14 SPI-MOSI; 3V3 für Display/DAC/BLK) sind als Netze zugewiesen, aber die reale HW-678-Pinbelegung und mechanische Passung müssen unabhängig geprüft werden.

## Routing-Versuch (08.11.2026)
- **434 Segmente** mit 0,25 mm Breite auf B.Cu erzeugt und in die PCB-Datei geschrieben (Commit bd8fe4d).
- Die Verbindungsketten von 3V3, GPIO14, GPIO15, GPIO18, GPIO39, GPIO4, GPIO5, GPIO6 und GPIO7 wurden algorithmisch geführt. **Nicht DRC-geprüft; diese Verbindungen sind NICHT als elektrisch korrekt bestätigt.**
- Nicht geroutet: **GPIO16, GPIO17, GPIO21, GPIO40, GPIO41, GPIO47**. Diese sechs Luftlinien bleiben offen.
- Der GND-Zonenfüllstand ist weiterhin nicht berechnet. Einlagige Signalführung auf B.Cu ist nur ein Zwischenschritt; ggf. F.Cu + Vias nötig.
- **Keine Gerber oder Produktionsfreigabe** bis KiCad-DRC, Netz-Konnektivitätsprüfung und mechanische Passprobe erfolgreich abgeschlossen sind.

## F.Cu-Routingversuch
- Vier zuvor offene Netze auf F.Cu mit 0,25-mm-Segmenten ergänzt: GPIO47, GPIO21, GPIO17, GPIO16 (Commit 9c2c126).
- **GPIO40 und GPIO41 sind weiterhin unverbunden.** Die automatische Wegsuche fand bei der derzeitigen Reihenfolge und Belegung keine kollisionsfreie Route auf F.Cu.
- GND-Kupferzone ist nicht gefüllt; vollständige DRC und reale Modul-Passprobe fehlen weiterhin. Außerdem sind die 0,25-mm-Leitungen noch nicht auf Abstände, Kurzschlüsse oder Fertigbarkeit geprüft.
- Kein Produktionsstatus, keine Gerberfreigabe.

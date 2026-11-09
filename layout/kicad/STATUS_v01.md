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

## 70 × 65 mm, M3-Befestigung und restliches Routing (08.11.2026)
- Außenkontur **70 × 65 mm**, B.Cu-Massezone entsprechend erweitert.
- Vier **nicht metallisierte 3,2-mm-Bohrungen** bei (4,4), (66,4), (4,61), (66,61) mm ergänzt (Commit 50dacfd). Mechanische Bauteilfreiräume und Kupferabstände müssen noch per DRC bestätigt werden.
- **GPIO40 und GPIO41** algorithmisch über F.Cu/B.Cu ergänzt (Commit eb799d9): 459 weitere 0,25-mm-Segmente und **1 Via (0,8/0,4 mm)**. GPIO40 ohne Via; GPIO41 mit einem Via. Alle ursprünglich offenen GPIO-Verbindungen haben damit einen Entwurfs-Routingpfad.
- **WICHTIG:** Dies ist kein bestandener KiCad-DRC. Die automatischen Routen sind noch nicht auf tatsächliche Kupferkurzschlüsse, Abstände, Leiterbahn-Pad-Anschlüsse oder unverbundene Netze geprüft; Massezone nicht gefüllt. Keine Fertigungsfreigabe.

## Statische Plausibilitätsprüfung (08.11.2026)
- PCB-Text enthält **1206 Leiterbahnsegmente**, davon 736 auf F.Cu und 470 auf B.Cu, sowie **1 Via**.
- **66 elektrische Kontaktpads** vorhanden (44 ESP32, 6 DAC, 8 Display, 8 Encoder); drei davon absichtlich ohne Netz: ESP32-RST, TX, RX. Hinzu kommen vier nichtmetallisierte Montagebohrungen.
- Abstandstest der vorhandenen Leiterbahnen zu den vier M3-Bohrungen: keine Verletzung des groben Grenzwerts 2,025 mm vom Bohrmittelpunkt gefunden; Kupferzonenfüllung und Bauteil-Courtyards weiterhin nicht geprüft.
- **KRITISCHER BEFUND:** Eine statische geometrische Kontrolle meldet auf F.Cu einen Abstand von nur **0,25 mm** zwischen einer GPIO21-Leiterbahn (Netz 18, Segment x=36,75 mm) und GPIO40 (Netz 26, bei y=23,5 mm). Bei 0,25-mm-Leiterbahnen bleibt nur 0,00 mm Kupferabstand zwischen diesen Segmenten. Der Entwurf ist **nicht fertigungsreif**. Vor Gerberexport muss die Route korrigiert und mit KiCad DRC verifiziert werden.
- Keine DRC- oder ERC-Prüfung mit KiCad möglich in der aktuellen Laufzeitumgebung. Eine formale Prüfung darf nicht als bestanden dargestellt werden.


## V02: Encoder J5 näher am ESP32 und neu geroutet (09.11.2026)
- Separate Datei: `fiat_mini_radio_carrier_v02_encoder_near_esp_DRAFT.kicad_pcb` (V01 bleibt unverändert).
- J5 bei (40,22) mm; Lötaugenreihenfolge **SW / B / A / GND** statt A / B / SW / GND, weil die GPIO-Reihenfolge am ESP32 umgekehrt ist.
- J5 Pad 1 SW = GPIO41 (40,22); Pad 2 B = GPIO40 (40,25.5); Pad 3 A = GPIO39 (40,29); Pad 4 GND = GND (40,32.5).
- Drei kurze B.Cu-Segmente: GPIO41 (35.25,20.74)→(40,22); GPIO40 (35.25,23.28)→(40,25.5); GPIO39 (35.25,25.82)→(40,29).
- Alte langen Routingsegmente der Netze 24/26/27 und das alte Via GPIO41 aus V02 entfernt. Der zuvor dokumentierte F.Cu-Kurzschluss GPIO21/GPIO40 entfällt dadurch in V02.
- Ein Segment-Abstandscheck auf B.Cu gegen vorhandene **Leiterbahnsegmente** zeigte keine Kollisionen in diesem Bereich; **keine vollständige Pad-/Via-/Zonen-DRC**. Netzanschluss der übrigen Bauteile und GND-Zone nicht bestätigt. **Keine Gerberfreigabe**.

## V02: zusätzliche Prüfung der neuen Encoder-Verbindungen (09.11.2026)
- Die V02-Datei enthält nach dem Umrouten 725 Leiterbahnsegmente (einschließlich der drei neuen B.Cu-Segmente).
- GPIO41: J2 Pad 7 (35,25 / 20,74) → J5 Pad 1 (40 / 22), B.Cu.
- GPIO40: J2 Pad 8 (35,25 / 23,28) → J5 Pad 2 (40 / 25,5), B.Cu.
- GPIO39: J2 Pad 9 (35,25 / 25,82) → J5 Pad 3 (40 / 29), B.Cu.
- Gegen die anderen vorhandenen B.Cu-Leiterbahnsegmente wurden keine unmittelbaren geometrischen Kollisionen der drei neuen Verbindungen gefunden. Die drei neuen Segmente sind auch untereinander getrennt.
- **Achtung:** Die GND-Zone ist zwar im Dateitext definiert, aber noch nicht mit Kupfer gefüllt; insbesondere J5 Pad 4 (40 / 32,5) hat damit noch keine nachgewiesene Masseverbindung. Die Prüfung umfasst **nicht** Pads, Footprint-Courtyards, Via-Abstände, die vollständige Connectivity oder einen offiziellen KiCad-DRC. Keine Gerber-/Fertigungsfreigabe.

## V02: Lötpad-Abstände am versetzten J5 (09.11.2026)
- Die vier J5-Lötaugen liegen bei (40,22), (40,25.5), (40,29), (40,32.5) mm.
- Statische Geometrieprüfung gegen 70 aus dem PCB-Text ausgelesene Through-Hole-/Montagepads: **kein fremdes Pad mit weniger als 0,30 mm Kupferabstand zu einem J5-Pad** gefunden. Für die drei neuen B.Cu-Segmente GPIO39/40/41: **kein fremdes elektrisches Through-Hole-Pad mit weniger als 0,20 mm rechnerischem Kupferabstand** gefunden. Nicht geprüft: Footprint-Courtyards, Pad-Formen abweichend vom angenommenen Kreis, Massezonenfüllung, vollständiger DRC.
- Das lokale Routing ist geometrisch plausibel, aber **nicht offiziell DRC-validiert**. GND-Zone ist nicht gefüllt. Keine Gerberfreigabe.

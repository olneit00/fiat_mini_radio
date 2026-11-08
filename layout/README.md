# PCB-Layout – DRAFT v0.4: rein passive Trägerplatine

**Ziel:** So einfach wie möglich. Die Platine enthält **keine aktiven Komponenten** und keine eigenen Widerstände, Spannungsregler, USB-Buchsen oder Taster. **Noch nicht fertigungsreif.**

## Bestückung
1. Zwei **22-polige Buchsenleisten (2 × 22 Kontakte)** als Sockel für das **vorhandene ESP32-S3-DevKitC-1 N16R8** (USB-C sitzt bereits auf dem DevKit).
2. Eine **6-polige Buchsenleiste** für das vorhandene **PCM5100-DAC-Modul** (Pinfolge VIN, GND, LCK, DIN, BCK, SCK).
3. **Durchkontaktierte, beschriftete Lötaugen** für Encoder 1 (A, B, SW, GND).
4. **Durchkontaktierte, beschriftete Lötaugen** für Encoder 2 (A, B, SW, GND).
5. **Durchkontaktierte, beschriftete Lötaugen** für das ST7789-Display (VCC, GND, SCLK, MOSI, CS, DC, RST, BLK soweit das konkrete Modul sie benötigt).

Keine Verstärkerschaltung. Audioausgänge bleiben zunächst am vorhandenen DAC-Modul, kein separater Line-Out-Stecker auf der Trägerplatine.

## Stromversorgung
- Ein einziges USB-C-Kabel direkt in die Buchse des ESP32-DevKits.
- 3V3 und GND vom DevKit werden passiv an die benötigten Lötaugen verteilt.
- **DAC-VIN ist bis zur Prüfung der zulässigen Versorgungsspannung des konkreten Moduls noch offen.**
- Keine zusätzliche Gehäusebuchse und kein 12-V-Eingang.

## Signalbelegung aus aktueller Firmware
| Verbraucher | Signal | GPIO |
|---|---|---|
| PCM5100 | LCK | 6 |
| PCM5100 | DIN | 5 |
| PCM5100 | BCK | 4 |
| PCM5100 | SCK | GND (vom Nutzer bestätigt) |
| Encoder 1 | A, B, SW | 47, 21, 7 |
| Encoder 2 | A, B, SW | 39, 40, 41 |
| ST7789 | CS, DC, RST | 17, 16, 15 |
| ST7789 | SCLK, MOSI | noch mit tatsächlich genutztem SPI2/HSPI-Core abgleichen |

## Dateien
- [schaltplan_v02.md](schaltplan_v02.md) – ältere Architekturübersicht, teils überholt; **diese README v0.4 hat Vorrang**
- [pcm5100_module.md](pcm5100_module.md) – DAC-Modul und Pinfolge
- [pin_mapping.csv](pin_mapping.csv) – Firmwarebelegung
- [schaltplan_netzliste.csv](schaltplan_netzliste.csv) – vorläufig, nicht vollständig
- [bom.csv](bom.csv) – ältere Stückliste, für v0.4 zu reduzieren
- [kicad_pin_assignment.csv](kicad_pin_assignment.csv) – ältere KiCad-Vorbereitung

## Vor dem Layout zwingend abgleichen
- Stiftleistenanzahl **22 je Seite (vom Nutzer bestätigt)**. Pitch voraussichtlich 2,54 mm; Reihenabstand und Orientierung des vorhandenen ESP32-S3-DevKits noch prüfen.
- Stiftabstand, Maße und Einsteckrichtung des PCM5100-Moduls.
- Stromversorgung und BLK-Beschaltung des Displaymoduls.
- Die **tatsächlichen** SPI-SCLK/MOSI-Pins der laufenden Firmware.
- Lage der Kabel-Lötaugen im CAD-Gehäuse und Antennenfreiraum des ESP32.

**Nächster Schritt:** Maßzeichnung/Footprints der beiden Steckmodule festlegen, anschließend passive KiCad-Schaltplan- und PCB-Dateien erzeugen.

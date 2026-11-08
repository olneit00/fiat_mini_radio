# Schaltplanentwurf v0.2 – USB-C, ohne Verstärker

**Status:** Architektur und verbindliche Netze für einen KiCad-Schaltplan. **Dies ist noch keine native `.kicad_sch`-Datei und nicht fertigungsreif.**

## Blockschaltbild

```text
 USB-C (USB 2.0, 5 V)
  | VBUS ---- Schutz/Filter ---- +5V --------------------> ggf. DAC-Modul
  |                             |
  |                             +-- 3V3-Regler --> ESP32-S3-WROOM-1
  |                                              +--> Display (wenn 3V3-Modul)
  |                                              +--> DAC (wenn 3V3-Modul)
  | GND -----------------------------------------------> gemeinsame Masse
  | D+/D- ----------------------------> ESP32-S3 native USB (GPIO20/GPIO19)
  | CC1 -- 5k1 --> GND; CC2 -- 5k1 --> GND

 ESP32-S3
  GPIO17/16/15 -----------------------> ST7789 CS/DC/RST
  SPI2 SCLK/MOSI (noch offen) --------> ST7789 CLK/DIN
  GPIO5/4/6 -------------------------> PCM5100 DIN/BCK/LRCK
  GPIO47/21/7 -----------------------> Encoder 1 A/B/Taster
  GPIO39/40/41 ----------------------> Encoder 2 A/B/Taster
  PCM5100 LOUT/ROUT/GND -------------> Line-Out-Anschluss
```

## USB-C und Stromversorgung
- USB-C **USB-2.0-Device/Sink**: CC1 und CC2 jeweils mit eigenem 5,1-kΩ-Pulldown nach GND; A6/B6 (D+) zusammenführen, A7/B7 (D−) zusammenführen. USB-ESD-Schutz nahe Buchse vorsehen.
- ESP32-S3 **native USB**: GPIO20 = USB D+, GPIO19 = USB D− (anhand des finalen Moduldatenblatts und Layouts nochmals prüfen).
- 3,3-V-LDO mit ausreichender Reserve für WLAN-Spitzenlast, Display und DAC auswählen. Ein konkreter Reglertyp ist noch **nicht** freigegeben.
- Kondensatoren, Reglerstabilität, Eingangsschutz und ggf. USB-Strombudget nach Datenblatt auslegen. Keine direkte Verbindung zur 12-V-Fahrzeugversorgung.
- ESP32 EN: Pull-up nach 3V3, RC-Power-on-Reset gemäß Espressif-Referenzdesign und RESET-Taster nach GND.
- GPIO0: Boot-Pull-up und BOOT-Taster nach GND gemäß Espressif-Referenzdesign. GPIO0 während Normalbetrieb nicht durch weitere Hardware festhalten.
- Modulstrapping, interne PSRAM-/Flashbelegung und unbenutzte Pins anhand der **exakten** S3-WROOM-Variante prüfen.

## Display (ST7789, SPI)
| Signal | ESP32 GPIO | Status |
| --- | --- | --- |
| CS | 17 | Firmware bestätigt |
| DC | 16 | Firmware bestätigt |
| RST | 15 | Firmware bestätigt |
| SCLK | **offen** | `SPI2(HSPI)`-Pinbelegung im tatsächlich verwendeten Core prüfen |
| MOSI | **offen** | dito |
| BLK | **offen** | Versorgung/Strombedarf des konkreten Moduls prüfen |
| VCC/GND | **offen** | Modulversion prüfen |

**Achtung:** Die alte Prototyp-Tabelle nennt CS=15 und RST=17; die aktuelle Firmware vertauscht diese Signale. Vor Layout beide Stände abgleichen.

## I²S-DAC (PCM5100)
| Signal | ESP32 GPIO | Status |
| --- | --- | --- |
| DIN | 5 | Firmware bestätigt |
| BCK | 4 | Firmware bestätigt |
| LRCK/LCK | 6 | Firmware bestätigt |
| LOUT/ROUT/GND | Line-Out-Stecker | Vorgesehen |
| Versorgung, MCLK/SCK, XSMT, FMT, FLT, DEMP | **offen** | Hängt von tatsächlichem PCM5100-Modul ab |

Der DAC liefert **Line-Level**; keine Lautsprecher direkt anschließen. Ein Verstärker ist in dieser Revision nicht enthalten.

## Drehencoder
- Encoder 1: A=GPIO47, B=GPIO21, SW=GPIO7
- Encoder 2: A=GPIO39, B=GPIO40, SW=GPIO41
- Common-Pins an GND, Firmware-Pull-ups auf ihre tatsächliche Konfiguration prüfen.
- Mechanische Bauform, Pinreihenfolge und Footprints vor Schaltplanfinalisierung festlegen.

## PCB-Aufbau
- ESP32-Antennenfreiraum nach Modul-Datenblatt; Metall-Chromrahmen berücksichtigen.
- USB-C-Buchse an zugänglicher Gehäusekante; USB-Datenpaar kurz und zusammenhängende Referenzmasse.
- Audio-Analogsignale getrennt von USB/SPI und Schaltregler halten.
- Mechanik zuerst: Gehäuse, Schraubdome, Encoderachsen, Displayöffnung, USB-Ausschnitt.
- Erst nach ERC/DRC und Abgleich mit realen Modulen Gerber erzeugen.

## Nächste Entscheidung
Das genaue ST7789-Displaymodul und das PCM5100-DAC-Modul (Fotos/Links oder Pinbeschriftungen) bestimmen die Stecker und Versorgung. Danach native KiCad-Symbole/Footprints und einen überprüfbaren Schaltplan erstellen.

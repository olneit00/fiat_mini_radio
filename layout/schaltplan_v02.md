# Schaltplanentwurf – Trägerplatine v0.3, ohne Verstärker

**Status: Entwurf, keine native KiCad-Schaltplandatei, nicht fertigungsreif.**

## Architektur

```text
    USB-C-Kabel
         |
         v
  +-------------------------+
  | ESP32-S3-DevKitC-1      |
  | integrierte USB-C-Buchse|
  | integrierte 3V3-Regelung|
  | BOOT / RESET vorhanden  |
  +-------------------------+
      |   |   |    |
      |   |   |    +-- GPIOs -> Encoder 1 + Encoder 2
      |   |   +------- SPI -> ST7789-Display
      |   +----------- I2S -> PCM5100-Steckmodul -> Line-Out
      +--------------- GND, 3V3 und ggf. 5V -> Peripherie
```

**Wichtig:** Auf der Trägerplatine gibt es **keine eigene USB-C-Buchse, keinen USB-Controller, keine USB-Datenleitung, keinen eigenen Spannungsregler und keine BOOT-/RESET-Taster**. Das vorhandene ESP32-S3-DevKitC-1 wird in zwei passende Buchsenleisten gesteckt. USB-C bleibt direkt am DevKit; keine Gehäuse-Durchführung geplant.

## Display (ST7789)
| Signal | ESP32 GPIO | Status |
|---|---|---|
| CS | 17 | Firmware |
| DC | 16 | Firmware |
| RST | 15 | Firmware |
| SCLK | offen | SPI2(HSPI)-Core-Belegung prüfen |
| MOSI | offen | SPI2(HSPI)-Core-Belegung prüfen |
| BLK / VCC / GND | offen | Tatsächliches Displaymodul prüfen |

**Achtung:** Historische Prototyp-Verdrahtung vertauscht CS und RST gegenüber aktuellem `myoptions.h`.

## PCM5100 (aufgelötete 6-polige Buchsenleiste)
| Modul-Pin | Beschriftung | Verbindung |
|---|---|---|
| 1 | VIN | 3V3 oder 5V **nach Prüfung des Breakouts** |
| 2 | GND | GND |
| 3 | LCK | GPIO6 |
| 4 | DIN | GPIO5 |
| 5 | BCK | GPIO4 |
| 6 | SCK | **GND** |

Analogausgänge L/R/GND separat als Line-Out herausführen; Position/Steckverbinder des Moduls noch prüfen. **Kein Audioverstärker.**

## Encoder
- Encoder 1: A=GPIO47, B=GPIO21, Taster=GPIO7, Common=GND
- Encoder 2: A=GPIO39, B=GPIO40, Taster=GPIO41, Common=GND
- Pull-ups in Firmware prüfen; tatsächliche Encoder-Footprints und Orientierung festlegen.

## Versorgung und Mechanik
- Nur die auf dem DevKit verfügbaren **3V3/GND** und ggf. **5V** zur Peripherie verteilen. Belastbarkeit des DevKit-Reglers und die Modulspannungen vor Verbindung prüfen.
- Keine direkte Verbindung mit 12 V.
- Exaktes DevKit-Header-Raster und Pinpositionen messen/mit Datenblatt abgleichen; USB-C-Stecker muss im eingebauten Zustand zugänglich sein, ohne zusätzliche Gehäusebuchse.
- WLAN-Antennenbereich des DevKits von Kupfer und Metall nach Herstellerangaben freihalten.
- Vor PCB-Freigabe: ERC/DRC, Versorgung, Steckrichtung, CAD-Abmessungen.

## Nächster Schritt
Pin- und Footprintabgleich des **konkreten ESP32-S3-DevKitC-1**, ST7789 und PCM5100, dann native KiCad-Schaltplandatei und Trägerplatinenlayout.

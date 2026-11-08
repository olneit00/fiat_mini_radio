# Komponenten und offene Punkte

## Aus dem Repository bestätigt
- Boardziel: `esp32-s3-devkitc1-n16r8`, 16 MB Flash und 8 MB PSRAM (`firmware/platformio.ini`). Das ist **nicht** das klassische ESP32-WROOM-32.
- Display: `DSP_ST7789_240`, 240×240, SPI; **nicht** GC9A01 (`firmware/myoptions.h`, `src/core/options.h`).
- I²S-Pins: GPIO5 Data, GPIO4 BCLK, GPIO6 LRCK.
- Zwei Encoder: GPIO47/21/7 und GPIO39/40/41. Pull-ups laut Default `true`.
- Display-Steuerpins: GPIO17 CS, GPIO16 DC, GPIO15 RST.
- `VS1053_CS=255` und `SDC_CS=255`: deaktiviert.
- Kein Si4703 in der aktiven Konfiguration nachgewiesen. Die genannte Si4703-Quarzfrequenz ist daher für diese Revision **nicht relevant**.

## Prototyp / zu verifizieren
- Bisher genannter DAC: PCM5100-Breakout; Modul-Pinout, Versorgung und MCLK-Anforderungen am tatsächlichen Teil prüfen.
- Audioverstärker: genaue Platine, Versorgung, Leistung, Lautsprecherlast und Einschaltverhalten offen.
- Display-Hintergrundbeleuchtung: direkter 3,3-V-Anschluss oder geregelter Treiber? Strombedarf prüfen.
- SPI2/HSPI auf ESP32-S3: tatsächliche Standardpins der verwendeten Arduino-ESP32-Boardvariante und `SPI2.begin(...)` ermitteln. Nicht die ESP32-WROOM-32-Defaults übernehmen.
- Boot/EN, USB D+/D-, 3,3-V-Regler, Reset-Beschaltung, Masse und alle Stecker sind durch Software allein nicht rekonstruierbar.

## Datenblatt-/Referenzquellen (Hersteller)
- ESP32-S3-WROOM-1: https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf
- ESP32-S3 Hardware Design Guidelines: https://docs.espressif.com/projects/esp-hardware-design-guidelines/en/latest/esp32s3/
- ESP32-S3-DevKitC-1: https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide.html
- PCM5100A (Familienreferenz; tatsächliches DAC-Modul prüfen): https://www.ti.com/product/PCM5100A
- ST7789V (Controllerfamilie; konkretes Displaymodul prüfen): https://www.sitronix.com.tw/

## Rechtliches
Die Dateien enthalten nur generische Bauteilbezeichnungen und technische Fakten. Vor der Weitergabe von Firmware fremde Lizenzbedingungen, Copyright-Hinweise und verwendete Bibliotheken prüfen. Keine Geheimnisse oder WLAN-Zugangsdaten einchecken.

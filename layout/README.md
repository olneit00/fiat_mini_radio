# PCB-Layout – DRAFT v0.2

**Nicht zur Fertigung freigegeben.** Basis: `firmware/myoptions.h` und `firmware/platformio.ini`.

## Festgelegter Umfang
- ESP32-S3-WROOM-1 (passende 16-MB-Flash-/8-MB-PSRAM-Variante noch anhand der Modulbestellnummer prüfen)
- USB-C: 5-V-Versorgung und USB-Programmierung
- 3,3-V-Regler für ESP32 und geeignete Peripherie
- ST7789-SPI-Display (240×240)
- zwei Drehencoder mit Tastern
- PCM5100-I²S-DAC und analoger Stereo-Line-Out
- **kein Audioverstärker** auf der Platine
- **kein** Si4703-UKW-Empfänger, kein GC9A01

## Dateien
- [schaltplan_v02.md](schaltplan_v02.md): elektrischer Blockschaltplan, USB-C-/Reset-/Boot-Konzept und offene Gates
- [pin_mapping.csv](pin_mapping.csv): aktuelle Firmware-GPIOs
- [schaltplan_netzliste.csv](schaltplan_netzliste.csv): erste Signalzuordnung; **unvollständig**
- [bom.csv](bom.csv): vorläufige Bauteile, ohne Verstärker
- [kicad_pin_assignment.csv](kicad_pin_assignment.csv): KiCad-Vorbereitung, **keine** native Schaltplandatei
- [pcb_layout_guide.md](pcb_layout_guide.md): Layoutregeln
- [komponenten_details.md](komponenten_details.md): Referenzen und Prüfaufgaben

## Noch zu verifizieren
SPI-SCLK/MOSI bei `SPI2(HSPI)` im tatsächlich gebauten Arduino-ESP32-Core; exakte Display- und PCM5100-Modulanschlüsse; 5-V-/3,3-V-Versorgung; USB-Datenleitungen; mechanische CAD-Maße. Ein fertiger KiCad-Schaltplan und ein geroutetes PCB stehen noch aus.

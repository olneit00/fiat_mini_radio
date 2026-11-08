# PCB-Layout – DRAFT v0.3 (Trägerplatine)

**Nicht zur Fertigung freigegeben.** Grundlage: vorhandenes **ESP32-S3-DevKitC-1 N16R8** mit eigener USB-C-Buchse, `firmware/myoptions.h` und `firmware/platformio.ini`.

## Festgelegter Umfang
- **Vorhandenes ESP32-S3-DevKitC-1** wird auf Buchsenleisten der Trägerplatine gesteckt; kein nacktes ESP32-WROOM-Modul auf der Trägerplatine.
- **Stromversorgung und Firmware-Upload ausschließlich über die USB-C-Buchse am DevKit.** Keine USB-C-Buchse, kein 3,3-V-Regler, keine USB-Datenleitungen, keine zusätzlichen BOOT-/RESET-Taster auf der Trägerplatine.
- ST7789-SPI-Display (240×240) über Steckanschluss.
- Zwei Drehencoder mit Tastern.
- Vorhandenes PCM5100-I²S-DAC-Modul über 6-polige Buchsenleiste; SCK an GND, BCK an GPIO4.
- Stereo-Line-Out, **kein Audioverstärker**.
- Keine 12-V-Fahrzeugversorgung auf der Trägerplatine.

## Dateien
- [schaltplan_v02.md](schaltplan_v02.md): aktuelle Trägerplatinen-Architektur (inhaltlich v0.3)
- [pcm5100_module.md](pcm5100_module.md): DAC-Pinfolge und SCK an GND
- [pin_mapping.csv](pin_mapping.csv): Firmware-GPIOs
- [schaltplan_netzliste.csv](schaltplan_netzliste.csv): vorläufige Signalzuordnung; unvollständig
- [bom.csv](bom.csv): Stückliste der Trägerplatine
- [kicad_pin_assignment.csv](kicad_pin_assignment.csv): KiCad-Vorbereitung, noch keine native Schaltplandatei
- [pcb_layout_guide.md](pcb_layout_guide.md) und [komponenten_details.md](komponenten_details.md): ältere Draft-Hinweise; bei Widerspruch gilt dieser Stand v0.3

## Vor Fertigung zu prüfen
- Exaktes DevKitC-1-Board (Headerreihenabstand, Anzahl Pins, USB-Buchsen-Überstand, verfügbare 3V3-/5V-Pins, Einsteckrichtung)
- Strombedarf und zulässige 3V3-/5V-Versorgung von Display und DAC; DevKit-Reglerkapazität
- SPI-SCLK/MOSI aus tatsächlich verwendetem Arduino-Core und Pin-Konfiguration
- PCM5100-Modul-Pitch, Ausgänge und Abmessungen
- Mechanische Passung mit CAD-Gehäuse und WLAN-Antennenfreiraum

Noch kein fertiger KiCad-Schaltplan oder geroutetes PCB.

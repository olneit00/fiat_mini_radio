# PCB-Layout – Entwurf / DRAFT

**Status: Vorläufige Arbeitsunterlagen. Nicht zur Fertigung freigegeben.**

Diese Dateien sichern die erste Extraktion der GPIO-Zuordnung aus der Firmware und die Vorbereitung einer eigenen Leiterplatte für das Mini-Radio.

## Dateien
- [schaltplan_netzliste.csv](schaltplan_netzliste.csv) – vorläufige Netzzuordnung
- [pin_mapping.csv](pin_mapping.csv) – GPIO- und Funktionsübersicht
- [bom.csv](bom.csv) – vorläufige Stückliste
- [kicad_pin_assignment.csv](kicad_pin_assignment.csv) – KiCad-Vorbereitungstabelle (kein vollständiger Schaltplanimport)
- [pcb_layout_guide.md](pcb_layout_guide.md) – mechanische und elektrische Layout-Hinweise
- [komponenten_details.md](komponenten_details.md) – Datenblattverweise und offene Fragen

**Wichtig:** Die Firmware konfiguriert derzeit einen ESP32-S3 mit ST7789-Display und I²S-Audio. Ein FM-Tuner und ein GC9A01-Display sind in dieser aktiven Konfiguration nicht nachgewiesen. SPI-Takt/Datenleitungen, Stromversorgung und konkrete Modul-Footprints müssen vor dem PCB-Design verifiziert werden.

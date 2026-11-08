# PipER32 – PCB-Layout-Leitfaden (Entwurf)

## Quelle und Status
Repository `olneit00/fiat_mini_radio`, Branch `main`, Firmware `firmware/myoptions.h` und `firmware/platformio.ini`, geprüft 2026-11-08. Keine Fertigungsfreigabe. Die CSV-Dateien sind **Planungs- und Importhilfen**, keine elektrisch vollständige KiCad-Schaltplandatei.

## Mechanik
Der genannte Einbauraum von ungefähr **95 × 43 mm** ist als Vorgabe zu verifizieren. Ob **35 × 45 mm** passt, ist offen: 45 mm überschreiten bereits die nominelle 43-mm-Richtung, sofern nicht gedreht oder in einem anderen Bauraum montiert. STEP/CAD-Maße, Schraubdome, Displayausschnitt, Encoderachsen und maximale Bauhöhe exakt vermessen. Encoder möglichst mechanisch an der Front befestigen, nicht allein über Lötstellen belasten. Eine Hauptplatine mit Steckverbindern ist eine valide Alternative zur durchgehenden Front-PCB.

## Platzierung
- ESP32-S3-WROOM-Modul an Platinenrand, Antennen-Keepout nach Modul-Datenblatt einhalten. Abstand zu Chromrahmen und Metallteilen berücksichtigen.
- DAC räumlich von Schaltregler, WLAN-Antenne und digitalen Displayleitungen trennen; analoge Ausgänge kurz zum Verstärker.
- Display-Steckverbinder zur Displayposition, Encoder nach tatsächlicher Mechanik.
- Spannungsversorgung nahe Eingang; lokale Entkopplung an jedem IC.
- Zwei- oder vierlagige Platine mit möglichst zusammenhängender Massefläche; vier Lagen erleichtern die Rückstromführung.

## Signale
- **SPI:** CS=17, DC=16, RST=15 bestätigt. SCLK und MOSI sind **noch zu verifizieren**; `DSP_HSPI=true` allein ist keine sichere Pinbelegung für das gewählte S3-Board. Kurze Leitungen, durchgängiger Rückstrompfad; keine pauschale 50-Ohm-Impedanzforderung für diese kurzen Displayleitungen.
- **I²S:** DOUT=5, BCLK=4, LRCK=6. DAC-Masterclock und konkrete Modulanschlüsse anhand des verwendeten Boards prüfen.
- **Encoder:** A/B/SW auf 47/21/7 und 39/40/41. Interne Pull-ups sind im Firmwaredefault aktiviert. Optional RC/ESD nach Leitungslänge und tatsächlichem Encodertyp; Entprellung prüfen.
- **I²C:** Aktuell keine aktive I²C-Peripherie aus `myoptions.h` bestätigt. Kein Si4703 einplanen, solange er nicht tatsächlich vorgesehen ist.

## Versorgung und Schutz
- Architektur erst nach Messung von ESP32-WLAN-Spitzenstrom, Display-Backlight, DAC und Verstärker festlegen. 5-V-USB-Eingang und ausreichend dimensionierte 3,3-V-Regelung sind mögliche Optionen, nicht bestehende Verbindungen.
- Für Fahrzeugbetrieb Eingangsschutz gegen Verpolung, Transienten, Spannungseinbrüche und EMV-Störungen separat auslegen; USB-5-V ist keine direkte Fahrzeugversorgung.
- Keramik-Abblockkondensatoren nahe Versorgungspins; Bulk-Kapazität nahe Regler/Lastgruppen nach Datenblättern.
- USB-Datenleitungen: Schutz, Pinbelegung, CC-Widerstände bei USB-C und korrekte S3-USB-Pins erst im Schaltplan festlegen. Boot-/Reset-Taster und Programmierzugang vorsehen.

## Fertigungs-Gates
1. Exakte Stückliste und Fotos aller Module samt Pinbeschriftung.
2. Aktive SPI-Bus-Pins im Build/Boardvariant nachweisen.
3. Stromaufnahme und Stromversorgungsarchitektur festlegen.
4. ESP32-Modulvariante, USB/Boot/Reset und Antennenabstände gemäß Referenzdesign.
5. Schaltplan/ERC, Footprints, DRC, 3D-Kollisionsprüfung, Prototyp und Messung.

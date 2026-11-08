# PipER32 – Drehencoder sauber anschließen

## Elektrische Belegung der Trägerplatine

Die PCB-Entwurfsanschlüsse sind **Lötaugen für vier Adern je Encoder**, keine fünfpoligen Encoder-Footprints. Die tatsächliche mechanische Pinfolge des verwendeten Encoders ist **nicht** bekannt und darf nicht allein anhand der Lage seiner Beinchen geraten werden.

| Encoder | Platinenanschluss | Funktion | ESP32-S3 |
|---|---|---|---|
| Links/Rechts: Encoder 1 (J4) | A | Quadraturkanal A | GPIO47 |
| Encoder 1 (J4) | B | Quadraturkanal B | GPIO21 |
| Encoder 1 (J4) | SW | Drucktaster | GPIO7 |
| Encoder 1 (J4) | GND | gemeinsame Masse | GND |
| Encoder 2 (J5) | A | Quadraturkanal A | GPIO39 |
| Encoder 2 (J5) | B | Quadraturkanal B | GPIO40 |
| Encoder 2 (J5) | SW | Drucktaster | GPIO41 |
| Encoder 2 (J5) | GND | gemeinsame Masse | GND |

**Wichtig:** Bei typischen mechanischen EC11-Encodern sind **drei Pins** der Drehgeberkontakte A, C (gemeinsam), B und **zwei separate Pins** des Drucktasters. Der Taster besitzt zwei Anschlüsse: einer an SW, einer an GND. Der gemeinsame Drehgeberkontakt C muss **ebenfalls an GND**. Daher am Encoder selbst **fünf Pins** belegen, aber **nur vier Leitungen** zur Platine führen, indem C und eine Tasterseite lokal gemeinsam an GND gelegt werden. Die Anordnung der Pins und die Tasterfunktion mit dem Multimeter prüfen; nicht blind nach einem fremden Pinout löten.

## Sauberer mechanischer Aufbau

**Empfohlen für das Mini-Gehäuse:** Encoder mit Gewindehülse und Mutter direkt an der Frontplatte befestigen; keine mechanische Belastung auf die PCB-Lötaugen. Kurzes, flexibles **vieradriges Kabel** pro Encoder (z. B. AWG26–28 Litze) mit kleiner Zugentlastung im Gehäuse. An den fünf Encoderbeinchen Schrumpfschlauch verwenden; die GND-Brücke zwischen C und Taster-GND isolieren.

**Noch wartungsfreundlicher:** Ein kleines Stück Lochrasterplatine mit den beiden Encodern und einem 4-poligen Steckverbinder (z. B. JST-XH 2,54 mm, wenn der Platz reicht; JST-PH 2,0 mm für kompaktere Bauweise). Die Trägerplatine hat momentan nur Lötaugen, keine passenden Steckverbinder-Footprints: für echte Steckbarkeit müssten J4/J5 auf Steckverbinder geändert werden. Steckverbinder brauchen ein eindeutig dokumentiertes Pin-1-/GND-Schema und eine passende Crimpzange bzw. vorkonfektionierte Kabel.

## Prüfen vor dem Anschließen

1. Ohne Versorgung mit dem Multimeter den gemeinsamen Drehgeberkontakt und die zwei Tasterkontakte bestimmen.
2. Prüfen, dass der Taster nur bei gedrücktem Knopf schließt.
3. Die drei Drehgeberkontakte identifizieren (bei Drehen wechselnde Verbindungen zu C).
4. C und eine Tasterseite an GND, die übrigen Kontakte an A/B/SW anschließen.
5. Falls die Drehrichtung vertauscht ist: A und B tauschen oder die Firmware invertieren.
6. Firmware-Pull-ups und Entprellung kontrollieren. Lange ungeschirmte Leitungen vermeiden.

## PCB-Status

**Nicht für die Fertigung freigegeben.** Ein geometrischer Konflikt zwischen GPIO21 und GPIO40 sowie die ausstehende KiCad-DRC-Prüfung sind dokumentiert. Für eine Steckerlösung vor dem Gerber-Export J4/J5-Footprints festlegen und Layout neu prüfen.

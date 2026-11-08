# Mechanische Vorprüfung – Trägerplatine 65 × 65 mm (v0.2)

## Koordinaten (mm, Ursprung oben links)
- Leiterplattenkante: x=0..65, y=0..65.
- ESP32-Sockel links J1: x=10,75; y=5,50..58,84 (22 × 2,54 mm).
- ESP32-Sockel rechts J2: x=35,25; y=5,50..58,84 (22 × 2,54 mm). Abstand der Reihenmitten **24,50 mm**.
- DAC-Buchse J3: **waagerecht**, x=43,00..55,70; y=10,00; sechs Kontakte an der **kurzen DAC-Seite**.
- Encoder-Lötaugen J4: x=4,50; y=12,00..22,50; J5: x=4,50; y=34,00..44,50.
- Display-Lötaugen J6: x=61,00; y=32,00..56,50 (8 × 3,50 mm).

## Mechanischer Check
- Zwischen äußerem ESP32-Sockelpad (J2, Mitte x=35,25, Pad-Radius 0,90) und linkem DAC-Sockelpad (x=43,00, Radius 0,90) liegen 5,95 mm freie **Pad-zu-Pad-Distanz** in x-Richtung. Das sagt **nichts** über den tatsächlichen Abstand der bestückten Modulplatinen aus.
- Der DAC-Modulquerschnitt beträgt nach Nutzermessung ungefähr **17,30 × 31,63 mm**. Die 6 Kontakte liegen auf der kurzen Seite, daher erstreckt sich das Modul voraussichtlich in y-Richtung; die exakte Position der Pinreihe relativ zur Modulkante ist noch nicht vermessen.
- Die DAC-Buchse liegt x=43..55,7, sodass die DAC-Modulbreite bei zentrierter Stiftleiste ungefähr x=40,7..58,0 betragen könnte. **Diese Umrissannahme ist nicht gemessen**. Die Modulfläche kann der ESP32-Modulfläche nahekommen; der Überstand der 3,5-mm-Klinkenbuchse muss geprüft werden.
- ESP32-Modulumriss aus provisorischem Footprint: ungefähr 30 × 59,5 mm (bei Sockelursprung y=5,5: y=2,5..62,0), Breite zwischen x≈8..38. Der Fußabdruck ist **nur eine Annahme**, nicht mechanisch verifiziert.
- Am oberen/unteren Rand bleiben bei ESP32 nur etwa 2,5 bzw. 3,0 mm; der USB-C-Stecker und sein Kabel können über die PCB-Kontur hinausstehen. Das Gehäuse muss diesen Zugang erlauben.
- Die Lötaugen sind an den Randbereichen platziert; Platz für Litzen, Knickradius, Beschriftungen und eventuell Zugentlastung prüfen.

## Noch offene Sperrpunkte vor Produktion
1. HW-678-Sockelpinreihenfolge anhand des **konkreten** Boards vollständig gegenprüfen. Der rechte Sockel J2 ist derzeit 1..22 von oben nach unten gezählt, die ältere Einzel-Footprint-Datei dagegen 44..23. Beide Konventionen müssen vor einer endgültigen Schaltplan-/PCB-Verknüpfung vereinheitlicht werden.
2. DAC-Pinreihe und Klinkenbuchsenüberstand anhand eines Maßfotos prüfen. Insbesondere darf das Modul nicht mit ESP32 oder Gehäuse kollidieren.
3. Verfügbarkeit von 22-poligen Buchsenleisten mit **24,5 mm** Reihenabstand prüfen (zwei unabhängige Einzelreihen sind erforderlich).
4. Leiterbahnen sind **noch nicht geroutet**; Netzzuordnung ist keine physische Verbindung. Ohne Routing, DRC und reale Passprobe keine Gerber freigeben.

Die Verdrahtung aus der Firmware: Display GPIO18/14/17/16/15; DAC GPIO4/5/6; Encoder links GPIO47/21/7, rechts GPIO39/40/41; 3V3 und GND wie dokumentiert.

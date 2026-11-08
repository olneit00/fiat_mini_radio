# PCM5100-Steckmodul – Anschluss J2 (DRAFT)

Vorhandenes DAC-Breakout wird auf eine aufgelötete **6-polige Buchsenleiste** der Hauptplatine gesteckt. Pinfolge **aus Sicht der vom Nutzer angegebenen Beschriftungsrichtung von links nach rechts**:

| J2 Pin | Aufdruck Modul | Netz | ESP32-S3 |
|---|---|---|---|
| 1 | VIN | DAC_VIN_TBD | – |
| 2 | GND | GND | GND |
| 3 | LCK | I2S_LRC | GPIO6 |
| 4 | DIN | I2S_DOUT | GPIO5 |
| 5 | BCK | I2S_BCLK | GPIO4 |
| 6 | SCK | DAC_SCK_TBD | zunächst nicht angeschlossen, nach Modulprüfung |

## Schaltplan / Footprint

- Symbol: `Connector_Generic:Conn_01x06`.
- Footprint **vorläufig**: `Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical`, **nur falls** der tatsächliche Stiftabstand 2,54 mm beträgt.
- Pin-1-Markierung und Ansicht des gesteckten Moduls vor Layout anhand der Platine kontrollieren; Einsteckrichtung ist für die physische Anordnung entscheidend.
- VIN nicht blind mit 3V3 oder 5V verbinden. Prüfen, ob das konkrete Breakout einen Regler enthält und welche Versorgung es verlangt.
- Der PCM5100A kann je nach Breakout ohne externes SCK/MCLK über seine interne PLL betrieben werden; Pin 6 nur nach Prüfung der konkreten Breakout-Schaltung offen lassen.
- Analogausgänge LOUT, ROUT und GND müssen separat an einen Line-Out-Stecker geführt werden. Die sechs aufgeführten Pins enthalten **keine** Audioausgänge.
- Kein Audioverstärker vorgesehen.

**Status:** Die sechs Aufdrucke und ihre Reihenfolge wurden vom Nutzer bestätigt. Modulspannung, Pitch, Abmessungen, Ausgangsanschlüsse und SCK-Beschaltung sind offen.

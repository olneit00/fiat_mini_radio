# PipER32 – Mini-Radio für den Fiat 500

**PipER32** ist ein kompaktes, selbst gebautes Internetradio im Stil klassischer Autoradios der 1960er-Jahre. Das Projekt verbindet ein individuell konstruiertes, 3D-druckbares Gehäuse mit moderner Elektronik und einer bewusst zurückhaltenden Retro-Optik.

Das Gerät ist für den Einbau in einen kleinen vorhandenen Aschenbecher-Schacht eines historischen Fiat 500 gedacht. Die Konstruktion kann auch als Ausgangspunkt für andere kompakte Einbauten dienen.

> **Projektstatus (November 2026):** CAD-Modelle, der yoRadio-basierte Firmware-Quellcode und erste Unterlagen zur Leiterplattenentwicklung sind im Repository vorhanden. Die Elektronik läuft bisher als verdrahteter ESP32-S3-DevKit-Prototyp. Die Dateien in `layout/` sind **DRAFT** und ausdrücklich noch nicht zur Fertigung freigegeben.

## Konzept

- Kompaktes Gehäuse mit separater Front- und Rückwand
- Zwei klassische Drehknöpfe als Bedienelemente
- Kleines Farbdisplay zwischen den Knöpfen
- Internet-Audiowiedergabe über WLAN
- Statische, nostalgisch gestaltete Frequenzskala im Ruhezustand
- Moderne Benutzeroberfläche während der Bedienung
- Selbst entworfene, 3D-druckbare Gehäuseteile

Die Retro-Skala ist **rein dekorativ**: Sie stellt weder einen realen UKW-Empfänger noch eine Abstimmung auf analoge Frequenzen dar. Beim Bedienen erscheint weiterhin die reguläre Benutzeroberfläche.

## Mechanischer Aufbau

Die druckbaren Modelle befinden sich im Verzeichnis [CAD](CAD/).

| Datei | Inhalt |
| --- | --- |
| `01_Grundgehaeuse.stl` | Hauptgehäuse |
| `02_Frontpanel.stl` | Frontplatte |
| `03_Heckpanel.stl` | Rückwand |
| `04_Chromrahmen.stl` | Separater dekorativer Frontrahmen |
| `05_Drehknopf.stl` | Drehknopf |
| `06_Chromring.stl` | Dekorativer Ring für einen Drehknopf |
| `07_Test_010.stl` bis `09_Test_030.stl` | Testmodelle |
| `fiat-radio.solidcraft` | Bearbeitbares CAD-Projekt (Dateiname aus der Entwicklung) |

Die Front ist mehrteilig ausgeführt, damit Zierelemente unabhängig von der Grundplatte gefertigt und oberflächenbehandelt werden können. Die endgültigen Maße, Druckparameter, Toleranzen und Befestigungspunkte sind vor einem Nachbau am CAD-Modell und am eigenen Einbauort zu prüfen.

### Hinweise zum 3D-Druck

Die STL-Dateien lassen sich in einem geeigneten Slicer öffnen. Material, Schichthöhe, Stützstrukturen und Ausrichtung hängen vom eingesetzten Drucker und der späteren Einbausituation ab.

Für den dauerhaften Einsatz im Fahrzeug sind insbesondere hohe Innenraumtemperaturen, UV-Belastung, mechanische Befestigung und ausreichender Abstand zu elektrischen Komponenten zu berücksichtigen. Ein geeigneter Werkstoff ist anhand seiner tatsächlichen Temperaturbeständigkeit auszuwählen.

## Elektronik – Prototyp und geplante eigene Leiterplatte

Das bisherige Hardwarekonzept umfasst:

| Baugruppe | Beschreibung |
| --- | --- |
| Mikrocontroller | ESP32-S3-Entwicklungsboard mit WLAN |
| Display | Kleines ST7789-Farbdisplay über SPI |
| Audioausgabe | Externer I²S-Digital-Analog-Wandler |
| Verstärker | Kompakte Audioverstärkerplatine |
| Bedienung | Zwei Drehencoder, gegebenenfalls mit Drucktastern |
| Stromversorgung | Geregelte Versorgung passend zu den verwendeten Komponenten |

Diese Tabelle beschreibt den bisherigen Aufbau, **keine abschließend verifizierte Stückliste**.

### Displayanschlüsse: frühere Prototypverdrahtung und aktuelle Firmware

Die folgende Tabelle dokumentiert die **früher notierte Prototypverdrahtung** und ist **nicht** mit der aktuellen Firmwarekonfiguration identisch. Für die PCB-Entwicklung gelten zunächst die aktiven Definitionen in `firmware/myoptions.h` (CS=17, DC=16, RST=15). Die SPI-Buspins müssen anhand des verwendeten ESP32-S3-Arduino-Cores noch verifiziert werden.

| Display-Signal | GPIO / Anschluss |
| --- | --- |
| SCL / CLK | GPIO 13 |
| SDA / MOSI | GPIO 14 |
| CS | GPIO 15 |
| DC | GPIO 16 |
| RES / RST | GPIO 17 |
| Hintergrundbeleuchtung | 3,3 V gemäß verwendeter Displayplatine |

Die Firmware definiert außerdem I²S auf GPIO 5/4/6 und zwei Encoder auf GPIO 47/21/7 beziehungsweise 39/40/41. Die tatsächlichen Modulanschlüsse, SPI-Buspins, Versorgung und Footprints müssen noch geprüft werden. **Keinesfalls Anschlüsse allein anhand dieser vorläufigen Tabelle verdrahten.**

## Software und Bedienoberfläche

Der Quellcode liegt jetzt unter [firmware](firmware/). Er basiert auf [yoRadio](https://github.com/e2002/yoradio) und wird für das Mini-Radio angepasst. `firmware/platformio.ini` konfiguriert ein ESP32-S3-DevKitC-1 N16R8 mit 16 MB Flash und 8 MB PSRAM; `firmware/myoptions.h` enthält die projektspezifischen Pinzuordnungen. Der genaue Build- und Teststand sowie die Lizenzhinweise sind vor einem Nachbau zu prüfen.

Vorgesehen beziehungsweise im bisherigen Prototyp erprobt:

- Empfang von Internet-Audiostreams über WLAN
- Bedienung über zwei Drehencoder
- Anzeige von Sender- und Statusinformationen
- Automatischer Wechsel zu einer Retro-Anzeige bei Inaktivität
- Rückkehr zur regulären Benutzeroberfläche bei Bedienung

### Retro-Anzeige

Der Ruhezustand orientiert sich allgemein an beleuchteten Analogskalen der 1960er-Jahre:

- Elfenbeinfarbener Hintergrund
- Dunkle Skalenmarkierungen und Ziffern
- Fester roter Abstimmzeiger
- Dezente, gleichmäßige Beleuchtungswirkung

Die Skala ist als **statisches Designmotiv** vorgesehen. Der Zeiger bewegt sich nicht mit der Senderauswahl und es werden keine Internetsender auf analoge Frequenzen abgebildet. Damit bleibt die vorhandene Steuerung unabhängig vom dekorativen Erscheinungsbild.

## PCB-Entwicklung (DRAFT)

Unter [layout](layout/) liegen erste Arbeitsdateien zur eigenen Leiterplatte: vorläufige Netzliste, GPIO-Pinmapping, Stückliste, KiCad-Vorbereitungstabellen, Bauteilhinweise und ein Layout-Leitfaden. Diese Unterlagen sind **noch kein vollständiger KiCad-Schaltplan** und nicht zur Produktion freigegeben.

Für die Platine ist ein ESP32-S3-WROOM-1-Modul statt des bisherigen DevBoards vorgesehen. Vor der Umsetzung sind insbesondere die tatsächlichen SPI-Leitungen, die Versorgung von Display/DAC/Verstärker, USB-Programmierung, Boot-/Reset-Schaltung, Antennenfreiraum und die mechanischen Einbaumaße zu klären.

## Repository-Struktur

| Verzeichnis | Inhalt | Stand |
| --- | --- | --- |
| [`CAD/`](CAD/) | STL-Modelle und SolidCraft-Projekt | Vorhanden |
| [`firmware/`](firmware/) | yoRadio-basierter Quellcode, Konfiguration und Webressourcen | In Entwicklung |
| [`layout/`](layout/) | Pinmapping, Netzliste, BOM und PCB-Planung | **DRAFT** |

## Nächste Schritte

- [x] Firmwarestand in das Repository aufnehmen
- [ ] Abhängigkeiten und Open-Source-Lizenzen prüfen und dokumentieren
- [ ] Finale Pinbelegung aller Baugruppen ergänzen
- [ ] Stückliste und Stromversorgung dokumentieren
- [ ] Build- und Flash-Anleitung anhand des tatsächlichen Quellcodes erstellen
- [ ] Tastenfunktionen sowie Verhalten bei kurzem und langem Tastendruck verifizieren
- [ ] Fotos, Einbaumaße und Druckhinweise ergänzen
- [ ] Darstellung der Retro-Skala mit dem finalen Display abgleichen

## Sicherheit und rechtliche Hinweise

Dies ist ein privates Maker- und Dokumentationsprojekt, **kein offizielles oder von einem Fahrzeug- oder Gerätehersteller unterstütztes Produkt**. Die Gestaltung ist eigenständig und lediglich allgemein von der Ästhetik historischer Geräte inspiriert. Fremde Logos, Wortmarken, originale Skalenabbildungen und geschützte Grafiken sind nicht Bestandteil dieser Dokumentation.

**Software-Lizenzen:** Fremde Software und Bibliotheken behalten ihre jeweiligen Lizenzbedingungen. Bei Änderungen und Weitergabe der bereits enthaltenen Firmware müssen vorhandene Urheberrechtshinweise, Lizenztexte und gegebenenfalls Hinweise auf Änderungen korrekt übernommen werden. Für eigene Inhalte wurde noch keine Lizenz festgelegt; daraus ergibt sich keine pauschale Erlaubnis zur Weiterverwendung.

**Zugangsdaten:** Keine Passwörter, WLAN-Zugangsdaten, API-Schlüssel oder Zugriffstoken einchecken. Lokale Konfigurationen vor dem Veröffentlichen kontrollieren. Bereits offengelegte Zugangsdaten unverzüglich widerrufen.

**Einbau und Betrieb:** Anschlüsse elektrisch absichern, die Spannungsversorgung auf mögliche Fahrzeugspannungsschwankungen auslegen und den Einbau so gestalten, dass weder Bedienung noch Fahrzeugsicherheit beeinträchtigt werden. Die bereitgestellten Dateien und Angaben erfolgen ohne Gewähr; Nachbau und Betrieb erfolgen in eigener Verantwortung.

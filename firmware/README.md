# firmware - Fiat 500 L mini radio (yoRadio fork)

ESP32-S3 internet radio firmware for a radio built into the ashtray slot of a
1969 Fiat 500 L. Front with two rotary encoders, 1.3" ST7789 240x240 SPI
display, I2S DAC (PCM5100), retro 1960s UKW dial as screensaver.

## Origin and license

This firmware is a modified version of **yoRadio** by e2002
(https://github.com/e2002/yoradio), base revision
`2fd3e388d528756f7db666b2261326a6ff234dc7` (release v0.9.720).

yoRadio is licensed under the **GNU General Public License v3.0**. This
firmware is therefore also distributed under GPL-3.0; see [LICENSE](LICENSE).
Third-party libraries bundled in `yoRadio/src` keep their own licenses.

All modifications relative to the base revision are listed in
[CHANGES.md](CHANGES.md), as required by GPL-3.0 section 5(a).

## Hardware (summary)

| Function            | ESP32-S3 GPIO                         |
|---------------------|---------------------------------------|
| Display SCK / MOSI  | 18 / 14 (SPI2, `DSP_HSPI`)            |
| Display RST/DC/CS   | 15 / 16 / 17                          |
| I2S BCLK/DOUT/LRC   | 4 / 5 / 6 (see CHANGES.md)            |
| Encoder 1 (volume)  | 47, 21, 7                             |
| Encoder 2 (station) | 39, 40, 41                            |

Display backlight is tied to 3.3 V. Full configuration: `myoptions.h`.

## Build

1. Install PlatformIO and open the `firmware` folder.
2. Adjust `myoptions.h` to your hardware if needed.
3. `pio run -e yoradio`, then upload the filesystem and firmware.

Personal files `data/data/wifi.csv` and `data/data/playlist.csv` are not part of
this repository (see `data/data/.gitignore`). Create them locally from the
templates described in the yoRadio documentation.

## Screensaver

`#define RETRO_SCREENSAVER true` in `myoptions.h` activates the static dial
(88-108 MHz, pointer fixed at 96 MHz). With `false` the original bouncing clock
is used.

## Contact

Issues related to this hardware fork: use the issue tracker of this repository.
Issues in the base firmware: https://github.com/e2002/yoradio/issues

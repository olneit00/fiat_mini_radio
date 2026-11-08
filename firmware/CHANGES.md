# CHANGES - modifications relative to e2002/yoradio

Base revision: `2fd3e388d528756f7db666b2261326a6ff234dc7` (yoRadio v0.9.720, GPL-3.0)
Modified by: olneit00 (Fiat 500 L mini radio project)
Date of this release: 2026-11-08

Per GPL-3.0 section 5(a), every modified file is listed below with a short
description. Lines are summarised, not diffed. Run `git diff 2fd3e388` in the
upstream repository to see the exact changes.

## 1. New files (hardware and build configuration)

| File | Purpose |
|------|---------|
| `myoptions.h` | Hardware configuration for ESP32-S3-DevKitC-1 N16R8, ST7789 240x240 over SPI2 (`DSP_HSPI`), `ROTATE_90`, I2S pins, encoder pins, `RETRO_SCREENSAVER`. |
| `platformio.ini` | PlatformIO environment `yoradio` for `esp32-s3-devkitc1-n16r8`, Arduino framework. |
| `partitions.csv` | Partition table used for the 16 MB flash. |
| `.gitignore` | Ignore rules for build output and IDE files. |

## 2. Modified files

### 2.1 Display and screensaver (retro dial)

- **`src/core/options.h`**: added default `RETRO_SCREENSAVER false` (feature flag).
- **`src/core/display.h`**: includes `options.h`; forward declaration and member
  `FrequencyScaleWidget *_freqscale` (only with `RETRO_SCREENSAVER`); constructor
  now initialises all widget pointers to `NULL` (was `Display() {}`).
- **`src/core/display.cpp`**:
  - `Display::~Display()` deletes `_freqscale` when the feature is active.
  - `Display::init()` calls `SPI2.begin(18, -1, 14, -1)` when `DSP_HSPI` is set
    (SCK=GPIO18, MOSI=GPIO14; MISO and CS unused). Upstream does not call this.
  - `Display::_buildPager()`: with `RETRO_SCREENSAVER`, the screensaver page
    contains the dial instead of the clock.
  - `Display::loop()`, case `CLOCK`: with `RETRO_SCREENSAVER` the clock is only
    updated in player mode, so the clock is not drawn over the dial.
- **`src/displays/widgets/widgets.h`**: new class `FrequencyScaleWidget`
  (only with `RETRO_SCREENSAVER`).
- **`src/displays/widgets/widgets.cpp`**: implementation of
  `FrequencyScaleWidget`. Static drawing, no animation, no link to the station
  list. Scale 88-108 MHz, labels every 4 MHz, ticks of three lengths, red 3 px
  pointer at 96 MHz, 3 px frame, simulated lamp gradient. Inverted display setting
  is pre-compensated for the hardware inversion of the ST7789 driver.

### 2.2 Audio and SD card

- **`src/audioI2S/Audio.cpp`**: `connecttoSD()` uses `SD_MMC` instead of `SD`.
- **`src/audioI2S/AudioEx.h`**: removed `#include <SD.h>` (library is not used).
- **`src/audioVS1053/audioVS1053Ex.h`**: removed `#include "SD.h"`.
- **`src/core/sdmanager.h`**: `SDManager` is now a wrapper around `SD_MMC`
  (no longer derives from `SDFS`). **API change** for SD card mode; SPI-wired SD
  cards are not supported by this variant.

### 2.3 Encoder and controls

- **`src/core/controls.cpp`** (`encodersLoop()`, non-DSP_DUMMY branch):
  - Encoder 1 is unchanged (volume).
  - Encoder 2: the blocking wait `while(display.mode()!=STATIONS) delay(10)` was
    removed. The `controlsEvent()` call at the end of the branch was removed as
    well; button-pressed rotation calls `player.next()/prev()` directly.
    **Behaviour change**, see section 4.
- **`src/yoEncoder/yoEncoder.cpp`**: `readEncoder_ISR()` expression split over two
  lines with comments. No functional change.

### 2.4 Robustness (timeouts)

- **`src/core/config.cpp`**:
  - `changeMode()`: wait for `SDCHANGE` is limited to 3 s instead of blocking.
  - `waitConnection()`: wait for the connection is limited to 5 s.
- **`src/core/netserver.cpp`**: `begin()` waits at most 5 s for the request queue
  and restarts the ESP32 on failure.
- **`src/core/network.cpp`**:
  - `wifiBegin()`: per-attempt timeout of 10 s in addition to `WIFI_ATTEMPTS`.
  - `searchWiFi()`: recursive task re-creation replaced by a retry loop with
    `MAX_RETRIES = 10`. **Behaviour change**, see section 4.

### 2.5 Web interface

- **`src/core/netserver.h`**: `lang="en" translate="no"` and
  `<meta name="google" content="notranslate">` added to the HTML templates so that
  browsers do not translate the UI automatically.

## 3. Not changed

Audio decoder (`ESP32-audioI2S`), playlist handling, web UI scripts, `data/www`,
IRremoteESP8266, ESPAsyncWebServer and other bundled libraries.

## 4. Known issues and review notes

These changes were made during bring-up and have not been reviewed upstream.
Please check them before reuse:

1. **WiFi gives up after 10 retries** (`network.cpp`, `searchWiFi()`). Upstream
   retries indefinitely. If the router is unavailable at boot, the device stays
   offline until reboot.
2. **Encoder 2 playlist scrolling** (`controls.cpp`): the `controlsEvent()` call
   was removed from the encoder 2 branch. Verify that rotation in the playlist
   view still scrolls the list.
3. **SD card wiring** (`sdmanager.h`, `Audio.cpp`): SD support assumes SD_MMC.
   SPI-wired SD modules need the upstream code.
4. **Hardware-specific defaults** in `myoptions.h` (pins, display model) apply to
   the Fiat 500 L hardware only.

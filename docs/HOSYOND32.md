# Hosyond 3.2-inch E32R32P

This is a hardware port of
[SquachWatch-CYD](https://github.com/skizzophrenic/SquachWatch-CYD), created
by **TalkingSasquach** (`@skizzophrenic`). The original project, history, and
GPL-3.0 license remain intact. E32R32P pin mapping and hardware diagnostics
were cross-checked against iamankushpandit's GPL-3.0
[Gume project](https://github.com/iamankushpandit/Gume).

This local port targets the Hosyond/LCDWIKI/QDtech `E32R32P`: ESP32-WROOM-32E,
240x320 ST7789P3 display, and XPT2046 resistive touch.

The important difference from the ordinary 2.8-inch CYD is the touch wiring.
The XPT2046 shares the display SPI bus and uses GPIO33 for chip select. The
backlight is GPIO27. Do not substitute GPIO22 or GPIO17.

## Build and upload

Connect the board by USB-C, open PowerShell in the repository, and run:

```powershell
python -m platformio run -e hosyond32 -t upload
```

If more than one serial device is attached, add the correct port to the
`hosyond32` section of `platformio.ini`, for example:

```ini
upload_port = COM7
```

To build without uploading:

```powershell
python -m platformio run -e hosyond32
```

The application image is written to
`.pio/build/hosyond32/firmware.bin`. PlatformIO also builds the required
bootloader and partition-table images and flashes all of them at their proper
offsets, so prefer the upload command above over flashing `firmware.bin` alone.

## First boot

The first boot opens the corner-target touch calibration because the 2.8-inch
CYD's built-in calibration is not valid for this digitizer. Use the stylus and
tap each target carefully. The result is saved in flash and follows screen
rotation.

GPIO36 touch IRQ is deliberately not used. This board's IRQ behavior is not
reliable; touch-down is detected from XPT2046 pressure readings instead.

## If something looks wrong

- Stable image but no touch: confirm the PCB/model is `E32R32P` and that this
  target—not `cyd`—was uploaded.
- Red and blue are swapped: open Settings > Color Check. The profile starts
  with the hardware-verified BGR order and normal (non-inverted) polarity.
- Bad saved calibration: hold the screen for about one second immediately
  after boot to clear it, then calibrate again.
- White screen: verify the display is the advertised ST7789P3 model. A
  different controller needs a different build profile.

This target is intentionally absent from `default_envs` and the upstream web
flasher until it has been exercised on the physical Hosyond board.

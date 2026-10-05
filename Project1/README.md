# Cucumber Board Starter (ESP32-S2)

This repository is a minimal ESP-IDF project for the Gravitech Cucumber
R/RS/RI/RIS family. It builds for the ESP32-S2 and starts with the safest
hardware test: GPIO2 blinks once per second while status messages are printed
to the serial monitor at 115200 baud.

## Hardware used by this starter

- MCU/module: ESP32-S2-WROVER
- Flash: 4 MB
- Status LED: GPIO2
- Serial monitor: 115200 baud

The Cucumber RS also has HTS221, BMP280, and MPU-6050 sensors. They are not
required for this first test. Support for them can be added after the basic
build, flash, and serial connection work.

## One-time VS Code setup

This project uses the official **Espressif IDF** extension, not PlatformIO.
The Medium article was written in 2020 and its old `master`-branch setup is no
longer the recommended installation method.

1. Open this repository in Visual Studio Code with **File > Open Folder**.
2. Open **Extensions** (`Shift+Command+X` on macOS).
3. Install the recommended **Espressif IDF** extension when VS Code prompts.
   Its extension ID is `espressif.esp-idf-extension`.
4. Open the Command Palette (`Shift+Command+P`).
5. Run **ESP-IDF: Open ESP-IDF Installation Manager**.
6. Install a stable ESP-IDF release and its tools. Keep the suggested install
   paths unless you have a reason to change them.
7. Run **ESP-IDF: Select Current ESP-IDF Version** and select the installation.
8. Run **ESP-IDF: Doctor Command**. Resolve any item shown as an error before
   building.

Official setup guide:
<https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/installation.html>

## Connect the board

1. Use a USB **data** cable and the Cucumber programming/UART USB connector,
   not its USB-OTG connector.
2. In the Command Palette, run **ESP-IDF: Select Port to Use**.
3. On macOS the port normally looks like `/dev/cu.usbserial-*`.

If no USB serial port appears:

- try a different data cable and USB port;
- disconnect and reconnect the board;
- check whether macOS can see the FTDI USB-to-serial device;
- install the FTDI VCP driver only if your macOS version does not provide a
  working driver: <https://ftdichip.com/drivers/vcp-drivers/>.

## Build, flash, and monitor

The target is already fixed to `esp32s2` in the root `CMakeLists.txt`.

From the Command Palette, run these commands in order:

1. **ESP-IDF: Build your Project**
2. **ESP-IDF: Flash your Project**
3. **ESP-IDF: Monitor your Device**

You can also use the ESP-IDF buttons in the VS Code status bar. A successful
boot repeatedly prints messages similar to:

```text
I (...) cucumber: Cucumber ESP32-S2 starter is running
I (...) cucumber: LED on GPIO2: ON
I (...) cucumber: LED on GPIO2: OFF
```

Exit the serial monitor with `Ctrl+]`.

If flashing cannot connect, hold **BOOT**, tap **RESET**, release **BOOT**, and
run the flash command again.

## Project layout

```text
.
├── .vscode/
│   ├── extensions.json       # recommends the ESP-IDF extension
│   └── settings.json         # enables project auto-detection
├── main/
│   ├── CMakeLists.txt
│   └── main.c                # GPIO2 blink + serial log
├── CMakeLists.txt            # ESP-IDF project and ESP32-S2 target
└── sdkconfig.defaults        # reproducible board defaults
```

## Next development steps

After the starter works, useful milestones are:

1. scan the Cucumber RS I2C bus on GPIO12 (SDA) and GPIO13 (SCL);
2. read temperature/humidity from HTS221;
3. read pressure from BMP280;
4. read acceleration and angular velocity from MPU-6050;
5. stream measurements over USB serial, then Wi-Fi/MQTT;
6. enable the 2 MB PSRAM for R/RS/RI/RIS projects that need it.

Do not enable PSRAM blindly if your Cucumber variant does not include it.

## Reference

- [Original Cucumber/ESP-IDF/VS Code article](https://vsupacha-90388.medium.com/%E0%B8%9B%E0%B8%A3%E0%B8%B0%E0%B8%AA%E0%B8%9A%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B8%93%E0%B9%8C%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%9A%E0%B8%AD%E0%B8%A3%E0%B9%8C%E0%B8%94-cucumber-e10796067170)
- [ESP-IDF VS Code extension documentation](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/)

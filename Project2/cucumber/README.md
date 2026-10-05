# Cucumber ESP32-S2 applications

The `common/cucumber_app` ESP-IDF component owns Wi-Fi connection, DHCP,
reconnection, SNTP, and serial time logging. Each `boardN` directory is a
standalone ESP-IDF project; its `sdkconfig.defaults` supplies the unique board
ID and hostname.

## Build and flash one board

With ESP-IDF exported in your shell, for example:

```sh
cd Project2/cucumber/board1
idf.py set-target esp32s2
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

Repeat from `board2`, `board3`, and `board4`, selecting the respective serial
port. The common component is found using `EXTRA_COMPONENT_DIRS`, so do not
copy it into a board directory.

At boot, a board joins SSID `ADV-EMBEDDED-P2`, requests DHCP, sets its
hostname (`cucumber-1` … `cucumber-4`), gets time from `192.168.50.1`, and
prints Bangkok/ICT local time (UTC+7) every 30 seconds. If the AP is
temporarily unavailable it automatically retries connection.

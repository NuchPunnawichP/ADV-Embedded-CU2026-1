# Cucumber ESP32-S2 applications

Each folder below is a separate ESP-IDF application for one physical Cucumber
board. The shared `common/cucumber_app` component handles Wi-Fi, DHCP,
automatic reconnection, NTP, and serial time output.

## Choose the correct folder

| Owner | Folder | Serial identity |
| --- | --- | --- |
| Nuch | `board1` | `Board 1 (Nuch)` / `cucumber-1` |
| Thiha | `board2` | `Board 2 (Thiha)` / `cucumber-2` |
| June | `board3` | `Board 3 (June)` / `cucumber-3` |
| Windy | `board4` | `Board 4 (Windy)` / `cucumber-4` |

## Build, flash, and monitor

1. Export the ESP-IDF environment in your terminal.
2. Change to **your** board folder. The example below is for Nuch/Board 1.
3. Build, flash, and open the serial monitor:

   ```sh
   cd Project2/cucumber/board1
   idf.py set-target esp32s2
   idf.py build
   idf.py -p /dev/ttyUSB0 flash monitor
   ```

   Replace `/dev/ttyUSB0` with the serial port for your Cucumber. Other owners
   use the same commands from `board2`, `board3`, or `board4`.

## Expected serial output

After boot, the board should report its board ID, owner, and hostname. It then
joins `ADV-EMBEDDED-P2`, receives a DHCP address, and requests time only from
`192.168.50.1`. Once synchronized, it prints ICT time (Thailand, UTC+7) every
30 seconds.

If Wi-Fi disappears, the firmware retries automatically. If the time remains
unsynchronized, first confirm that the Pi is online and that `chronyc tracking`
on the Pi reports a valid upstream source.

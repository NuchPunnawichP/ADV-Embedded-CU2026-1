# Project 2 — Raspberry Pi time server and four Cucumber boards

## Goal

Build a small course network in which a Raspberry Pi receives accurate time
from Chulalongkorn University over Ethernet, then supplies that time to four
Gravitech Cucumber ESP32-S2 boards over Wi-Fi.

The Pi runs a minimal Yocto image. It is the Wi-Fi access point, DHCP server,
router/NAT gateway, and local NTP server. The boards do **not** contact public
NTP services; every board synchronizes only with `192.168.50.1`.

## Network defaults

| Item | Value |
| --- | --- |
| WAN interface | `eth0` |
| Access-point interface | `wlan0` |
| Wi-Fi SSID | `ADV-EMBEDDED-P2` |
| Wi-Fi password | `ADVEmbedded2026` |
| Pi/AP address | `192.168.50.1/24` |
| DHCP range | `192.168.50.100`–`192.168.50.150` |
| Board NTP server | `192.168.50.1` |
| Board local timezone | Thailand / UTC+7 (`ICT`) |

## Board assignment

| Board folder | Board ID | Hostname | Owner |
| --- | ---: | --- | --- |
| `cucumber/board1` | 1 | `cucumber-1` | Nuch |
| `cucumber/board2` | 2 | `cucumber-2` | Thiha |
| `cucumber/board3` | 3 | `cucumber-3` | June |
| `cucumber/board4` | 4 | `cucumber-4` | Windy |

Each board prints its ID, owner, hostname, DHCP address, and synchronized ICT
time on the serial monitor.

## Start in this order

1. Get the authoritative Chulalongkorn NTP hostname from the instructor.
2. Replace `REPLACE_WITH_CHULA_NTP_SERVER` in
   `raspberry-pi/meta-adv-embedded-p2/recipes-core/project2/files/adv-embedded-p2.conf`.
3. Build and boot the Pi image using the [Raspberry Pi guide](raspberry-pi/README.md).
4. Build and flash each assigned board using the [Cucumber guide](cucumber/README.md).
5. Follow [INTEGRATION.md](INTEGRATION.md), then complete
   [DEMO_CHECKLIST.md](DEMO_CHECKLIST.md).

## Directory map

```text
raspberry-pi/   Yocto layer, image recipe, and Pi operating instructions
cucumber/      Shared ESP-IDF component and four separate board applications
```

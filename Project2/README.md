# Project 2 — Raspberry Pi and four Cucumber boards

Project 2 creates a small isolated lab network:

- a Raspberry Pi running a minimal custom Yocto image;
- `eth0` as the upstream/WAN interface;
- `wlan0` as access point **ADV-EMBEDDED-P2** at `192.168.50.1/24`;
- DHCP leases from `192.168.50.100` through `192.168.50.150`;
- IPv4 forwarding and NAT through `eth0`;
- the Pi as downstream NTP server at `192.168.50.1`;
- four ESP32-S2 Cucumber clients named `cucumber-1` through `cucumber-4`.

The upstream Chulalongkorn NTP hostname is deliberately not guessed. Replace
`REPLACE_WITH_CHULA_NTP_SERVER` in exactly one file before building:
`raspberry-pi/meta-adv-embedded-p2/recipes-core/project2/files/adv-embedded-p2.conf`.

## Repository layout

```text
Project2/
├── raspberry-pi/                 # Yocto layer, image and Pi operating guide
└── cucumber/
    ├── common/cucumber_app/      # shared ESP-IDF Wi-Fi/NTP component
    └── board1/ … board4/         # independently buildable ESP32-S2 apps
```

Follow the Raspberry Pi [build guide](raspberry-pi/README.md), then flash the
four clients using the [Cucumber guide](cucumber/README.md). The recommended
team hand-off is in [INTEGRATION.md](INTEGRATION.md); the live-test order is in
[DEMO_CHECKLIST.md](DEMO_CHECKLIST.md).

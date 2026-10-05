# Project 2 architecture

```text
                    Chulalongkorn NTP server
                              │
                         eth0 (WAN)
                              │
                 ┌────────────▼────────────┐
                 │ Raspberry Pi / Yocto     │
                 │ chrony: upstream + LAN   │
                 │ hostapd: Wi-Fi AP        │
                 │ dnsmasq: DHCP            │
                 │ nftables: NAT/forwarding │
                 └────────────┬────────────┘
                  wlan0 / 192.168.50.1/24
                              │
       ┌──────────┬───────────┼───────────┬──────────┐
       │          │           │           │          │
 cucumber-1  cucumber-2  cucumber-3  cucumber-4
 ESP32-S2    ESP32-S2    ESP32-S2    ESP32-S2
 DHCP + NTP server 192.168.50.1, local display UTC+7
```

The Pi receives its own wall-clock time from the approved Chulalongkorn NTP
server over `eth0`. Chrony is permitted to answer NTP requests only from the
lab subnet. DHCP gives each Cucumber a route and advertises the Pi as both NTP
server (DHCP option 42) and DNS server. `nftables` permits LAN-to-WAN traffic,
returns established WAN traffic, and masquerades traffic leaving `eth0`.

Credentials are the course defaults, not a production security design. Change
the access-point password before deploying this outside the lab.

# Project 2 architecture

## System view

```text
 Chulalongkorn University NTP server
                │  UDP/123 over Ethernet
                ▼
        eth0 ┌─────────────────────────────────────────────┐
             │ Raspberry Pi — minimal Yocto Linux           │
             │                                               │
             │ chrony     receives upstream time and serves │
             │            NTP only to 192.168.50.0/24       │
             │ hostapd    creates ADV-EMBEDDED-P2           │
             │ dnsmasq    assigns DHCP leases               │
             │ nftables  enables forwarding and NAT         │
             │ OpenSSH    provides administration access    │
             └──────────────────────┬──────────────────────┘
                                    wlan0
                              192.168.50.1/24
                                     │
         ┌───────────────┬───────────┼───────────┬───────────────┐
         ▼               ▼           ▼           ▼
   Board 1 / Nuch  Board 2 / Thiha  Board 3 / June  Board 4 / Windy
    cucumber-1       cucumber-2       cucumber-3       cucumber-4
```

## Data flow

1. `chronyd` on the Pi synchronizes with the approved university server via
   `eth0`.
2. A Cucumber joins the Pi access point on `wlan0` and receives a DHCP lease.
3. DHCP advertises `192.168.50.1` as router, DNS server, and NTP server.
4. The Cucumber requests NTP from `192.168.50.1`, changes to ICT (UTC+7), and
   prints the local time on serial.
5. If a client uses the Pi as its gateway, `nftables` masquerades its traffic
   through `eth0`.

## Boundaries and safety

The firewall only forwards LAN-to-WAN traffic and reply traffic. Chrony permits
NTP clients only from `192.168.50.0/24`. The supplied Wi-Fi password is for
the lab demonstration; replace it before any non-course deployment.

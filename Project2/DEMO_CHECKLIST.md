# Final demonstration checklist

Use this document during the final presentation. Record a screenshot or serial
log beside each completed check if the instructor requires evidence.

## 1. Raspberry Pi readiness

- [ ] The university NTP hostname replaces the marked placeholder in
  `adv-embedded-p2.conf`.
- [ ] `ip -4 addr show wlan0` reports `192.168.50.1/24`.
- [ ] `systemctl status adv-embedded-p2 hostapd dnsmasq chronyd` shows all
  required services healthy.
- [ ] `chronyc tracking` confirms the Pi is synchronized upstream.
- [ ] `nft list ruleset` includes both Project 2 firewall/NAT tables.

## 2. Board connection and time

| Owner | Expected identity | Evidence to show |
| --- | --- | --- |
| Nuch | Board 1 / `cucumber-1` | DHCP address and ICT serial time |
| Thiha | Board 2 / `cucumber-2` | DHCP address and ICT serial time |
| June | Board 3 / `cucumber-3` | DHCP address and ICT serial time |
| Windy | Board 4 / `cucumber-4` | DHCP address and ICT serial time |

- [ ] Every board joined `ADV-EMBEDDED-P2` and received an address from
  `192.168.50.100–150`.
- [ ] Every serial monitor shows `NTP synchronized` and an `ICT` local time.
- [ ] `chronyc clients` on the Pi shows NTP requests from the board network.

## 3. Resilience and end-to-end proof

- [ ] Restart one board and show automatic Wi-Fi reconnection and time recovery.
- [ ] From a connected client, prove Internet access through Pi NAT.
- [ ] Save the Pi status output, four DHCP leases, and four serial logs for the
  submission.

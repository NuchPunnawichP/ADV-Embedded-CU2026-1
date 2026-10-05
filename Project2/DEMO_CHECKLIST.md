# Final demonstration checklist

## Raspberry Pi

- [ ] The approved Chulalongkorn NTP hostname has replaced the marked
  placeholder in `adv-embedded-p2.conf`.
- [ ] `ip -4 addr show wlan0` shows `192.168.50.1/24`.
- [ ] `systemctl status adv-embedded-p2 hostapd dnsmasq chronyd` is healthy.
- [ ] `chronyc tracking` reports a synchronized upstream source.
- [ ] `chronyc clients` shows Cucumber clients after they synchronize.
- [ ] `nft list ruleset` contains the `adv_embedded_p2` table.

## Cucumber boards

- [ ] Each board joins `ADV-EMBEDDED-P2` with its own hostname.
- [ ] Each receives an address in `192.168.50.100–150`.
- [ ] Each serial monitor shows `NTP synchronized` and a local `ICT` time.
- [ ] Restart one board and verify Wi-Fi reconnection and time synchronization.

## End-to-end

- [ ] A connected client can reach the Internet through the Pi (NAT).
- [ ] The Pi continues supplying LAN time after a board reconnects.
- [ ] Record the four leases, NTP status, and serial output for the submission.

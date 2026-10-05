#!/bin/sh
set -eu

echo '== Interfaces =='
ip -4 addr show wlan0
ip -4 addr show eth0 || true
echo '== Services =='
systemctl --no-pager --full status adv-embedded-p2 hostapd dnsmasq chronyd || true
echo '== Time synchronization =='
chronyc tracking || true
chronyc sources -v || true
echo '== DHCP leases =='
cat /var/lib/misc/dnsmasq.leases 2>/dev/null || true
echo '== Firewall =='
nft list table inet adv_embedded_p2 || true
nft list table ip adv_embedded_p2_nat || true

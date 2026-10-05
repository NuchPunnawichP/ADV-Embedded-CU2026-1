#!/bin/sh
set -eu

CONFIG=/etc/adv-embedded-p2/adv-embedded-p2.conf
. "$CONFIG"

case "$CHULA_NTP_SERVER" in
  REPLACE_WITH_CHULA_NTP_SERVER|"")
    echo "Project 2: set CHULA_NTP_SERVER in $CONFIG before starting" >&2
    exit 1
    ;;
esac

ip link set "$AP_IFACE" up
ip addr flush dev "$AP_IFACE" || true
ip addr add "$AP_ADDRESS" dev "$AP_IFACE"
sysctl -w net.ipv4.ip_forward=1

# Keep the NTP hostname in one authoritative, explicitly marked config file.
# Remove a previous generated upstream line before adding the selected source.
sed -i '/# ADV_EMBEDDED_P2_UPSTREAM$/d' /etc/chrony/chrony.conf
printf 'server %s iburst # ADV_EMBEDDED_P2_UPSTREAM\\n' "$CHULA_NTP_SERVER" >> /etc/chrony/chrony.conf

nft delete table inet adv_embedded_p2 2>/dev/null || true
nft delete table ip adv_embedded_p2_nat 2>/dev/null || true
nft -f /etc/adv-embedded-p2/adv-embedded-p2.nft

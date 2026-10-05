# Raspberry Pi Yocto image

## What this image does

The image is a minimal Raspberry Pi Yocto image for Project 2. It provides only
the required course services: OpenSSH, Wi-Fi access point, DHCP, routing/NAT,
upstream NTP synchronization, and downstream NTP for the Cucumber boards.

| Interface/service | Purpose |
| --- | --- |
| `eth0` | University network / WAN connection |
| `wlan0` | `ADV-EMBEDDED-P2` Wi-Fi access point |
| `hostapd` | Creates the access point |
| `dnsmasq` | Gives clients `192.168.50.100`–`192.168.50.150` leases |
| `chrony` | Gets university time and serves Pi time to the boards |
| `nftables` | IPv4 forwarding and NAT through `eth0` |

## Build the image

1. Ask the instructor for the exact Chulalongkorn University NTP hostname.
2. Update this one required setting before building:

   ```text
   meta-adv-embedded-p2/recipes-core/project2/files/adv-embedded-p2.conf
   CHULA_NTP_SERVER=REPLACE_WITH_CHULA_NTP_SERVER
   ```

3. Create a compatible Poky build environment and run `oe-init-build-env`.
4. Add these layers to `BBLAYERS`:

   - `meta-raspberrypi`
   - `meta-openembedded/meta-oe`
   - `Project2/raspberry-pi/meta-adv-embedded-p2`

5. In `conf/local.conf`, set the Pi model in `MACHINE` and include the needed
   Wi-Fi firmware. [local.conf.example](local.conf.example) is the starting
   point.
6. Build the image:

   ```sh
   bitbake adv-embedded-p2-image
   ```

7. Write the generated `.wic` image to an SD card, connect Ethernet, and boot
   the Pi. Use the serial console or OpenSSH for first access.

## First boot and verification

Run this short health check first:

```sh
adv-embedded-p2-status
```

For detailed checks:

```sh
ip -4 addr show wlan0
systemctl status adv-embedded-p2 hostapd dnsmasq chronyd
chronyc tracking
chronyc sources -v
chronyc clients
nft list ruleset
```

The Pi is ready when `wlan0` is `192.168.50.1/24`, the services are healthy,
and `chronyc tracking` shows synchronization. A phone or Cucumber connected to
`ADV-EMBEDDED-P2` with password `ADVEmbedded2026` should receive an address in
the configured DHCP range.

After changing `/etc/adv-embedded-p2/adv-embedded-p2.conf`, restart the setup
and time service:

```sh
systemctl restart adv-embedded-p2 chronyd
```

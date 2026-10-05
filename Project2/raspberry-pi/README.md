# Raspberry Pi Yocto image

This layer targets a Raspberry Pi machine supplied by `meta-raspberrypi` and
expects a Poky build with `meta-openembedded/meta-oe` available for networking
packages. The image stays intentionally small while adding OpenSSH, hostapd,
dnsmasq, chrony, nftables, and the Project 2 configuration package.

## Before building

1. Obtain the exact Chulalongkorn University NTP hostname from the instructor.
2. Edit only this marked value:

   ```text
   meta-adv-embedded-p2/recipes-core/project2/files/adv-embedded-p2.conf
   CHULA_NTP_SERVER=REPLACE_WITH_CHULA_NTP_SERVER
   ```

3. Initialize a compatible Poky/Yocto workspace and source `oe-init-build-env`.
   Add `meta-raspberrypi`, `meta-openembedded/meta-oe`, and this layer to
   `BBLAYERS`; see [local.conf.example](local.conf.example).
4. Set `MACHINE` to the actual Pi model (for example `raspberrypi4-64`), add
   the Wi-Fi firmware appropriate for that model, and build:

   ```sh
   bitbake adv-embedded-p2-image
   ```

5. Write the resulting `.wic` image to an SD card using the normal Yocto
   deployment process, boot with Ethernet connected, and log in over the
   serial console or SSH.

## Runtime checks

```sh
adv-embedded-p2-status
ip -4 addr show wlan0
systemctl status adv-embedded-p2 hostapd dnsmasq chronyd
chronyc tracking
chronyc sources -v
chronyc clients
nft list ruleset
```

`adv-embedded-p2-start` may be run after changing `/etc/adv-embedded-p2/`
files. Restart the service afterward: `systemctl restart adv-embedded-p2`.

For a demo, connect a phone or Cucumber to `ADV-EMBEDDED-P2` using
`ADVEmbedded2026`; it should get a `192.168.50.100–150` lease. The network is
lab-only: rotate the default password before a real deployment.

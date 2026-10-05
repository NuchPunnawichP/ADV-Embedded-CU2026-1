# Integration guide

## Fastest integration order

1. **Pi owner:** replace the marked NTP placeholder, build and boot the Yocto
   image; verify wired Internet and `chronyc tracking`.
2. **Network owner:** verify the AP, DHCP, forwarding, and NAT from one laptop
   before using any board.
3. **Firmware owner:** build and flash `board1`; confirm a DHCP lease and a
   serial line showing time in `ICT` (UTC+7).
4. Repeat for boards 2–4. Their `sdkconfig.defaults` assigns the distinct
   board IDs and hostnames; do not copy one board's defaults over another.
5. Run the complete [demo checklist](DEMO_CHECKLIST.md).

## Combining teammate work

The shared ESP-IDF component is the only code common to all boards. Board
folders contain only their app entry point and identity defaults, so shared
behaviour belongs in `cucumber/common/cucumber_app/`. Keep Pi runtime settings
in `adv-embedded-p2.conf`; it is installed into `/etc/adv-embedded-p2/` by the
Yocto recipe. Do not hard-code a Chula NTP name into the firmware: each board
always uses the Pi (`192.168.50.1`).

Before merging, build at least one Pi image and every `boardN` application.
Use the commands in the two component READMEs and resolve conflicts in shared
configuration before flashing hardware.

# Integration guide

## Team board allocation

| Owner | Build directory | Device identity |
| --- | --- | --- |
| Nuch | `cucumber/board1` | Board 1, `cucumber-1` |
| Thiha | `cucumber/board2` | Board 2, `cucumber-2` |
| June | `cucumber/board3` | Board 3, `cucumber-3` |
| Windy | `cucumber/board4` | Board 4, `cucumber-4` |

Do not exchange `sdkconfig.defaults` files between board folders. They set the
board ID, hostname, and owner displayed on serial.

## Recommended integration sequence

1. **Prepare the Pi.** Obtain the approved university NTP hostname and replace
   the marked value in `adv-embedded-p2.conf`. Build and boot the Yocto image
   with Ethernet connected.
2. **Prove the Pi network.** On the Pi, run `adv-embedded-p2-status` and
   `chronyc tracking`. Connect a phone or laptop to the AP and confirm it
   receives a `192.168.50.x` address and can reach the Internet.
3. **Bring up one board first.** Build and flash Nuch's Board 1. Confirm the
   serial monitor shows the expected owner/hostname, DHCP address, and ICT
   time. Fix Pi networking before attempting the remaining boards.
4. **Add Boards 2–4.** Each owner builds only their assigned directory, flashes
   their board, and records the resulting DHCP address and serial output.
5. **Run the demo.** Use [DEMO_CHECKLIST.md](DEMO_CHECKLIST.md) as the final
   shared verification record.

## Rules for combining changes

- Put shared Wi-Fi, DHCP, NTP, and reconnect behaviour in
  `cucumber/common/cucumber_app/`.
- Keep board-specific identity in that board's `sdkconfig.defaults` only.
- Keep the university NTP host only in the Pi configuration. The firmware must
  keep using the Pi NTP address, `192.168.50.1`.
- Before merging shared firmware changes, build all four board directories.

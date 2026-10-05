SUMMARY = "Minimal Raspberry Pi image for Advanced Embedded Project 2"
LICENSE = "MIT"

inherit core-image

IMAGE_FEATURES += "ssh-server-openssh"
IMAGE_INSTALL:append = " \
    adv-embedded-p2-config \
    bash \
    chrony \
    dnsmasq \
    hostapd \
    iproute2 \
    nftables \
    wireless-regdb \
"

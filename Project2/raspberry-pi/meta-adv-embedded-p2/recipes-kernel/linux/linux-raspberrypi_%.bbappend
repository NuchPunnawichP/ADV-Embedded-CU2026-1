FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI:append = " file://adv-embedded-p2-network.cfg"
KERNEL_CONFIG_FRAGMENTS:append = " ${WORKDIR}/adv-embedded-p2-network.cfg"

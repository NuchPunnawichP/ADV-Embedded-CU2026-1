SUMMARY = "Project 2 access point, NAT, and NTP configuration"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = " \
    file://adv-embedded-p2.conf \
    file://hostapd.conf \
    file://dnsmasq.conf \
    file://chrony.conf \
    file://adv-embedded-p2.nft \
    file://adv-embedded-p2-start.sh \
    file://adv-embedded-p2-status.sh \
    file://adv-embedded-p2.service \
"

S = "${WORKDIR}"
inherit systemd

RDEPENDS:${PN} = "bash chrony dnsmasq hostapd iproute2 nftables"
SYSTEMD_SERVICE:${PN} = "adv-embedded-p2.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"

do_install() {
    install -d ${D}${sysconfdir}/adv-embedded-p2 ${D}${sysconfdir}/hostapd
    install -d ${D}${sysconfdir}/dnsmasq.d ${D}${sysconfdir}/chrony
    install -d ${D}${systemd_system_unitdir} ${D}${sbindir}
    install -m 0644 ${WORKDIR}/adv-embedded-p2.conf ${D}${sysconfdir}/adv-embedded-p2/adv-embedded-p2.conf
    install -m 0644 ${WORKDIR}/hostapd.conf ${D}${sysconfdir}/hostapd/hostapd.conf
    install -m 0644 ${WORKDIR}/dnsmasq.conf ${D}${sysconfdir}/dnsmasq.d/adv-embedded-p2.conf
    install -m 0644 ${WORKDIR}/chrony.conf ${D}${sysconfdir}/chrony/chrony.conf
    install -m 0644 ${WORKDIR}/adv-embedded-p2.nft ${D}${sysconfdir}/adv-embedded-p2/adv-embedded-p2.nft
    install -m 0755 ${WORKDIR}/adv-embedded-p2-start.sh ${D}${sbindir}/adv-embedded-p2-start
    install -m 0755 ${WORKDIR}/adv-embedded-p2-status.sh ${D}${sbindir}/adv-embedded-p2-status
    install -m 0644 ${WORKDIR}/adv-embedded-p2.service ${D}${systemd_system_unitdir}/adv-embedded-p2.service
}

FILES:${PN} += "${sysconfdir}/adv-embedded-p2 ${sysconfdir}/hostapd ${sysconfdir}/dnsmasq.d ${sysconfdir}/chrony ${sbindir}"

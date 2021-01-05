require recipes-bsp/u-boot/u-boot.inc
DESCRIPTION = "Odroid C2/C4/N2 boot loader supported by the hardkernel product"
SECTION = "bootloaders"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

PROVIDES += "virtual/bootloader u-boot"

LIC_FILES_CHKSUM = "file://Licenses/gpl-2.0.txt;md5=b234ee4d69f5fce4486a80fdaf4a4263"

USE_BOOTSCR = "0"
USE_BOOTSCR_odroid-n2 = "1"

UBOOT_MACHINE_odroid-c2 = "odroidc2_defconfig"
UBOOT_MACHINE_odroid-c4-hardkernel = "odroidc4_defconfig"
UBOOT_MACHINE_odroid-n2-hardkernel = "odroidn2_defconfig"
UBOOT_MACHINE_odroid-n2 = "odroidn2_defconfig"
UBOOT_MACHINE_odroid-hc4-hardkernel = "odroidc4_defconfig"

BRANCH_odroid-c2 = "odroidc2-v2015.01"
BRANCH = "odroidg12-v2015.01"

UBOOT_INITIAL_ENV = ""

COMMON_SRC_URI = "git://github.com/hardkernel/u-boot.git;branch=${BRANCH}"

SRC_URI_odroid-c2 = "${COMMON_SRC_URI} \
           https://releases.linaro.org/components/toolchain/binaries/4.9-2017.01/aarch64-linux-gnu/gcc-linaro-${LINAROTOOLCHAIN}-x86_64_aarch64-linux-gnu.tar.xz;name=aarch64toolchain;subdir=git \
           file://boot.ini \
           file://0001-Enable-adc-driver-in-u-boot.patch \
           file://add_rootfs_partion_info.patch \
           file://0001-Enabling-support-for-Amlogic-Hardware-Watchdog-with-.patch \
           file://0002-Replaced-hardcoded-watchdog-timeout-value-with-macro.patch \
           file://0001-makefile-Match-the-bs-and-count-values-with-hardkern.patch \
           file://0001-odroidc2-Enable-s905-on-chip-watchdog.patch \
          "
SRC_URI = "\
    git://github.com/hardkernel/u-boot.git;branch=${BRANCH} \
    file://boot.ini \
    https://releases.linaro.org/archive/13.11/components/toolchain/binaries/gcc-linaro-aarch64-none-elf-4.8-2013.11_linux.tar.xz;name=aarch64linaro;subdir=git \
    https://releases.linaro.org/archive/14.04/components/toolchain/binaries/gcc-linaro-arm-none-eabi-4.8-2014.04_linux.tar.xz;name=aarch64linaroelf;subdir=git \
    "

SRC_URI_append_odroid-c4-hardkernel = "\
    file://config.ini \
    "

SRC_URI_append_odroid-hc4-hardkernel = "\
    file://config.ini \
    "

SRC_URI[aarch64toolchain.md5sum] = "631c4c7b1fe9cb115cf51bd6a926acb7"
SRC_URI[aarch64toolchain.sha256sum] = "d1f2761b697e6b49f5db1ec0cd48d2fd98224be8cb5ef182093f691e99c923eb"

SRC_URI[aarch64linaro.md5sum] = "5fd777bee04a79435a0861efd473ec0e"
SRC_URI[aarch64linaro.sha256sum] = "603ef1733c40361767d62ba9786cf6d373f5787822d3115a877033fcb59567c7"

SRC_URI[aarch64linaroelf.md5sum] = "12d6e8a0cbd2d8e130cc8f55389a95c3"
SRC_URI[aarch64linaroelf.sha256sum] = "98b99b7fa2eb268d158639db2a9b8bcb4361e94087bd2ce29f26199bd09cf459"

# TAG s905_6.0.1_v3.7
SRCREV_odroid-c2 = "95264d19d04930f67f10f162df70de447659329d"

SRCREV = "12c58e94e533b85a19d2f83d1c0a34345764ca07"

PR = "${PV}+git${SRCPV}"

UBOOT_SUFFIX ?= "bin"

PACKAGE_ARCH = "${MACHINE_ARCH}"

S = "${WORKDIR}/git"
B = "${S}"

inherit uboot-boot-scr

DEPENDS += "bc-native atf-native"

EXTRA_OEMAKE_odroid-c2 = 'V=1 CROSS_COMPILE=${TOOLCHAIN_PREFIX} HOSTCC="${BUILD_CC} ${BUILD_CFLAGS} ${BUILD_LDFLAGS}"'
EXTRA_OEMAKE = 'V=1 HOSTCC="${BUILD_CC} ${BUILD_CFLAGS} ${BUILD_LDFLAGS}"'

LINAROTOOLCHAIN_odroid-c2 = "4.9.4-2017.01"
LINAROTOOLCHAIN = "4.8-2013.11"

TOOLCHAIN_PREFIX_odroid-c2 = "aarch64-linux-gnu-"
TOOLCHAIN_PREFIX = "aarch64-linux-gnu-"
HOST_PREFIX_odroid-c2 = "${TOOLCHAIN_PREFIX}"

PATH_prepend ="${S}/gcc-linaro-aarch64-none-elf-4.8-2013.11_linux/bin:${S}/gcc-linaro-arm-none-eabi-4.8-2014.04_linux/bin:"
PATH_prepend ="${S}/gcc-linaro-${LINAROTOOLCHAIN}-x86_64_aarch64-linux-gnu/bin:"

do_configure () {
	CROSS_COMPILE=aarch64-elf- ARCH=arm CFLAGS="" LDFLAGS="" oe_runmake mrproper
	CROSS_COMPILE=aarch64-elf- ARCH=arm CFLAGS="" LDFLAGS="" oe_runmake ${UBOOT_MACHINE}
}

do_configure_append() {
	if [ -e ${WORKDIR}/boot.ini ]; then
		cp ${WORKDIR}/boot.ini ${B}/
	fi
	if [ -e ${WORKDIR}/config.ini ]; then
		cp ${WORKDIR}/config.ini ${B}/
	fi
}

do_compile () {
	CROSS_COMPILE=aarch64-elf- ARCH=arm CFLAGS="" LDFLAGS="" oe_runmake
}

do_compile_append () {
	cp ${S}/sd_fuse/u-boot.bin ${B}/${UBOOT_BINARY}
}

do_install_append() {
	if [ -e ${B}/config.ini ]; then
		install -m 644 ${B}/config.ini ${D}/boot/config-${MACHINE}-${PV}-${PR}.${UBOOT_ENV_SUFFIX}
		ln -sf config-${MACHINE}-${PV}-${PR}.${UBOOT_ENV_SUFFIX} ${D}/boot/config.ini
	fi
}

do_deploy_append() {
	if [ -e ${B}/config.ini ]; then
		install -m 644 ${B}/config.ini ${DEPLOYDIR}/config-${MACHINE}-${PV}-${PR}.${UBOOT_ENV_SUFFIX}
                rm -f ${DEPLOYDIR}/config.ini
		ln -sf config-${MACHINE}-${PV}-${PR}.${UBOOT_ENV_SUFFIX} ${DEPLOYDIR}/config.ini
	fi
}

COMPATIBLE_MACHINE = "(odroid-c2|odroid-c4-hardkernel|odroid-n2-hardkernel|odroid-n2|odroid-hc4-hardkernel)"

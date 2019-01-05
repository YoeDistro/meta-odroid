# Odroid BSP Arm default settings
require conf/machine/include/odroid-default-settings.inc

XSERVER_append = " \
    ${@bb.utils.contains('MACHINE_FEATURES', 'mali', 'xserver-xorg-module-exa', '', d)} \
"

KERNEL_IMAGETYPE ?= "zImage"

PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot"
PREFERRED_PROVIDER_u-boot ?= "u-boot"
PREFERRED_VERSION_u-boot ?= "2018.11"

USE_BOOTSRC ?= "1"
UBOOT_ENV  ?= "boot"
UBOOT_BINARY ?= "u-boot-dtb.bin"
UBOOT_ENV_SUFFIX ?= "scr"
UBOOT_SCRIPT ?= "boot.${UBOOT_ENV_SUFFIX}"
UBOOT_LOAD_CMD ?= "ext4load"
UBOOT_BOOT_CMD ?= "bootz"

UBOOT_BOOTDEV  ?= "2"
UBOOT_BOOTPART ?= "2"
UBOOT_ROOTDEV ?= "1"
UBOOT_ROOTPART ?= "2"
UBOOT_BOOTTYPE ?= "mmc"
UBOOT_ROOTTYPE ?= "mmcblk${UBOOT_ROOTDEV}p"
BOOT_PREFIX ?= "boot/"

UBOOT_EXTRA_ENV ?= ""
UBOOT_FILE_TITLE ?= "#"
BOOT_PREFIX ?= ""
UBOOT_VIDEO ?= "${@bb.utils.contains("DISTRO_FEATURES", "x11", "drm.edid_firmware=edid/1024x768.bin", " ", d)}"
UBOOT_XTRA_CMDLINE ?=  "${@bb.utils.contains('DISTRO_FEATURES', 'TS_vu7+', 'usbhid.quirks=0x16B4:0x0703:0x00000040 ', '', d)}"

IMAGE_BOOT_FILES ?= "${UBOOT_SCRIPT}"

MACHINE_FEATURES_append = " mali"

MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

EXTRA_IMAGEDEPENDS_append = " u-boot secure-odroid"
EXTRA_IMAGEDEPENDS_append = " ${@bb.utils.contains("DISTRO_FEATURES", "x11", " odroid-edid", " ", d)}"
IMAGE_INSTALL_append = " kernel-devicetree"

IMAGE_CLASSES += "image_types_odroid"

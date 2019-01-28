# Odroid XU default BSP

require conf/machine/include/samsung-exynos.inc
require conf/machine/include/odroid-arm-defaults.inc

DEFAULTTUNE = "cortexa15thf-neon-vfpv4"
include conf/machine/include/tune-cortexa15.inc

UBOOT_FDT_LOADADDR = "0x40800000"
UBOOT_LOADADDR = "0x40007FC0"
UBOOT_LOADADDRESS = "0x40007FC0"
UBOOT_KERNEL_NAME = "zImage"
UBOOT_USB_NET = "1"

WKS_FILE ?= "odroid_xu-u-boot.wks"

MACHINE_FEATURES_append = " alsa screen"

VIRTUAL-RUNTIME_mesa = "mesa"
PREFERRED_PROVIDER_virtual/gpu = "mali-t62x"

PREFERRED_PROVIDER_virtual/egl = "${PREFERRED_PROVIDER_virtual/gpu}" 
PREFERRED_PROVIDER_virtual/libgbm = "${PREFERRED_PROVIDER_virtual/gpu}"
PREFERRED_PROVIDER_virtual/libgles1 = "${PREFERRED_PROVIDER_virtual/gpu}"
PREFERRED_PROVIDER_virtual/libgles2 = "${PREFERRED_PROVIDER_virtual/gpu}"
PREFERRED_PROVIDER_virtual/libopencl = "${PREFERRED_PROVIDER_virtual/gpu}"
PREFERRED_PROVIDER_virtual/libgl = "${VIRTUAL-RUNTIME_mesa}"
PREFERRED_PROVIDER_virtual/mesa = "${VIRTUAL-RUNTIME_mesa}"

XSERVER_append = " \
    ${@bb.utils.contains('MACHINE_FEATURES', 'mali', 'xf86-video-armsoc', '', d)} \
"


FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

KBRANCH = "odroidg12-4.9.y"
KBUILD_DEFCONFIG = "odroidg12_defconfig"

SRCREV = "20d79ab6a52a20842a18dfb63d67cb66004fe0ea"
LINUX_VERSION ?= "4.9.241"

EXTRA_OEMAKE_append = " KBUILD=${B}"
require linux-hardkernel.inc
SRC_URI_append = " file://oe.scc"

KERNEL_EXTRA_FEATURES = ""

do_install_prepend() {
    bbnote "custom kernel_do_install customization"
    cp ${B}/arch/arm64/boot/dts/amlogic/*.dtb ${B}/arch/arm64/boot/dts/
}

COMPATIBLE_MACHINE = "(odroid-n2-hardkernel|odroid-c4-hardkernel|odroid-hc4-hardkernel)"

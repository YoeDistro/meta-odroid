DEFAULTTUNE ?= "aarch64"

require conf/machine/include/arm/arch-armv7ve.inc

TUNEVALID[aarch64] = "Enable instructions for aarch64"

MACHINEOVERRIDES .= "${@bb.utils.contains('TUNE_FEATURES', 'aarch64', ':aarch64', '' ,d)}"

TUNEVALID[ilp32] = "Enable instructions for aarch64 32 bit mode"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'ilp32', ' -mabi=ilp32', '', d)}"
MACHINEOVERRIDES .= "${@bb.utils.contains('TUNE_FEATURES', 'ilp32', ':aarchilp32', '' ,d)}"

# Little Endian base configs
AVAILTUNES += "aarch64 aarch64_be aarch64_ilp32 aarch64_be_ilp32"
ARMPKGARCH_tune-aarch64 ?= "aarch64"
ARMPKGARCH_tune-aarch64_be ?= "aarch64_be"
ARMPKGARCH_tune-aarch64_ilp32 ?= "aarch64_ilp32"
ARMPKGARCH_tune-aarch64_be_ilp32 ?= "aarch64_be_ilp32"
TUNE_FEATURES_tune-aarch64 = "aarch64"
TUNE_FEATURES_tune-aarch64_be = "${TUNE_FEATURES_tune-aarch64} bigendian"
TUNE_FEATURES_tune-aarch64_ilp32 ?= "${TUNE_FEATURES_tune-aarch64} ilp32"
TUNE_FEATURES_tune-aarch64_be_ilp32 ?= "${TUNE_FEATURES_tune-aarch64} bigendian ilp32"
BASE_LIB_tune-aarch64 = "lib64"
BASE_LIB_tune-aarch64_be = "lib64"
BASE_LIB_tune-aarch64_ilp32 = "libilp32"

PACKAGE_EXTRA_ARCHS_tune-aarch64 = "aarch64"
PACKAGE_EXTRA_ARCHS_tune-aarch64_be = "aarch64_be"
PACKAGE_EXTRA_ARCHS_tune-aarch64_ilp32 = "aarch64_ilp32"
PACKAGE_EXTRA_ARCHS_tune-aarch64_be_ilp32 = "aarch64_be_ilp32"

ARMPKGSFX_ENDIAN_64 = "${@bb.utils.contains('TUNE_FEATURES', 'bigendian', '_be', '', d)}"
ARMPKGSFX_ILP32 = "${@bb.utils.contains('TUNE_FEATURES', 'ilp32', '_ilp32', '', d)}"
TUNE_ARCH_64 = "aarch64${ARMPKGSFX_ENDIAN_64}${ARMPKGSFX_ILP32}"
TUNE_PKGARCH_64 = "aarch64${ARMPKGSFX_ENDIAN_64}${ARMPKGSFX_ILP32}"
ABIEXTENSION_64 = "${@bb.utils.contains('TUNE_FEATURES', 'ilp32', 'ilp32', '' ,d)}"
TARGET_FPU_64 = ""

# Duplicated from arch-arm.inc
TUNE_ARCH_32 = "${@bb.utils.contains('TUNE_FEATURES', 'bigendian', 'armeb', 'arm', d)}"
TUNE_PKGARCH_32 = "${ARMPKGARCH}${ARMPKGSFX_THUMB}${ARMPKGSFX_DSP}${ARMPKGSFX_EABI}${ARMPKGSFX_ENDIAN}${ARMPKGSFX_FPU}"
ABIEXTENSION_32 = "eabi"
TARGET_FPU_32 = "${@d.getVar('TUNE_CCARGS_MFLOAT') or 'soft'}"

TUNE_ARCH = "${@bb.utils.contains('TUNE_FEATURES', 'aarch64', '${TUNE_ARCH_64}', '${TUNE_ARCH_32}' ,d)}"
TUNE_PKGARCH = "${@bb.utils.contains('TUNE_FEATURES', 'aarch64', '${TUNE_PKGARCH_64}', '${TUNE_PKGARCH_32}' ,d)}"
ABIEXTENSION = "${@bb.utils.contains('TUNE_FEATURES', 'aarch64', '${ABIEXTENSION_64}', '${ABIEXTENSION_32}' ,d)}"
TARGET_FPU = "${@bb.utils.contains('TUNE_FEATURES', 'aarch64', '${TARGET_FPU_64}', '${TARGET_FPU_32}' ,d)}"

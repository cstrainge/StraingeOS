#!/bin/bash



source ./tools_env.sh



ensure "${DIR_TOOLS_ARCHIVE}"
ensure "${DIR_TOOLS_SRC}"
ensure "${DIR_TOOLS_BUILD}"
ensure "${DIR_TOOLS_OUT}"

download "${BINUTILS_ARCHIVE_PATH}" "${BINUTILS_URI}"
download "${GCC_ARCHIVE_PATH}" "${GCC_URI}"

extract "${BINUTILS_SRC_PATH}" "${BINUTILS_ARCHIVE_PATH}"
extract "${GCC_SRC_PATH}" "${GCC_ARCHIVE_PATH}" "./contrib/download_prerequisites"



configure "${BINUTILS_SRC_PATH}" "${BINUTILS_BUILD_PATH}" \
    --target="${BUILD_TARGET}" \
    --prefix="${DIR_TOOLS_OUT}" \
    --with-sysroot \
    --disable-nls \
    --disable-werror

build "${BINUTILS_BUILD_PATH}"
build "${BINUTILS_BUILD_PATH}" install



configure "${GCC_SRC_PATH}" "${GCC_BUILD_PATH}" \
    --target="${BUILD_TARGET}" \
    --prefix="${DIR_TOOLS_OUT}" \
    --disable-nls \
    --enable-languages=c,c++ \
    --without-headers

build "${GCC_BUILD_PATH}" all-gcc
build "${GCC_BUILD_PATH}" all-target-libgcc
build "${GCC_BUILD_PATH}" install-gcc
build "${GCC_BUILD_PATH}" install-target-libgcc

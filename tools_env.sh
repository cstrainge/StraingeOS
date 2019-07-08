
DIR_TOOLS="${PWD}/tools"

DIR_TOOLS_ARCHIVE="${DIR_TOOLS}/archive"
DIR_TOOLS_SRC="${DIR_TOOLS}/src"
DIR_TOOLS_BUILD="${DIR_TOOLS}/build"
DIR_TOOLS_OUT="${DIR_TOOLS}/out"




BINUTILS_VER="2.32"
BINUTILS_ARCHIVE="binutils-${BINUTILS_VER}.tar.xz"
BINUTILS_ARCHIVE_PATH="${DIR_TOOLS_ARCHIVE}/${BINUTILS_ARCHIVE}"
BINUTILS_URI="https://mirror.leifrogers.com/gnu/binutils/${BINUTILS_ARCHIVE}"
BINUTILS_SRC_PATH="${DIR_TOOLS_SRC}/binutils-${BINUTILS_VER}"
BINUTILS_BUILD_PATH="${DIR_TOOLS_BUILD}/binutils-${BINUTILS_VER}"




GCC_VER="9.1.0"
GCC_ARCHIVE="gcc-${GCC_VER}.tar.xz"
GCC_ARCHIVE_PATH="${DIR_TOOLS_ARCHIVE}/${GCC_ARCHIVE}"
GCC_URI="https://bigsearcher.com/mirrors/gcc/releases/gcc-${GCC_VER}/${GCC_ARCHIVE}"
GCC_SRC_PATH="${DIR_TOOLS_SRC}/gcc-${GCC_VER}"
GCC_BUILD_PATH="${DIR_TOOLS_BUILD}/gcc-${GCC_VER}"




BUILD_TARGET="i686-elf"

TOOLS_AS="${BUILD_TARGET}-as"
TOOLS_LD="${BUILD_TARGET}-ld"
TOOLS_GCC="${BUILD_TARGET}-gcc"
TOOLS_GXX="${BUILD_TARGET}-g++"

export PATH="${DIR_TOOLS_OUT}/bin:${PATH}"




function ensure
{
    local NEW_PATH="$1"

    if [ ! -d "$NEW_PATH" ]
    then
        mkdir -p "$NEW_PATH"
    fi
}


function download
{
    local ARCHIVE_FILE_PATH="$1"
    local URI="$2"

    if [ ! -f "${ARCHIVE_FILE_PATH}" ]
    then
        pushd "${DIR_TOOLS_ARCHIVE}"
        wget "${URI}"
        popd
    fi
}


function extract
{
    local SRC_DIR="$1"
    local ARCHIVE_PATH="$2"
    local POST_CMD="$3"

    if [ ! -d "${SRC_DIR}" ]
    then
        pushd "${DIR_TOOLS_SRC}"

        tar -xvf "${ARCHIVE_PATH}"

        if [ ! -z "$POST_CMD" ]
        then
            cd "$SRC_DIR"
            "${POST_CMD}"
        fi

        popd
    fi
}


function configure
{
    local SRC_DIR="$1"
    shift

    local BUILD_DIR="$1"
    shift

    if [ ! -d "${BUILD_DIR}" ]
    then
        mkdir -p "${BUILD_DIR}"
        pushd "${BUILD_DIR}"

        "${SRC_DIR}/configure" $@

        popd
    fi
}


function build
{
    local BUILD_DIR="$1"
    shift

    pushd "${BUILD_DIR}"

    make $@

    popd
}

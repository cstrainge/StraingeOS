#!/bin/bash



source "./tools_env.sh"




export CXX="$TOOLS_GXX"
export AS="$TOOLS_AS"



echo "Using $TOOLS_AS"
echo "Using $CXX"



rm -rf ./obj
mkdir -p `realpath ./obj`


objList=""



function fail
{
    echo "$1" >&2
    exit 1
}



function assemble
{
    source=`realpath ./src/${1}.s`
    object=`realpath ./obj/${1}.o`

    echo "Assemble $source with $AS"
    objList="$objList $object"

    $AS --32 "$source" -o "$object" || fail "Assemble failed."
}



function compile
{
    source=`realpath ./src/${1}.cpp`
    object=`realpath ./obj/${1}.o`

    echo "Compile $source"
    objList="$objList $object"

    $CXX -ffreestanding \
         -O2 \
         -Wall \
         -Wextra \
         -fno-exceptions \
         -fno-rtti \
         -std=c++11 \
         -m32 \
         -c "${source}" \
         -o "${object}" || fail "Compile failed."
}



function addCrtObject
{
    name="$1.o"

    objFilePath=`$CXX -m32 --print-file-name=$name` || fail "Search failed."

    echo "Found CRT: $objFilePath"
    objList="$objList $objFilePath"
}



function link
{
    echo "Link $kernelPath"

    $CXX -T linker.ld \
         -o $kernelPath \
         -ffreestanding \
         -O2 \
         -nostdlib  \
         -m32 \
         -lgcc \
         $objList || fail "Link failed."
}

         #-melf_i386 \


function checkMultiBoot
{
    if grub-file --is-x86-multiboot2 $kernelPath
    then
        echo "Multi-Boot 2 kernel comfirmed."
    else
        echo "Kernel is not multiboot 2 compliant."
        exit 1
    fi
}



function createIso
{
    echo "Generating StraingeOS.iso"

    cp grub.cfg ${grubDir}/grub.cfg
    grub-mkrescue -o StraingeOS.iso ${stagingDir} 2> /dev/null || fail "Could not create OS .iso"
}


function execute
{
    echo "Starting emulator."
    qemu-system-i386 -cdrom StraingeOS.iso & #|| fail "Could not start emulator."
}




stagingDir=`realpath ./staging`
bootDir="${stagingDir}/boot"
grubDir="${bootDir}/grub"

kernelPath="${bootDir}/kernel"


rm -rf ${stagingDir}/*
mkdir -p ${bootDir} ${grubDir}




assemble      boot

assemble      crti
addCrtObject  crtbegin

compile       string
compile       printing
compile       terminal
compile       multiBoot
compile       kernel

compile       cppSupport

addCrtObject  crtend
assemble      crtn

link

checkMultiBoot

createIso
execute

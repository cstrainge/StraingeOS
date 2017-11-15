#!/bin/bash



TARGET=i686-elf
CC=${TARGET}-gcc
CXX=${TARGET}-g++
AS=${TARGET}-as



rm -rf ./obj
mkdir -p `realpath ./obj`


objList=""



function assemble
{
    source=`realpath ./src/${1}.s`
    object=`realpath ./obj/${1}.o`

    echo "Assemble $source"
    objList="$objList $object"

    $AS "$source" -o "$object"

    if [ ! $? ]
    then
        echo "Assemble failed."
        exit 1
    fi
}



function compile
{
    source=`realpath ./src/${1}.cpp`
    object=`realpath ./obj/${1}.o`

    echo "Compile $source"
    objList="$objList $object"

    $CXX -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -std=c++11 -c "${source}" -o "${object}"

    if [ ! $? ]
    then
        echo "Compile failed."
        exit 1
    fi
}



function appendCrtObject
{
    name="$1.o"

    objFilePath=`$CXX --print-file-name=$name`

    echo "Include CRT file $objFilePath"
    objList="$objList $objFilePath"
}



stagingDir=`realpath ./staging`
bootDir="${stagingDir}/boot"
grubDir="${bootDir}/grub"

kernelPath="${bootDir}/kernel"


rm -rf ${stagingDir}/*
mkdir -p ${bootDir} ${grubDir}



assemble         crti
appendCrtObject  crtbegin

assemble         boot
compile          terminal
compile          kernel

appendCrtObject  crtend
assemble         crtn



echo "Link $kernelPath"

$CXX -T linker.ld -o $kernelPath -ffreestanding -O2 -nostdlib  $objList -lgcc



echo "Checking kernel image."
if grub-file --is-x86-multiboot $kernelPath
then
    echo "Multi-Boot kernel comfirmed."
else
    echo "Kernel is not multiboot."
    exit 1
fi



echo "Building StraingeOS.iso"

cp grub.cfg ${grubDir}/grub.cfg
grub-mkrescue -o StraingeOS.iso ${stagingDir}



echo "Starting emulator."
qemu-system-i386 -cdrom StraingeOS.iso

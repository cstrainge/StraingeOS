#!/bin/bash


rm -rf ./obj
mkdir -p `realpath ./obj`


objList=""



function assemble
{
    source=`realpath ./src/${1}.s`
    object=`realpath ./obj/${1}.s.o`

    echo "Assemble $source"
    objList="$object $objList"

    i686-elf-as "$source" -o "$object"

    if [ ! $? ]
    then
        echo "Assemble failed."
        exit 1
    fi
}



function compile
{
    source=`realpath ./src/${1}.cpp`
    object=`realpath ./obj/${1}.cpp.o`

    echo "Compile $source"
    objList="$object $objList"

    i686-elf-g++ -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -std=c++11 -c "${source}" -o "${object}"

    if [ ! $? ]
    then
        echo "Compile failed."
        exit 1
    fi
}



stagingDir=`realpath ./staging`
bootDir="${stagingDir}/boot"
grubDir="${bootDir}/grub"

kernelPath="${bootDir}/kernel"


rm -rf ${stagingDir}/*
mkdir -p ${bootDir} ${grubDir}


assemble boot
compile terminal
compile kernel




echo "Link $kernelPath"

i686-elf-gcc -T linker.ld -o $kernelPath -ffreestanding -O2 -nostdlib  $objList -lgcc



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

#!/bin/bash

if [ "$1" == "clean" ];
then
    rm -f *.o *.elf *.bin
	exit 0;
fi


trap catch_errors ERR;

function catch_errors()
{
	echo "Script abortado devido a erros";
	exit 0;
}

i686-elf-gcc -std=c99 -g -Os -march=i686 -ffreestanding -Wall -Werror -I. -nostdlib -c -o stage1.o stage1.c
i686-elf-gcc -std=c99 -g -Os -march=i686 -ffreestanding -Wall -Werror -I. -nostdlib -c -o stage2.o stage2.c
i686-elf-gcc -std=c99 -g -Os -march=i686 -ffreestanding -Wall -Werror -I. -nostdlib -c -o floppy.o floppy.c

i686-elf-ld -static -Tstage1.ld -nostdlib -nmagic -o stage1.bin stage1.o -Map=stage1.map
i686-elf-ld -static -Tstage2.ld -nostdlib -nmagic -o stage2.bin stage2.o floppy.o -Map=stage2.map

#gcc -g -Os -march=i686 -ffreestanding -Wall -Werror -I. -static -nostdlib -Wl,-Tstage2.ld -Wl,--nmagic -Wl,--oformat=binary -o stage2.bin stage2.c

#i686-elf-as stage1.S -o stage1.o
#i686-elf-gcc -c -Os -march=i686 -ffreestanding -Wall -Werror fat12.c -o fat12.o
#i686-elf-ld -static -Tstage1.ld -nostdlib -nmagic -o stage1.elf stage1.o fat12.o
#i686-elf-objcopy -O binary stage1.elf stage1.bin

#i686-elf-gcc -c -Os -march=i686 -ffreestanding -Wall -Werror stage2.c -o stage2.o
#i686-elf-ld -static -Tstage2.ld -nostdlib -nmagic -o stage2.elf stage2.o
#i686-elf-objcopy -O binary stage2.elf stage2.bin

if [ -f "floppy.img" ];
then
	fat_imgen -m -s stage1.bin -g -i stage2.bin -f floppy.img
else
	fat_imgen -c -s stage1.bin -g -i stage2.bin -f floppy.img
fi

#-g -i stage2.bin 
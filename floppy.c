/*
floppy.c - 02/06/2014 by osdeving from America-SP, Brazil

* This file is included in stage1.c as a header file
* In stage2 it is a object

*/

#include "boot.h"

// err... 
// this function read sectors from bios_drive starting from lba
// at buffer_offset address.
// ** important **
// buffer_offset + sectors * 512 should be lesser than FFFF, be carefull!
int32 __REGPARM __NOINLINE
read_sectors(word buffer_offset, word lba, byte sectors, byte bios_drive)
{
	typedef struct _2bytes { byte a,b; } _2bytes_t;
	
	// to treat as word or as byte1 and byte2...
	// why not to use char foo[2]; instead this? because casting is ugly :)
	typedef union _ucs {
		word cs;
		_2bytes_t scs;
	} ucs_t;
	
	typedef union _uhb {
		word hb;
		_2bytes_t shb;
	} uhb_t;
		
	ucs_t ucs;
	uhb_t uhb;
	
	// LBACHS algorithm in its most inefficient version :)
	ucs.scs.b = lba / (NUM_HEADS * SECTORS_PER_TRACK);
	word t = lba % (NUM_HEADS * SECTORS_PER_TRACK);
	uhb.shb.b = t / SECTORS_PER_TRACK;
	uhb.shb.a = bios_drive;	
	ucs.scs.a = (t % SECTORS_PER_TRACK) + 1;
	
	
	byte failed = 0;
	
	__ASM(
	"movw $0, %0\n"
	"int $0x13\n"
	"setcb %0"
	: "=m"(failed)
	: "a"(0x0200 | sectors), "c"(ucs.cs), "d"(uhb.hb),
	  "b"(buffer_offset));
	
	// returns 0 if success
	return failed;
}
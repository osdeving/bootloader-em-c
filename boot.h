/*
boot.h - 02/06/2014 by osdeving from America-SP, Brazil

* This include file is used in stage1.c and stage2.c
* Includes only "boot.h" in your C files

*/

#ifndef _BOOT_H_
#define _BOOT_H_


// unlike .code16, .code16gcc works in stack operations too
__asm__ (".code16gcc\n\t");

// gcc related extensions
#define __ASM        __asm__ __volatile__ 
#define __NOINLINE  __attribute__((noinline))
#define __REGPARM   __attribute__ ((regparm(3)))
#define __PACKED    __attribute__((packed))
#define __NORETURN  __attribute__((noreturn))
#define __ALIGN8 __attribute__ ((aligned (8)))
#define __ALIGN4 __attribute__ ((aligned (4)))
#define __ALIGN2 __attribute__ ((aligned (2)))

// this section should appear at start of stage1 (look stage1.ld)
#define __SECTION_BPB   __attribute__((section("bpb")))

// this section comes after
#define __SECTION_START __attribute__((section("start")))

// others headers
#include "types.h"
#include "bpb.h"
#include "fat12.h"

// 9000:0 equals 8840:7C00, right?
// this is good because after of boot relocation to 9000:0
// we can use the same labels! e.g 8840:read_sectors equals 0:read_sectors
#define NEWBOOT_SEGMENT     0x8840
#define NEWBOOT_OFFSET      0x7C00

// the stage2 starts at address 0:500
#define STAGE2_SIZE_IN_SECTORS 4
#define STAGE2_SIZE_IN_BYTES   STAGE2_SIZE_IN_SECTORS*BYTES_PER_SECTORS
#define STAGE2_ADDRESS_OFFSET  0x500
#define STAGE2_ADDRESS_SEGMENT 0
#define STAGE2_FILE_NAME       "STAGE2  BIN"

// the kernel starts at address 0:D00  (above stage1)
// in protected mode, the kernel stats at address 100000 (1MB)
#define KERNEL_ADDRESS_OFFSET  STAGE2_ADDRESS_OFFSET+STAGE2_SIZE_IN_BYTES
#define KERNEL_ADDRESS_SEGMENT 0
#define KERNEL_PMODE_ADDRESS   0x100000
#define KERNEL_FILE_NAME       "KERNEL  BIN"

#endif // _BOOT_H_
 
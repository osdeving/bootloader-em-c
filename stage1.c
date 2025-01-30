/*
stage1.c - 02/06/2014 by osdeving from Americana-SP, Brazil

* Main file for stage1. 
* Loads stage 2 of a floppy disk formatted with FAT12.

*/

#include "boot.h"

// define and initialize BPB
// pay attention, this memory is alocated on section "bpb" (stage1.ld)
// constants for floppy disks 3" 1.44MB and FAT12.
bios_parameter_block_t bios_parameter_block __SECTION_BPB =
{
	.jmpBoot = {0xEB, 0x3C, 0x90},
	.OEMName = {'T','C','K','-','O','S',0,0},
	.bytesPerSect = BYTES_PER_SECTOR,
	.secstsPerClus = SECTORS_PER_CLUSTER,
	.reservedSectsCnt = RESERVED_SECTORS,
	.fatCnt = NUMBER_OF_FATS,
	.rootEntryCnt = ROOT_ENTRIES,
	.sectsCnt16 = NUMBER_OF_SECTORS,
	.media = 0xF0,
	.fatSize16 = SECTORS_PER_FAT,
	.sectsPerTrack = SECTORS_PER_TRACK,
	.headCnt = NUM_HEADS,
	.hiddenSects = 0,
	.sectsCnt32 = 0,
	.driveNum = 0,
	.reserved = 0,
	.bootSig = 0x29,
	.volumeID = 0,
	.volumeLabel = {'N', 'O', ' ', 'N', 'A', 'M', 'E', 0, 0, 0, 0},
	.fileSysType = {'F', 'A', 'T', '1', '2', 0, 0, 0}
};

extern int32 __REGPARM __NOINLINE read_sectors(word, word, byte, byte);

// this function is in section "start", after of section "bpb" (stage1.ld)
void __NORETURN __SECTION_START main()
{
	// boot relocation from 0:7C00 to 9000:0
	__ASM(
	"movw $0x07c0, %ax\n\t"
	"movw %ax, %ds\n\t"
	"movw $0x9000, %ax\n\t"
	"movw %ax, %es\n\t"
	"xorw %si, %si\n\t"
	"xorw %di, %di\n\t"
	"movw $512, %cx\n\t"
	"rep movsb\n\t"
	"jmpl $0x8840, $1f\n\t" // 8840:7C00 equals 9000:0
	"1:\n\t");
	
	// 8840 is for to continue using the offset 7C00
	__ASM(
	"movw %%ax, %%es\n\t"
	"movw %%ax, %%ds\n\t"
	:: "a"(0x8840));
	
	// the BIOS lets the drive number in register DL
	byte bios_drive = 0;
	__ASM("movb %%dl, %0\n\t" : "=r"(bios_drive));
	
	// err... read root dir
	if(read_sectors(ROOT_ADDRESS_OFFSET, ROOT_FIRST_SECTOR, ROOT_SIZE_IN_SECTORS, bios_drive))
		goto error;
	
	root_entry_t *proot_entry = (root_entry_t*)(ROOT_ADDRESS_OFFSET);
	
	// search the 11-bytes file name in each entry of the root directory
	int root_index, name_index;
	for(root_index = 0; root_index < ROOT_ENTRIES; root_index++)
	{
		for(name_index = 0; name_index < 11; name_index++)
			if(proot_entry[root_index].name[name_index] != STAGE2_FILE_NAME[name_index]) 
				break;
		
		if(name_index == 11) break;
	}
	
	// file name not found
	if(root_index >= ROOT_ENTRIES) goto error;
	
	// err... read FAT
	if(read_sectors(FAT_ADDRESS_OFFSET, FAT_FIRST_SECTOR, FAT_SIZE_IN_SECTORS, bios_drive))
		goto error;
	
	// Ok, FAT loaded.
	// Now we want to load stage2 in 0:500 and not 8840:500, right?
	__ASM("movw %%ax, %%es\n\t" :: "a"(0));
	
	// read each cluster of stage2
	word stage2_address_offset = STAGE2_ADDRESS_OFFSET;
	word cluster = proot_entry[root_index].first_cluster_lo;
	while(cluster < 0xFF0)
	{
		// cluster to lba is easy
		word lba = cluster - 2 + DATA_SECTOR;
		
		// read this cluster
		if(read_sectors(stage2_address_offset, lba, SECTORS_PER_CLUSTER, bios_drive))
			goto error;
		
		// copy cluster
		word temp_cluster = cluster;
		
		// next_cluster = VALUE of (cluster + cluster / 2 + FAT_ADDRESS_OFFSET)
		// lba = cluster - 2 + DATA_SECTOR.
		// that is, for next_cluster cluster is a address, for lba cluster is
		// a value.
		cluster = *(word*)((cluster + (cluster >> 1)) + FAT_ADDRESS_OFFSET);
		
		// cluster is a 12-bit value, in this case, if cluster is even, we
		// obtain your high 12-bits, if cluster is odd, we obtain your low 12-bits.
		// it is a little confusing, is not?
		(temp_cluster & 1) ? (cluster >>= 4) : (cluster &= 0xFFF);
		
		// add to next sector...
		stage2_address_offset += BYTES_PER_SECTOR;
	}
	
	// jump to stage2 (0:500)
	__ASM("jmpl $0, $0x500\n\t");
	
// we don't want reach here!
error:
	while(1);
}

// this is because floppy.c as object (floppy.o) is bigger and
// inflates my bootsect :(
#include "floppy.c"

/*
bpb.h - 02/06/2014 by osdeving from America-SP, Brazil

*/

#ifndef _BPB_H_
#define _BPB_H_

#define BYTES_PER_SECTOR    512
#define SECTORS_PER_CLUSTER 1
#define RESERVED_SECTORS    1
#define NUMBER_OF_FATS      2
#define ROOT_ENTRIES        224
#define NUMBER_OF_SECTORS   2880
#define SECTORS_PER_FAT     9
#define SECTORS_PER_TRACK   18
#define NUM_HEADS           2

typedef struct __PACKED _bios_parameter_block
{
	byte jmpBoot[3];
	byte OEMName[8];
	word bytesPerSect;
	byte secstsPerClus;
	word reservedSectsCnt;
	byte fatCnt;
	word rootEntryCnt;
	word sectsCnt16;
	byte media;
	word fatSize16;
	word sectsPerTrack;
	word headCnt;
	dword hiddenSects;
	dword sectsCnt32;
	byte driveNum;
	byte reserved;	
	byte bootSig;
	dword volumeID;
	byte volumeLabel[11];
	byte fileSysType[8];
} bios_parameter_block_t;

#endif // _BPB_H_
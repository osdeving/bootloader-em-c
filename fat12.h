/*
fat12.h - 02/06/2014 by osdeving from America-SP, Brazil

*/

#ifndef _FAT12_H_
#define _FAT12_H_

typedef struct __PACKED _root_entry
{
	byte name[11];
	byte attr;
	byte reserved;
	byte time_tenth;
	word time;
	word date;
	word last_access;
	word first_cluster_hi;
	word write_time;
	word write_date;
	word first_cluster_lo;
	dword file_size;
} root_entry_t;

#define ROOT_SIZE_IN_SECTORS   (32*ROOT_ENTRIES)/BYTES_PER_SECTOR
#define ROOT_SIZE_IN_BYTES     ROOT_SIZE_IN_SECTORS*BYTES_PER_SECTOR
#define ROOT_FIRST_SECTOR      RESERVED_SECTORS+(NUMBER_OF_FATS*SECTORS_PER_FAT)
#define ROOT_ADDRESS_OFFSET    NEWBOOT_OFFSET+BYTES_PER_SECTOR
#define ROOT_ADDRESS_SEGMENT   NEWBOOT_SEGMENT
#define FAT_SIZE_IN_SECTORS    SECTORS_PER_FAT
#define FAT_SIZE_IN_BYTES      FAT_SIZE_IN_SECTORS*BYTES_PER_SECTOR
#define FAT_FIRST_SECTOR       RESERVED_SECTORS
#define FAT_ADDRESS_OFFSET     ROOT_ADDRESS_OFFSET+ROOT_SIZE_IN_BYTES
#define FAT_ADDRESS_SEGMENT    NEWBOOT_SEGMENT

#define DATA_SECTOR            RESERVED_SECTORS + NUMBER_OF_FATS *SECTORS_PER_FAT + ROOT_SIZE_IN_SECTORS

#endif // _FAT12_H_
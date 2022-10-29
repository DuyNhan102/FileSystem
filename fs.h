#ifndef FS_H
#define FS_H
/* Prevent multiple inclusion */

/* fs.h
 * Various definitions for OSP Practical Case Study E
 */
 
/* The bitmap */
extern unsigned char bitmap[8];
/* 320Kb disk with 4Kb blocks -> 8 bytes for bitmap
 */
 
/* The directory entry */
struct entry {
	char user;
	char name[9];
	char extension[4];
	short blockcount;
	short block[8];
};

/* The directory */
extern struct entry directory[128];

/* extern means its defined in another file, prevents multiple definition errors */

int toggle_bit(int block);
/* Toggles the value of the bit 'block', in the external array 'bitmap'.
 * Returns the current value of the bit Does NOT validate 'block'!!! 
 */
 
int block_status(int block);
/* Returns the status of 'block', in the external array bitmap returns
 * 0 if bitmap bit is 0, not 0 if bitmap bit is 1. Does NOT validate block!!!
 */
 
#endif


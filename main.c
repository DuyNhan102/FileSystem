/*Author: Duy Nhan Ta
  Operating System Programing 
  1PM Friday
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"


//write file roi moi read file 6 5
/* Initialize the disk*/
void createDisk() {	
	memset(&bitmap[0], 0, sizeof(bitmap));
	memset(&directory[0], 0, sizeof(directory));
	printf("---Disk has been sucessfully Created!---\n");
}

/* This function will list out Filename, File extension and Block Count */
void listDirectory() {
	int i;
	
	printf("%-30s%-15s%15s\n", "Filename", "File Extension", "Block Count");
	
	for(i = 0; i < 128; i++) {
		if(strcmp(directory[i].name, "") != 0) {
			printf("%-30s%-15s%15dKb\n", directory[i].name, directory[i].extension, directory[i].blockcount);
		}
	}
}

/* Print the value of each of the bits in the bitmap */
void bitmapDisplay() {
	int i, j;
	for(i = 0; i < 8; i++) { // 
		for(j = 0; j < 8; j++) {
			if(block_status(i * 8 + j) == 0) // if the block status is 0
				printf("0");
			else
				printf("1");
		}
		
		printf("\n");
	}
}

/* Open the file, if new then it is created and added to the directory */
int open_file(char *filename, char *extension) {
	int i;
	
	/* Find the exist file in the directory and return position  */
	for(i = 0; i < 128; i++){
		if(strcmp(directory[i].name, filename) == 0 && strcmp(directory[i].extension, extension) == 0)
			return i;
	}
	/* ADD new file to directory If couldnt find the exits one */
	for(i = 0; i < 128; i++) {
		if(strcmp(directory[i].name, "") == 0) {
			directory[i].user = 1;
			strcat(directory[i].name, filename);
			strcat(directory[i].extension, extension);
			return -1;
		}
	}
	printf("There is some error here!");
	exit(0);
}

int main(int argc, char *argv[]) {
	int i;
	int choice;
	int filePosition = -1;
	int writeBit;
	
	char filename[9];
	char extension[4];
	
	do{
		printf("1. Initialise Disk\n");
		printf("2. List Files in the Directory\n");
		printf("3. Display the Free Bitmap\n");
		printf("4. Open/Create File\n");
		printf("5. Read File\n");
		printf("6. Write File\n");
		printf("7. Delete File\n");
		printf("0. Quit\n");

		printf("YOUR CHOICE: ");
		scanf("%d", &choice); 

		switch (choice)
		{
		
		case 1: 
			createDisk();
			break;
		case 2:
			listDirectory();
			break;
		case 3:
			bitmapDisplay();
			break;
		case 4:
			printf("Input filename <space> extension: ");
			scanf("%s %s", filename, extension);

			filePosition = open_file(filename, extension); 
			
			if(filePosition == -1) {
				printf("New file has been created.\n");
				filePosition = open_file(filename, extension); /* Re-execute open file to get the position */
			} else {
				printf("Existing file has opened.\n");
			}
			break;
		case 5:
			/* List the blocks occupied by the currently opened file. */
			if(filePosition == -1) {
				printf("No opened file.\n");
			} else {
				for(i = 0; i < 8; i++)
					printf("%d ", directory[filePosition].block[i]);
				
				printf("\n");
			}
			break;
		case 6:
			/* Allocate another block to the currently opened file when writing to file */
			if(filePosition == -1) {
				printf("No opened file.\n");
			} else {
				/* We find which bit position we going to start writing */
				/* 8 x 8 = (Size of bitmap) x (8 bits) */
				for(i = 0; i < 8 * 8; i++) {
					if(block_status(i) == 0) {
						toggle_bit(i);
						writeBit = i;
						break;
					}
				}
				
				directory[filePosition].block[directory[filePosition].blockcount] = writeBit;
				directory[filePosition].blockcount++;
			}
			break;
		case 7:
			/* Deallocate all blocks for the current file in the bitmap and marked as free */
			if(filePosition == -1) {
				printf("No opened file.\n");
			} else {
				/* Zero out the used bits */
				for(i = 0; i < directory[filePosition].blockcount; i++)
				toggle_bit(directory[filePosition].block[i]);

				memset(&directory[filePosition].block, 0, sizeof(directory[filePosition].block));
				memset(&directory[filePosition].name, 0, sizeof(char) * 9);
				memset(&directory[filePosition].extension, 0, sizeof(char) * 4);

				directory[filePosition].blockcount = 0;
				filePosition = -1;
			}
			break;
		default:
			break;
		}
	}
	while (choice !=0);
	return 0;
}

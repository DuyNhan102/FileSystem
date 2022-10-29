# Simulation of File System!
This repo is a simulation of File System in C Language.

When your program starts, it will assume that the disk is unformatted, you should provide a menu that implements
the following options:

-Initialise Disk: initialise disk control structures, setting the blocks allocated for the bitmap to used, and marking
all directory entries as being available.

-List Files: in the Directory List the names, extensions and block counts of all the valid files in the directory.
Display the Free Bitmap print the value of each of the bits in the bitmap. This need not be pretty, just a long list
of 1’s and 0’s is sufficient

-Open/Create File: scans the directory and if the name provided doesn’t exist then adds that file to the directory.
This file will must be used in all subsequent operations until a new file is open/created or it is deleted.
Read File list the blocks occupied by the currently open file (not the content of these blocks as you don’t store
this information)

-Write File: allocate another block to the currently open file. You should not preallocate blocks for the file, you
should allocate the first available block, by scanning the bitmap for the first block that is available. Each
write shall add another block to the file until there are no more slots to allocate blocks to, or the disk runs
out of blocks. (There are only 24 slots available for each file.)

-Delete File: deallocate all blocks for the current file in the bitmap, and marks as free the directory entry for that
file

To run the file system, run in the terminal the following commands: 
   "make"

# Allocating-Disk-Space
1. Create an array to simulate sectors on a storage device
2. Each element of the array is 500 bytes units in size.
3. Create an array that tracks where all of the data items are stored.
4. Give user the options to:
5. Ask user to enter the file name (filename can be 1 character).
6. Ask users to enter the size of the file (allow integers 1- 3300 bytes)
7. Find a location for the data item, preferably in contiguous position.
8. If cannot find contiguous slots, break the file up into non-contiguous slots.
9. Try to start loading a file from location 0 up towards location 99

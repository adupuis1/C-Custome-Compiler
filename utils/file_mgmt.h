#ifndef FILE_MGMT_H
#define FILE_MGMT_H


#include <stdio.h>
#include <stdlib.h>

//      FILE HANDLING
int sizeOfFile(FILE *file);
char* toArray(FILE *file, int filesize);
char* quicToArray(FILE *file);
char* fileToBuffer(const char *filename);


#endif

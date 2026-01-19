#ifndef FILE_MGMT_H
#define FILE_MGMT_H


#include <stdio.h>
#include <stdlib.h>

//      FILE HANDLING
void setFile(char * fileName);
FILE* getFile();
int sizeOfFile();
char* toArray(FILE *file, int filesize);
char* quicToArray(FILE *file);
char* fileToBuffer();


#endif

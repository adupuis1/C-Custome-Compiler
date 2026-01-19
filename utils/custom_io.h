#ifndef CUSTOM_IO_H
#define CUSTOM_IO_H

#include <stdio.h>
#include <string.h>


//MACROS 
#define BLUE "\033[0;34m"
#define RED "\033[0;31m"
#define DEFAULT "\033[0m"


//      CUSTOM PRINT STATEMENTS
void printline(int length);
void header(const char *text);
void message(const char *custom_message, int blue);
void customError(const char *custom_message);
void printloc(int pos, int line);
void blueText(char * text);
void blueInt(int num);
#endif

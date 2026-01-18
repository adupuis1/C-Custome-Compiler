#include "lexer_config.h"
#include <string.h>


// 1. Define the array locally in this file
static const char* KEYWORDS[] = {"int", "string", "file", "print"};

// 2. Use your #define here! It works perfectly in this scope.
#define NUM_OF_KEYWORDS (sizeof(KEYWORDS) / sizeof(KEYWORDS[0]))

bool isoperator(char c){

        return strchr("+-/!=&<>|%.", c) != NULL;
}

bool iskeyword(char * word){
        for(int i = 0; i < NUM_OF_KEYWORDS; i++){
		if(strcmp(word, KEYWORDS[i]) == 0){
                        return true;
                }
        }
        return false;
}


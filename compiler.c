#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils/custom_io.h"
#include "utils/file_mgmt.h"
#include "utils/lexer_config.h"
#include "utils/parser.h"
//------------------------------------------
//PROTOTYPES
//------------------------------------------
//	TOKENIZER
void tokenizer(char *input);
void PROCESS_wordToken(int ppos, int line, char *word);
bool isoperator(char c);


//MAIN
int main(){
	
	
	header("COMPILER made by Anatole Dupuis");
	setFile("files/input.txt");
	tokenize();
	start_parsing();
	
	return 0;
}



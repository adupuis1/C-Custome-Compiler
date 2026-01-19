#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils/custom_io.h"
#include "utils/file_mgmt.h"
#include "utils/lexer_config.h"

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
	newEmptyTokenList();	
	char *charStream = fileToBuffer();
	if(charStream != NULL){
		message("SUCCESS", 0);
		message("char stream created", 1);
		//printf("%s", charStream);
		tokenizer(charStream);
		
	} else {
		customError("failed\n");
	}
	

	return 0;
}

//FUNCTIONS
//	TOKENIZATION
//
void PROCESS_wordToken(int ppos, int line, char *word){
	if(iskeyword(word)){
		
		add_token(ppos, KEYWORD, line, word);

		
	} else {
		add_token(ppos, KEYWORD, line, word);
        	
		
	}
}

void tokenizer(char *input){

	int pos = 0;
	int line = 1;
	int ppos =0;
	int start;
	int length;
	header("STARTING TOKENIZATION");
	while(input[pos] != '\0'){
		char current = input[pos]; //why no pointer (char *current)!!
		start = pos;
		length = 0;
		if(current == '\n'){
			line++;
			pos++;
			continue;
		}

		if(isspace(current)){
			pos++;
			continue;
		}

		if(isdigit(current)){
			
			while(isdigit(input[pos])){
				pos++;
			}
			length = pos - start;
			char *numString = malloc(length + 1);
			strncpy(numString, &input[start], length);
			numString[length] = '\0';
			int val = atoi(numString);
			printf("INT_LITERAL: ", val);
//void add_intToken(int pos, TokenType type, char* lexeme, int line, int value);
			add_intToken(ppos, LITERAL_INT, numString, line, val);
			ppos += 1;
			free(numString);
			continue;
		}
//			1. starts with a char
		if(isalpha(current)){
			

//			2. if is a num or char pos++
			while(isalpha(input[pos]) || input[pos] == '_'){
				pos++;
			}
//			3. calculate length
			length = pos - start;

//			4. extract word
			char *word = malloc(length+1);
			strncpy(word, &input[start], length);
			word[length] = '\0';

			if(strncmp(word,"EOF",length) == 0){
				printf("%s\n", word);
				free(word);
				break;
			}
			// we must check if word is either
			//		 identifier: User-defined names given to program elements like variables, functions, classes, etc. (e.g., age, calculateSum)
			//		 keyword: Reserved words with predefined, special meanings in the programming language (e.g., if, while, return, class). 	
			if(iskeyword(word)){
				add_token(ppos, KEYWORD, line, word);
			} else{
				add_token(ppos, IDENTIFIER, line, word);

			}
			ppos += 1;
			free(word);
			continue;
		}
		if(isoperator(current)){
			while(isoperator(input[pos])){
				pos++;
			}
			length = pos - start;
			char *operator = malloc(length+1);
			strncpy(operator, &input[start], length);
			operator[length] = '\0';
			add_token(ppos, OPERATOR, line, operator);
			free(operator);
			continue;

		}
		if(current == '@'){
			printf("PUNCTUATOR: @	");
			printloc(pos, line);
			pos++;
			continue;
		}
		if(current == '{'){
			printf("PUNCTUATOR: {	");
			printloc(pos, line);
			pos++;
			continue;	
		}
	        if(current == '"'){
			
			pos++;
			start = pos;
			while(input[pos] != '"'){
				pos++;
			}
			length = (pos) - start;
			char *stringLiteral = malloc(length+1);
			strncpy(stringLiteral, &input[start], length);
			stringLiteral[length] = '\0';
			add_token(ppos, LITERAL_STRING, line, stringLiteral);
			free(stringLiteral);
			pos++;
			continue;
		}
		if(current == '#'){
			if(input[pos+1] != NULL && input[pos+1] == '#'){
				pos++;
				start = pos+1;
				while(input[pos] != '\n'){
					pos++;	
				}
				length = pos - start;
				char *comment = malloc(length+1);
				strncpy(comment, &input[start], length);
				comment[length] = '\0';
				printf("COMMENT: %s	", comment);
				printloc(pos, line);
				free(comment);
				continue;
			}
		}
		if(current == ';'){
			printf("PUNCTUATOR: ;	");
			printloc(pos, line);
			pos++;
			continue;
		}	
		if(current == '}'){
			printf("PUNCTUATOR: }	");
			printloc(pos, line);
			pos++;
			continue;
		}
		if(current == '('){
			printf("PUNCTUATOR: (	");
			printloc(pos, line);
                        pos++;
                        continue;

		}
		if(current == ')'){
                        printf("PUNCTUATOR: )	");
			printloc(pos, line);
                        pos++;
                        continue;

                }
	
		else {
			pos++;
			printf("undefined	");
			printloc(pos, line);
			continue;
		}
	}
	header("finished tokenization");
}



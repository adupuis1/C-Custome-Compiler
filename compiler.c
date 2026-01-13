#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils/custom_io.h"
#include "utils/file_mgmt.h"


typedef enum {
	Digit,
	Letter,
	Operator,
	Punctuation,
	endOfFile
} tokenType;

typedef struct {
	/*lexeme: actaul characters: e.g tokenType: Digit, lexeme: 566 */
	char *lexeme;
	tokenType type;
	int line;

} Token;

typedef struct {
	Token *tokens;	//token array
	int count;	//amount of tokens
	int capacity; //memory allocated
} TokenList;

//------------------------------------------
//PROTOTYPES
//------------------------------------------
//	TOKENIZER
void tokenizer(char *input);
void PROCESS_wordToken(char *word);

//MAIN
int main(){

	header("COMPILER made by Anatole Dupuis");

	char *charStream = fileToBuffer("input.txt");
	if(charStream != NULL){
		message("SUCCESS", 0);
		message("char stream created", 1);
		//printf("%s", charStream);
		tokenizer(charStream);
		
	} else {
		customError("failed");
	}
	

	return 0;
}

//FUNCTIONS
//	TOKENIZATION
void tokenizer(char *input){
	int pos = 0;
	int line = 1;

	header("STARTING TOKENIZATION");
	while(input[pos] != '\0'){
		char current = input[pos]; //why no pointer (char *current)!!
		char lookAhead = input[pos+1];
	
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
			pos++;
			message("integer found", 0);
			continue;
		}
//			1. starts with a char
		if(isalpha(current)){
			int start = pos;

//			2. if is a num or char pos++
			while(isalpha(input[pos])){
				pos++;
			}
//			3. calculate length
			int length = pos - start;

//			4. extract word
			char *word = malloc(length+1);
			strncpy(word, &input[start], length);
			word[length] = '\0';

			PROCESS_wordToken(word);
			free(word);
			continue;
		}	
		else {
			pos++;
			message("undefined", 1);
			continue;
		}
	}
	message("finished tokenization", 1);
}





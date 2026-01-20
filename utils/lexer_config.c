#include "lexer_config.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "file_mgmt.h"

// 1. Define the array locally in this file
static const char* KEYWORDS[] = {"int", "string", "file", "print"};


// 2. Use your #define here! It works perfectly in this scope.
#define NUM_OF_KEYWORDS (sizeof(KEYWORDS) / sizeof(KEYWORDS[0]))


// global current TokenList
TokenList* currentTokenList = NULL;
char * charStream_tokenList = NULL;

void print_Token(Token * token){
	
	char * type = "no type";

	switch(token->type){
		case LITERAL_INT:
                        type = "LITERAL_INT";
			break;
		case OPERATOR:
                        type = "OPERATOR";
			break;
		case KEYWORD:
			type = "KEYWORD";
			break;
		case IDENTIFIER:
                        type = "IDENTIFIER";
			break;
		case LITERAL_STRING:
			type = "LITERAL_STRING";
			break;
		case PUNCTUATOR:
                        type = "PUNCTUATOR";
			break;
		case TOKEN_EOF:
                        type = "TOKEN_EOF";
			break;
		default:
			type = "UNKNOWN_TYPE";
			break;
			

	}
	printf("%s:    ", type);
	blueText(token->data.string_val);
	printf("	|	");
	printloc(token->pos, token->line);
	printf("\n");
	
}

bool isoperator(char c){

        return strchr("+-/!=&<>|%.", c) != NULL;
}


bool ispunctuator(char c){

	return strchr(";@{}()", c) != NULL;
}
bool iskeyword(char * word){
        for(int i = 0; i < NUM_OF_KEYWORDS; i++){
		if(strcmp(word, KEYWORDS[i]) == 0){
                        return true;
                }
        }
        return false;
}

void setCurrentList(TokenList * newTokenList){
	currentTokenList = newTokenList;
}

void newEmptyTokenList(){

	
	TokenList * empty_list =  malloc(sizeof(TokenList));
	empty_list->capacity = sizeOfFile();
	empty_list->tokens = (Token*)malloc(sizeof(Token) * empty_list->capacity);
	empty_list->count = 0;
	setCurrentList(empty_list);
	
	
	
}

void add_intToken(int pos, TokenType type, char* lexeme, int line, int value){

	if(currentTokenList == NULL){
		customError("empty token list...");
		return;
	}
	
	Token * newToken = &currentTokenList->tokens[pos];
	newToken->type = type;
	newToken->lexeme = strdup(lexeme);
	newToken->line = line;
	newToken->pos = pos;
	newToken->data.int_val = value;
	newToken->data.string_val = newToken->lexeme;
	currentTokenList->count += 1;
	print_Token(newToken);


}

void add_token(int pos, TokenType type, int line, char * value){

	if(currentTokenList == NULL){
		customError("empty token list...");
                return;
        }
        Token * newToken = &currentTokenList->tokens[pos];
        newToken->type = type;
        newToken->lexeme = value;
        newToken->line = line;
        newToken->pos = pos;
        newToken->data.string_val = value;
        currentTokenList->count += 1;
	print_Token(newToken);

}

//FUNCTIONS
//	TOKENIZATION
//
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
			ppos ++;
			continue;

		}
 		if(ispunctuator(current)){
                        char * punctuator = malloc(3);
                        punctuator[0] = current;
                        punctuator[1] = '\0';
                        add_token(ppos, PUNCTUATOR, line, punctuator);
                        free(punctuator);
                        ppos++;
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

		else {
			pos++;
			printf("undefined	");
			printloc(pos, line);
			continue;
		}
	}
	header("finished tokenization");
}


void tokenize(){
	newEmptyTokenList();
        charStream_tokenList = fileToBuffer();
	if(charStream_tokenList != NULL){
                message("SUCCESS", 0);
                message("char stream created", 1);
                //printf("%s", charStream);
                tokenizer(charStream_tokenList);

        } else {
                customError("failed\n");
        }

}

	






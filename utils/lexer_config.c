#include "lexer_config.h"
#include <string.h>
#include <stdlib.h>
#include "file_mgmt.h"

// 1. Define the array locally in this file
static const char* KEYWORDS[] = {"int", "string", "file", "print"};


// 2. Use your #define here! It works perfectly in this scope.
#define NUM_OF_KEYWORDS (sizeof(KEYWORDS) / sizeof(KEYWORDS[0]))


// global current TokenList
TokenList* currentTokenList = NULL;

void print_intToken(Token * token){
	printf("LITERAL_INT:    ");
        blueInt(token->data.int_val);
        printf("        |       ");
	printloc(token->pos, token->line);
	printf("\n");
       
	
}
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
	print_intToken(newToken);


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




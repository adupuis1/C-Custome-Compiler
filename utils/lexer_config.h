#ifndef LEXER_CONFIG_H
#define LEXER_CONFIG_H

#include <stdbool.h>
#include <stdio.h>

// 1. Define the types of tokens your language has
typedef enum {
    OPERATOR,
    KEYWORD,
    IDENTIFIER,
    LITERAL_STRING,
    PUNCTUATOR,
    LITERAL_INT,
    TOKEN_EOF
    // Add more here...
} TokenType;

// 2. Define what a single Token looks like
typedef struct {
    TokenType type;
    char* lexeme;  // The actual text (e.g., "123" or "variable_name")
    int line;      // Useful for error messages!
    int pos;		//position
    union {
    	    char* string_val;
	    int int_val;
	    double f_value;

    } data;
} Token;

// 3. Define the list structure you just made
typedef struct {
    Token *tokens;
    int count;
    int capacity;
} TokenList;

TokenList* get_token_list();
void print_Token(Token * token);

bool isoperator(char c);
bool ispunctuator(char c);
bool iskeyword(char *word);


void newEmptyTokenList();
void setCurrentList(TokenList * newTokenList);

void add_intToken(int pos, TokenType type, char* lexeme, int line, int value);
void add_token(int pos, TokenType type, int line, char * value);

void tokenizer(char * input);
void tokenize();

#endif

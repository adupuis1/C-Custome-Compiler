#include "parser.h"
#include <stdlib.h>
#include "lexer_config.h"


static int current = 0;
static TokenList* local_token_list = NULL;
ASTNode* root = NULL;
void start_parsing(){


	local_token_list = get_token_list();
	if(local_token_list == NULL){
		printf("failed to import token list");
		return;
	}
	if(strcmp(peek()->lexeme, "CODE") == 0){
		advance();
		root = parse_block();
	}
	
		
}

Token* peek() {
	if (current >= local_token_list->count) {
		return &local_token_list->tokens[local_token_list->count - 1]; //return EOF Token
	}
	return &local_token_list->tokens[current];
}
Token* advance(){
	Token* t = peek();
	current++;
	return t;
}
Token* consume(TokenType expected_type, char* expected_lexeme){	
	
	Token * t = peek();
	if(t->type == expected_type && strcmp(t->lexeme, expected_lexeme)){
		printf("consumed: %s\n", expected_type);
		return advance();
	}
	printf("Syntax error on line %d: Expected '%s' but found '%s'\n", t->line, expected_lexeme, t->lexeme);
	exit(1);
}


ASTNode* createNode(int node_type, Token* t, ASTNode* left, ASTNode* right){


	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = node_type;
	node->token = t;
	node->left = left;
	node->right = right;
	return node;

}

ASTNode* parse_literal(){
	Token*t = peek();
	
	return t;
}
ASTNode* parse_statement(){
	Token* t = peek();

	if(t->type == IDENTIFIER){
		consume(IDENTIFIER, "@");
		
	}
}
ASTNode* parse_block(){
	consume(PUNCTUATOR, "{");
	ASTNode * head = NULL;
	ASTNode* tail = NULL;

	while(strcmp(peek()->lexeme, "}")){
		ASTNode * stmt = parse_statement();
		
		if(stmt == NULL) continue;
		if(head == NULL) {

			head = stmt;
			tail = stmt;
		} else {
			tail->right = stmt;
			tail = stmt;
		}
	}

	consume(PUNCTUATOR, "}");			
	return head;
}

#ifndef PARSER_H
#define PARSER_H


#include <stdio.h>
#include "lexer_config.h"



typedef struct ASTNode {
	enum {
		NODE_PROGRAM,      // The root of the whole file
    		NODE_BLOCK,
		NODE_ASSIGNMENT,   // x = 5
    		NODE_BINARY_EXPR,  // 5 + 10
    		NODE_FUNCTION_DECL,// void main() { ... }
   		NODE_VAR_DECL,     // int x;
    		NODE_LITERAL,       // Just a raw number
		NODE_IDENTIFIER,
		NODE_FUNC_CALL,


		//----TYPES FOR DB------
		NODE_CMD_NEW, //NEW
		NODE_CMD_USE, //USE
		NODE_CMD_ADD, //ADD
		NODE_CMD_REMOVE, //REMOVE
		NODE_CMD_GET,
		NODE_CMD_FIND,
		NODE_SCHEMA_DEF, // {Int: id,...}
		NODE_DATA_ENTRY // {"Bob", 26}
		
 	}type;
	struct ASTNode *right;
	struct ASTNode *left;

	Token* token;

} ASTNode;

void start_parsing();
Token * peek();
Token* advance();
Token* consume(TokenType expected_type, char* expected_lexeme);
ASTNode* createNode(int node_type, Token* t, ASTNode* left, ASTNode* right);

ASTNode* parse_literal();
ASTNode* parse_block();

ASTNode* parse_new();
ASTNode* parse_use(); 
ASTNode* parse_add();

ASTNode* parse_statement();

#endif

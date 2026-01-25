#ifndef PARSER_H
#define PARSER_H


#include <stdio.h>




typedef struct ASTNode {
	enum {
		NODE_PROGRAM,      // The root of the whole file
    		NODE_ASSIGNMENT,   // x = 5
    		NODE_BINARY_EXPR,  // 5 + 10
    		NODE_FUNCTION_DECL,// void main() { ... }
   		NODE_VAR_DECL,     // int x;
    		NODE_LITERAL       // Just a raw number} type;
 	}type;
	struct ASTNode *right;
	struct ASTNode *left;

	union {
		int int_val;
		char* op;
		char* id_name;
	} data;

} ASTNode;

#endif

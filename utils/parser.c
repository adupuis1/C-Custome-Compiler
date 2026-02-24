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
ASTNode* parse_new() {
	Token* t = peek(); //DB or TABLE
	
	//consume the type and make it the token of the node
	Token* typeToken = advance();
		
	//the next token is the name e.g: db1/ users
	//we treat the Name as the 'left' child 
	Token* nameToken = peek();
	ASTNode* nameNode = createNode(NODE_IDENTIFIER, nameToken, nameNode, NULL);
	advance();
	ASTNode* newNode = createNode(NODE_CMD_NEW, typeToken, nameNode, NULL);

	//if its a table we also look for the schema block {}
	if(strcmp(typeToken->lexeme, "TABLE") == 0) {
		if(strcmp(peek()->lexeme, "{") == 0){
		//we can reuse parse_block or write a specific shcema parser
		//for now, attache the shcma block the Name's left
		//may just rely on executer to handle the next block.
		// lets parse the block explicitly
		nameNode->left = parse_block();
		}
	}
	 
	consume(PUNCTUATOR, ";");
	return newNode;

}

ASTNode* parse_use(){
	Token* nameToken = peek();
	ASTNode* nameNode = createNode(NODE_IDENTIFIER, nameToken, NULL, NULL);
	advance();
	consume(PUNCTUATOR, ";");
	return createNode(NODE_CMD_USE, NULL, nameNode, NULL);
}

ASTNode* parse_add(){	

	consume(KEYWORD, "NEW");
	ASTNode* dataBlock = NULL;
	if (strcmp(peek()->lexeme, "{") == 0) {
		//we treat data entry {"Bob", ...} as a block or specifgic node
		//for now, jsut parse block.
		dataBlock = parse_block();
	} else {
		printf("Syntax Error");
		exit(1);
	}
	consume(PUNCTUATOR, ";");
	return createNode(NODE_CMD_ADD, NULL, dataBlock, NULL);
}




ASTNode* parse_statement(){
	Token* t = peek();

    // 1. Check for NEW
    if(strcmp(t->lexeme, "NEW") == 0){
        advance();
        return parse_new();
    }
    // 2. Check for USE
    if(strcmp(t->lexeme, "USE") == 0){
        advance();
        return parse_use();
    }
    // 3. Check for ADD
    if(strcmp(t->lexeme, "ADD") == 0){
        advance();
        return parse_add();
    }
    // 4. Check for GET
    if(strcmp(t->lexeme, "GET") == 0){
        advance();
        // Simplified for now: GET id = 1;
        // logic to parse condition...
        while(strcmp(peek()->lexeme, ";") != 0) advance();
        consume(PUNCTUATOR, ";");
        return createNode(NODE_CMD_GET, t, NULL, NULL); // t is "GET"
    }

	// [PRESERVED] Your original test logic
	if(t->type == IDENTIFIER){
        // Only consume @ if it's actually there, otherwise it might be a variable name
        if (strcmp(t->lexeme, "@") == 0) { 
		    consume(IDENTIFIER, "@");
        }
        // If it's just an identifier (like in a list), we might return it as a node
        ASTNode* node = createNode(NODE_IDENTIFIER, t, NULL, NULL);
        advance();
        return node;
	}
    
    // [PRESERVED] Handle literals
    if (t->type == LITERAL_INT || t->type == LITERAL_STRING) {
        ASTNode* node = createNode(NODE_LITERAL, t, NULL, NULL);
        advance();
        return node;
    }
    
    return NULL;
}

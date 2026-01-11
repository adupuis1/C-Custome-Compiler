#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//MACROS 
#define BLUE "\033[0;34m"
#define RED "\033[0;31m"
#define DEFAULT "\033[0m"


//STRUCTS
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
//	CUSTOM PRINT STATEMENTS
void printline(int length);
void header(const char *text);
void message(const char *custom_message, int blue);
void customError(const char *custom_message);
//	FILE HANDLING
int sizeOfFile(FILE *file);
char* toArray(FILE *file, int filesize);
char* quicToArray(FILE *file);
char* fileToBuffer(const char *filename);
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

//	CUSTOM PRINTS     ---MOVE TO ANOTHER FILE---
//		printline
void printline(int length){
	printf("\n");
	for(int i = 0; i<length; i++){
		printf("-");
	}
	printf("\n");
}

//		custome header
void header(const char *text){
	int length = strlen(text);
	printline(length+12);
	printf("      %s", text);
	printline(length+12);
}
//		custom message
void message(const char *custom_message, int blue){
	if(blue == 0){
		printf("\n%s%s%s\n", BLUE, custom_message, DEFAULT);
	} else {
		printf("%s\n", custom_message);
	}
}

//		custom error, const = Read-Only char
void customError(const char *custom_message){
			//print errors to stderr
			//"fprintf" = file print format. lets you choose exactly
			//	where the error goes
			//	in this case, to stderr
			//"stderr", unbuffered output stream reserved for errors, prints directly
	fprintf(stderr, "%sERROR: %s%s", RED, custom_message, DEFAULT);
}

//FILE FUNCTIONS
//	GET FILE SIZE
int sizeOfFile(FILE *file){
	if(file == NULL) return 0;

	//	1. move to very last byte in file
	fseek(file, 0L, SEEK_END);

	//	2. check the postion ftell(file): how many bytes away from start
	int size = (int)ftell(file);

	//	3. reset cursor to start of file so other functions like fread  can read it
	rewind(file);
	return size;
}
//	CREATE AN ARRAY SIZE OF FILESIZE
char* toArray(FILE *file, int fileSize){

	// alocate fileSize+1 for the null terminator
	char *buffer = (char *)malloc(fileSize+1);
	if(buffer == NULL){
		customError("memory allocation failed");
		return NULL;		
	}

	//fread reads the specific number of bytes in one operation
	//parameters: destination, size of each element, number of elements, file pointer
	size_t byteRead = fread(buffer, 1, fileSize, file);
	buffer[byteRead] = '\0';

	return buffer;
}

char* quickToArray(FILE *file){
	if(file == NULL) return NULL;
	int fileSize = sizeOfFile(file);
	char *buffer = toArray(file, fileSize);
	return buffer;
}

char* fileToBuffer(const char *fileName){
	
	FILE *file = fopen(fileName, "r");
	if (file==NULL) return NULL;

	
	char *buffer = quickToArray(file);
	if(buffer != NULL){
                message("SUCCESS", 0);
                message("buffer stream created", 1);
        } else {
                customError("failed");
        }



        fclose(file);
        return buffer;

}
void PROCESS_wordToken(char *word){
        printf("WORD FOUND: %s\n", word);
}

//TOKENIZATION
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





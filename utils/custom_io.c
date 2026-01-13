#include <custom_io.h>


//CUSTOM PRINTS     ---MOVE TO ANOTHER FILE---
//
//
//              printline
void printline(int length){
        printf("\n");
        for(int i = 0; i<length; i++){
                printf("-");
        }
        printf("\n");
}

//              custome header
void header(const char *text){
        int length = strlen(text);
        printline(length+12);
        printf("      %s", text);
        printline(length+12);
}
void message(const char *custom_message, int blue){
        if(blue == 0){
                printf("\n%s%s%s\n", BLUE, custom_message, DEFAULT);
        } else {
                printf("%s\n", custom_message);
        }
}

//              custom error, const = Read-Only char
void customError(const char *custom_message){
                        //print errors to stderr
                        //"fprintf" = file print format. lets you choose exactly
                        //      where the error goes
                        //      in this case, to stderr
                        //"stderr", unbuffered output stream reserved for errors, prints directly
        fprintf(stderr, "%sERROR: %s%s", RED, custom_message, DEFAULT);
}


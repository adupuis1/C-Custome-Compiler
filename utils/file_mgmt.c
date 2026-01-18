#include "file_mgmt.h"
#include "custom_io.h"

//FILE FUNCTIONS
//      GET FILE SIZE
int sizeOfFile(FILE *file){
        if(file == NULL) return 0;

        //      1. move to very last byte in file
        fseek(file, 0L, SEEK_END);

        //      2. check the postion ftell(file): how many bytes away from start
        int size = (int)ftell(file);

        //      3. reset cursor to start of file so other functions like fread  can read it
        rewind(file);
        return size;
}
//      CREATE AN ARRAY SIZE OF FILESIZE
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


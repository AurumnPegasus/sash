#include "header.h"

void echo(char* tokens[]) {
    long index = 1;
    char* string = "";
    while(tokens[index]) {
        if(tokens[index + 1] == NULL) {
            printf("%s", tokens[index]);
            break;    
        }
        printf("%s ", tokens[index]);
        index++;
    }
    printf("\n");
}
#include "header.h"

void pipeRun(char* command) {
    char* store = (char *) malloc(sizeof(char)*strlen(command));
    strcpy(store, command);
    char* delims = "|";
    char* save_pointer;
    char* args = strtok_r(removeSpace(command), delims, &save_pointer);
    int newfd = 0;
    long lenargs = 0;
    while(args != NULL) {
        lenargs++;
        args = strtok_r(NULL, delims, &save_pointer);
    }

    args = strtok_r(removeSpace(command), delims, &save_pointer);
    int count = 0;
    bool islast = false;
    while(args != NULL) {
        count++;
        if (count == lenargs) {
            islast = true;
        }
        
        newfd = getIOFiles(args, islast, newfd);
        args = strtok_r(NULL, delims, &save_pointer);
    }
}
#include "header.h"

char* getAbsolute(void) {
    size_t pathsize = MAXLEN;
    char* path = (char *) malloc(sizeof(char)*pathsize);
    if (getcwd(path, pathsize) == NULL) {
        printf("Error Number: %d\n", errno);
        perror("absolute: ");
        return NULL;
    } else {
        return path;
    }
}

char* getRelative(char* home, char* path) {
    size_t relsize = 1000;
    char* rel = (char *)malloc(sizeof(char)*1000);
    
    size_t homesize = strlen(home);
    size_t pathsize = strlen(path);
    if (homesize <= pathsize) {
        long index = 0;
        for(long i=0;i<homesize;i++){
            if (home[i] != path[i]) {
                index = i;
                break;
            }
        }
        
        if (index == 0) {
            rel[0] = '~';
            index = 1;
            for(long i=homesize;i<pathsize;i++) {
                rel[index] = path[i];
                index++;
            }
            rel[index] = '\0';
        } else {
            return getAbsolute();
        }
    } else {
        return getAbsolute();
    }

    return rel;
}

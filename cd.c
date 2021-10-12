#include "header.h" 

extern char* previous;
char* previous = NULL;

void initPrev(void) {
    if (previous == NULL) {
        previous = home;
    }
}

void cd(char* destination) {
    char* temp = getAbsolute();
    long response = chdir(destination);
    if (response != 0) {
        printf("Error Number: %d\n", errno);
        perror("chdir: ");
    } else {
        previous = temp;
    }
}

void change(char* tokens[]) {
    long index = 0;
    while(tokens[index]) {
        index++;
    }

    if (index > 2) {
        printf("sash: cd: too many arguments\n");
        return;
    } else if (index == 1) {
        if (strcmp("cd", tokens[0]) == 0) {
            cd(home);
        } else {
            printf("sash: No such command found\n");
            return;
        }
    } else {
        if (strcmp("..", tokens[1]) == 0) {
            char* path = strcat(strcat(getAbsolute(),"/"), tokens[1]);
            cd(path);
        } else if (strcmp("~", tokens[1]) == 0) {
            cd(home);
        } else if (strcmp(".", tokens[1]) == 0) {
            previous = getAbsolute();
        } else if(strcmp("-", tokens[1]) == 0) {
            cd(previous);
        } else {
            char* path = strcat(strcat(getAbsolute(),"/"), tokens[1]);
            cd(path);
        }
    }
}
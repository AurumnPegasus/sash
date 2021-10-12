#include "header.h"

int getIOFiles(char* command, bool islast, int newfd) {
    char* store = (char *) malloc(sizeof(char)*strlen(command));
    strcpy(store, command);
    char* tokens[MAXLEN];
    char* delims = " \n\t";
    char* save_pointer;
    char* args = strtok_r(removeSpace(command), delims, &save_pointer);
    bool bg = false;

    int inpointer = -1;
    int outpointer = -1;
    bool isAppend = false;
    char* arguments[MAXLEN];
    long argcount = 0;
    long index = 0;

    while(args != NULL) {
        tokens[index] = args;
        args = strtok_r(NULL, delims, &save_pointer);
        index++;
    }
    tokens[index] = NULL;
    index = 0;

    while(tokens[index] != NULL) {
        if (strcmp(tokens[index], "<") == 0) {
            inpointer = index + 1;
            index++;
        } else if (strcmp(tokens[index], ">") == 0) {
            outpointer = index + 1;
            isAppend = false;
            index++;
        } else if (strcmp(tokens[index], ">>") == 0) {
            outpointer = index + 1;
            isAppend = true;
            index++;
        } else if (strcmp(tokens[index], "&") == 0) {
            bg = true;
        } else {
            arguments[argcount] = tokens[index];
            argcount++;
        }
        index++;
    }
    arguments[argcount] = NULL;
    int fd[2];
    pipe(fd);

    int F_STDOUT = (islast)? 1: dup(fd[1]);
    int F_STDIN = newfd;
    int o_fd = 1;
    int i_fd = 0;
    int STDIN = -1;
    int STDOUT = -1;

    if (outpointer != -1) {
        if (!isAppend) {
            o_fd = open(tokens[outpointer], O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (o_fd < 0) {
                fprintf(stderr, "Error Number: %d\n", errno);
                perror("Output File Append: ");
            }
        } else {
            o_fd = open(tokens[outpointer], O_WRONLY | O_APPEND, 0644);
            if (o_fd < 0) {
                fprintf(stderr, "Error Number: %d\n", errno);
                perror("Output File: ");
            }
        }

        STDOUT = dup(STDOUT_FILENO);
        int response = dup2(o_fd, 1);
        if (response < 0) {
            fprintf(stderr, "Error Number: %d\n", errno);
            perror("Change input: ");
        }
        close(o_fd);
    }

    if (inpointer != -1) {
        i_fd = open(tokens[inpointer], O_RDONLY);
        if (i_fd < 0) {
            fprintf(stderr, "Error Number: %d\n", errno);
            perror("Input File: ");
        }
        // F_STDIN = dup(i_fd);
        STDIN = dup(STDIN_FILENO);
        int response = dup2(i_fd, 0);
        if (response < 0) {
            fprintf(stderr, "Error Number: %d\n", errno);
            perror("Change input: ");
        }
        close(i_fd);
    }
    int save = dup(fd[0]);
    runCommand(arguments, fd, &F_STDIN, &F_STDOUT, bg);
    if (F_STDOUT != -1) {
        int response = dup2(1, F_STDOUT);
        if(response < 0) {
            printf("Error Number: %d\n", errno);
            perror("dup2 stdout restore: ");
        }
        // close(F_STDIN);
    }

    fflush(stdin);
    if(STDOUT != -1) {
        int response = dup2(STDOUT, 1);
        if(response < 0) {
            printf("Error Number: %d\n", errno);
            perror("dup2 stdout restore: ");
        }
    }

    if (STDIN != -1) {
        int response = dup2(STDIN, 0);
        if(response < 0) {
            printf("Error Number: %d\n", errno);
            perror("dup2 stdout restore: ");
        }
    }

    if (F_STDIN != 0) {
        close(F_STDIN);
    }

    // close(fd[1]);
    return save;
}
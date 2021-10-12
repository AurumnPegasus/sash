#include "header.h"

void individualRun(char* command, char* tokens[]) {
    if (strcmp(command, "pwd") == 0) {
        printf("%s\n", getAbsolute());
    } else if (strcmp(command, "echo") == 0) {
        echo(tokens);
    } else if (strcmp(command, "cd") == 0) {
        change(tokens);
    } else if (strcmp(command, "ls") == 0) {
        parseLS(tokens);
    } else if (strcmp(command, "pinfo") == 0) {
        parsePINFO(tokens);
    } else if (strcmp(command, "jobs") == 0) {
        parseJobs(tokens);
    } else if (strcmp(command, "sig") == 0) {
        sig(tokens);
    } else if (strcmp(command, "fg") == 0) {
        ground(tokens);
    } else if (strcmp(command, "bg") == 0) {
        ground(tokens);
    } else if (strcmp(command, "replay") == 0) {
        parseReplay(tokens);
    } else {
        int response = execvp(command, tokens);
        if (response < 0) {
            printf("Error Number: %d\n", errno);
            perror("execvp: ");    
        }
    }
}

void runCommand(char* tokens[], int* fd, int* infd, int* outfd, bool bg){
    char* command = tokens[0];
    fg_name = command;
    pid_t child = fork();
    if (child == 0) {
        // child
        close(fd[0]);
        signal(SIGTSTP, SIG_DFL);
	    signal(SIGINT, SIG_DFL);
        int response = dup2(*infd, 0);
        if(response < 0) {
            printf("Error Number: %d\n", errno);
            perror("dup2 input child: ");
        }

        if (*outfd != 1) {
            response = dup2(fd[1], 1);
            if (response < 0) {
                printf("Error Number; %d\n", errno);
                perror("dup2 output child: ");
            }
        }

        if(bg) 
            setpgid(0, 0);
        individualRun(command, tokens);
        close(*infd);
        close(fd[1]);
        exit(0);
    } else if (child > 0) {
        // parent
        *infd = fd[0];
        close(fd[1]);
        if(bg) {
            printf("pid: %d\n", child);
            addProc(command, child);
        }
        if(!bg) {
            int wstatus;
            while(waitpid(child, &wstatus, WUNTRACED) > 0) {
                break;
            }

            if (WIFSTOPPED(wstatus)) {
                addProc(fg_name, child);
            }
        }

        close(*infd);
    } else {
        printf("Error Number: %d\n", errno);
        perror("fork: ");
    }
}
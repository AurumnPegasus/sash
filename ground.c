#include "header.h"


void background(pid_t child) {
    int response = kill(child, SIGCONT);
    if (response < 0) {
        printf("Error Number: %d\n", errno);
        perror("bg: ");
    }
}

void foreground(pid_t child) {
    printf("PID: %d\n", child);
    signal(SIGTTOU, SIG_IGN);
    int tpid = tcgetpgrp(0);
    tcsetpgrp(0, child);
    kill(child, SIGCONT);
    int wstatus;
    waitpid(child, &wstatus, WUNTRACED);
    tcsetpgrp(0, tpid);
    signal(SIGTTOU, SIG_DFL);
}

void ground(char* tokens[]) {
    long index = 0;
    while(tokens[index]){
        index++;
    }

    if (index != 2) {
        perror("Invalid Number of Arguments\n");
        return;
    }

    char* pointer;
    errno = 0;
    index = strtol(tokens[1], &pointer, 10);
    if ((errno == ERANGE && (index == LONG_MAX || index == LONG_MIN)) || (errno != 0 && index == 0)) {
        printf("Error Number: %d\n", errno);
        perror("strtol index: ");
        return;
    }

    if (pointer == tokens[1]) {
        printf("Program: No digits were found\n");
        return;
    }

    pid_t child;
    if (0 < index && index <= plen )  {
        child = processes[index - 1].pid;
        if (strcmp(tokens[0], "fg") == 0) {
            foreground(child);
        } else {
            background(child);
        }
    } else {
        perror("No such process exists \n");
    }
}

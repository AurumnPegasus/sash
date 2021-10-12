#include "header.h"

char status(pid_t pid) {
    int response = kill(pid, 0);
    if (response != 0) {
        printf("Error Number: %d\n", errno);
        perror("status: ");
    }
    char* filename = (char *)malloc(sizeof(char)*MAXLEN);
    sprintf(filename, "/proc/%d/stat", pid);
    FILE* f = fopen(filename, "r");
    int unused, ppid;
    char state;
    char comm[MAXLEN];
    size_t vmem;
    fscanf(f, "%d %s %c %d %lu", &unused, comm, &state, &ppid, &vmem);
    fclose(f);
    return state;
}

void pinfo(pid_t pid) {
    int resposne = kill(pid, 0);
    if (resposne == 0) {
        printf("pid -- %d\n", pid);
    } else {
        printf("Error Number: %d\n", errno);
        perror("pinfo: ");
        return;
    }

    char* filename = (char *) malloc(sizeof(char) * MAXLEN);
    sprintf(filename, "/proc/%d/stat", pid);
    FILE* f = fopen(filename, "r");
    int unused;
    char comm[MAXLEN];
    char state;
    int ppid;
    char* buf = (char *) malloc(sizeof(char) * MAXLEN);
    char* pr = (char *) malloc(sizeof(char) * MAXLEN);
    pid_t pgroup = getpgid(pid);
    pid_t tgroup = tcgetpgrp(STDOUT_FILENO);
    char plus = (tgroup == pgroup) ? '+' : ' ';
    sprintf(pr, "/proc/%d/exe", pid);
    size_t bufsize = MAXLEN;
    size_t vmem;
    fscanf(f, "%d %s %c %d %lu", &unused, comm, &state, &ppid, &vmem);
    int response = readlink("/proc/self/exe", buf, bufsize);
    if (response == -1) {
        printf("Error Number: %d\n", errno);
        perror("readlink: ");
        return;
    }
    printf("Process Status --- %c%c\n", state, plus);
    printf("memory --- %ld {Virtual Memory}\n", vmem);
    char* rel = getRelative(home, buf);
    printf("Executable Path --- %s\n", rel);
    fclose(f);
    free(filename);
    free(buf);
}

void parsePINFO(char* tokens[]) {
    long index = 0;
    while(tokens[index]) {
        index++;
    }
    if(index == 1) {
        pinfo(getpid());
    }
     else {
        char* endptr;
        errno = 0;
        long val = strtol(tokens[1], &endptr, 10);
        if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0)) {
            printf("Error Number: %d\n", errno);
            perror("strtol: ");
            return;
        }

        if (endptr == tokens[1]) {
            printf("Program: No digits were found\n");
            return;
        }

        pinfo(val);
    }
}
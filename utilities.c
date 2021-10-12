#include "header.h"

void addProc(char* name, pid_t pid) {
    printf("Adding Process: %s with pid: %d and length: %d\n", name, pid, plen);
    processes[plen].name = name;
    processes[plen].pid = pid;
    processes[plen].srno = plen + 1;
    processes[plen].display = true;
    plen++;
}

void delProc(pid_t pid) {
    for(int i=0;i<plen;i++) {
        if(processes[i].pid == pid) {
            processes[i].display = false;
            processes[i].pid = -1;
        }
    }
}

char* removeSpace(char* line) {
    size_t linelen = strlen(line);
    size_t newlen = MAXLEN;
    char* newline = (char *) malloc(sizeof(char)*newlen);
    char prev = ' ';
    long index = 0;
    for(long i=0;i<linelen;i++) {
        if (prev == ' ' && line[i] == ' ') {
            ;
        } else {
            newline[index] = line[i];
            index++;
        }
        prev = line[i];
    }
    newline[index] = '\0';
    return newline;
}

char* strip(char* string) {
    char* copy = string;
    printf("copy: %s\n", copy);
    size_t size = strlen(copy);
    char* end;
    if (!size || (copy[0] != ' ' && copy[size-1] != ' ')) {
        printf("final: %s\n", copy);
        return copy;
    } else {
        end = copy + size - 1;
        while(end >= copy && isspace(*end)) {
            end--;
        }
        *(end+1) = '\0';
        while(*copy && isspace(copy)) {
            copy++;
        }
        printf("final: %s\n", copy);
        return copy;
    }
}

char* fileName(char* string, long len) {
    char* file = (char *) malloc(sizeof(char)*len);
    long index = 0;
    for(long i=0;i<len;i++) {
        if(string[i] == '/') {
            free(file);
            char* file = (char *) malloc(sizeof(char)*len);
            index = 0;
        } else {
            file[index] = string[i];
            index++;
        }
    }
    file[index] = '\0';
    return file;
}

char* findChar(char* string, char c) {
    char* pointer = strchr(string, c);
    return pointer;
}


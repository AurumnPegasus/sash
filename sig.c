#include "header.h"

void sig(char* tokens[]) {
    char* pointer1, pointer2;
    errno = 0;
    long index = strtol(tokens[1], &pointer1, 10);
    if ((errno == ERANGE && (index == LONG_MAX || index == LONG_MIN)) || (errno != 0 && index == 0)) {
        printf("Error Number: %d\n", errno);
        perror("strtol index: ");
        return;
    }

    if (pointer1 == tokens[1]) {
        printf("Program: No digits were found\n");
        return;
    }

    errno = 0;
    long signal = strtol(tokens[2], &pointer1, 10);
    if ((errno == ERANGE && (signal == LONG_MAX || signal == LONG_MIN)) || (errno != 0 && signal == 0)) {
        printf("Error Number: %d\n", errno);
        perror("strtol signal: ");
        return;
    }

    if (pointer1 == tokens[1]) {
        printf("Program: No digits were found\n");
        return;
    }

    if ( 0 < index && index <= plen ) {
        int response = kill(processes[index -1].pid, signal);
        if (response < 0) {
            printf("Error Number: %d\n", errno);
            perror("kill signal: ");
        }
    }
}

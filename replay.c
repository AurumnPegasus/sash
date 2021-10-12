#include "header.h"
// replay -command echo "hi" -interval 3 -period 6
void parseReplay(char* tokens[]) {
    if(strcmp(tokens[1], "-command") == 0) {
        char* command = (char *) malloc(sizeof(char)*MAXLEN);
        char* space = (char *) malloc(sizeof(char)*MAXLEN);
        char* tempspace = (char *) malloc(sizeof(char)*MAXLEN);
        space[0] = ' ';
        tempspace[0] = ' ';
        long index = 2;
        long interval = 0;
        long period = 0;
        while(tokens[index]) {
            if (strcmp(tokens[index], "-interval") == 0) {
                errno = 0;
                char* pointer;
                interval = strtol(tokens[index+1], &pointer, 10);
                if ((errno == ERANGE && (interval == LONG_MAX || interval == LONG_MIN)) || (errno != 0 && interval == 0)) {
                    printf("Error Number: %d\n", errno);
                    perror("strtol index: ");
                }

                if (pointer == tokens[index + 1]) {
                    printf("Program: No digits were found\n");
                }
                index++;
            } else if (strcmp(tokens[index], "-period") == 0) {
                errno = 0;
                char* pointer;
                period = strtol(tokens[index+1], &pointer, 10);
                if ((errno == ERANGE && (period == LONG_MAX || period == LONG_MIN)) || (errno != 0 && period == 0)) {
                    printf("Error Number: %d\n", errno);
                    perror("strtol index: ");
                }

                if (pointer == tokens[index + 1]) {
                    printf("Program: No digits were found\n");
                }
                index++;
            } else {
                strcat(command, strcat(space, tokens[index]));
                strcpy(space, tempspace);
            }
            index++;
        }
        
        time_t start, end;
        double elapsed;
        start = time(NULL);
        // printf("interval: %ld, period: %ld\n", interval, period);
        while(true) {
            sleep(1);
            end = time(NULL);
            elapsed = difftime(end, start);
            // printf("start: %ld, end: %ld, difference: %f\n", start, end, elapsed);
            if (((int)elapsed)%interval == 0) {
                pipeRun(command);
            }
            if (elapsed >= period) {
                break;
            }
        }
    } else {
        perror("No such command");
    }
}
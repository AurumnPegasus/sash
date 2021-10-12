#include "header.h"

char* home = NULL;
struct process *processes = NULL;
int plen = 0;
char* fg_name = NULL;

int main() {

    char* delims = ";\n";
    size_t len = MAXLEN;
    char* line = (char *) malloc(sizeof(char) * len);

    size_t homesize = MAXLEN;
    home = (char *) malloc(sizeof(char)*homesize);
    fg_name = (char *) malloc(sizeof(char)*MAXLEN);
    fg_name = "main";

    processes = (struct process*) malloc(sizeof(struct process)*MAXLEN);
    setup();

    if (getcwd(home, homesize) == NULL) {
        printf("Error Number: %d\n", errno);
        perror("getcwd home: ");
        return -1;
    }
    initPrev();

    while(1) {
        prompt();
        errno = 0;
        if (!fgets(line, len, stdin)) {
            printf("Error Number: %d\n", errno);
            perror("read main: ");
            return -1;
        } else {
            char* save_pointer;
            char* args = strtok_r(removeSpace(line), delims, &save_pointer);
            while (args!= NULL) {
                pipeRun(args);
                args = strtok_r(NULL, delims, &save_pointer);
            }
        }
    }

    free(line);
    free(home);
    free(processes);
}
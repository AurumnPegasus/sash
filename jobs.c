#include "header.h"

struct storeJobs{
    char* name;
    pid_t pid;
    int srno;
    bool display;
};

int compare(const void *s1, const void *s2) {
    struct storeJobs* j1 = (struct storeJobs *) s1;
    struct storeJobs* j2 = (struct storeJobs *) s2;
    int c = strcmp(j1->name, j2->name);
    if (c == 0) {
        return j1->srno - j2->srno;
    } else {
        return c;
    }
}

void displayJobs(bool flag_r, bool flag_s) {
    struct storeJobs* running = (struct storeJobs*) malloc(sizeof(struct storeJobs*)*MAXLEN);
    struct storeJobs* stopped = (struct storeJobs*) malloc(sizeof(struct storeJobs*)*MAXLEN);
    int rindex = 0;
    int sindex = 0;
    if (!flag_r && !flag_s) {
        flag_r = true;
        flag_s = true;
    }

    for(int i=0;i<plen;i++) {
        char state[MAXLEN];
        if (!processes[i].display) {
            continue;
        }
    
        if (status(processes[i].pid) == 'T') {
            strcpy(state, "Stopped ");
            stopped[sindex].srno = processes[i].srno;
            stopped[sindex].pid = processes[i].pid;
            stopped[sindex].display = processes[i].display;
            strcat(state, processes[i].name);
            stopped[sindex].name = (char *) malloc(sizeof(char)*MAXLEN);
            strcpy(stopped[sindex].name, state);
            sindex++;
        }  else {
            strcpy(state, "Running ");
            running[rindex].srno = processes[i].srno;
            running[rindex].pid = processes[i].pid;
            running[rindex].display = processes[i].display;
            strcat(state, processes[i].name);
            running[rindex].name = (char *) malloc(sizeof(char)*MAXLEN);
            strcpy(running[rindex].name, state);
            rindex++;
        }
    }

    if (flag_r) {
        qsort(running, rindex, sizeof(struct storeJobs), compare);
        for(int i=0;i<rindex;i++) {
            printf("[%d]   %s   [%d]\n", running[i].srno, running[i].name, running[i].pid);
        }
    }
    if (flag_s) {
        qsort(stopped, sindex, sizeof(struct storeJobs), compare);
        for(int i=0;i<sindex;i++) {
            printf("[%d]   %s   [%d]\n", stopped[i].srno, stopped[i].name, stopped[i].pid);
        }
    }

    free(running);
    free(stopped);
}

void parseJobs(char* tokens[]) {
    bool flag_r = false;
    bool flag_s = false;
    long index = 0;
    while(tokens[index]) {
        char* current = tokens[index];
        if (strcmp(current, "-r") == 0) {
            flag_r = true;
        } else if (strcmp(current, "-s") == 0) {
            flag_s = true;
        } else if (strcmp(current, "-rs") == 0) {
            flag_r = true;
            flag_s = true;
        } else if (strcmp(current, "-sr") == 0) {
            flag_r = true;
            flag_s = true;
        }
        index++;
    }
    displayJobs(flag_r, flag_s);
}
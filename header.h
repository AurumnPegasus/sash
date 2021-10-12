#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXLEN 1024
#define DIRSIZE 4096

extern int errno;
extern char* home;
struct process {
    char* name;
    pid_t pid;
    int srno;
    bool display;
};
extern struct process* processes;
extern int plen;
extern char* fg_name;

void prompt();
char* getUser(void);
char* getHost(void);
char* getAbsolute(void);
char* getRelative(char* home, char* path);
char* removeSpace(char* line);
char* strip(char* string);
int getIOFiles(char* command, bool islast, int readfd);
void runCommand(char* tokens[], int* fd, int* infd, int* outfd, bool bg);
void echo(char* tokens[]);
void change(char* tokensp[]);
void cd(char* destination);
void initPrev(void);
void parseLS(char* tokens[]);
char* fileName(char* string, long len);
void displayFile(char* path, bool flag_a);
void parsePINFO(char* tokens[]);
char* findChar(char* string, char c);
void addProc(char* name, pid_t pid);
void setup(void);
void signal_handler(int signum);
void delProc(pid_t pid);
void pipeRun(char* command);
char status(pid_t pid);
void parseJobs(char* tokens[]);
void sig(char* tokens[]);
void ground(char* tokens[]);
void background(pid_t child);
void parseReplay(char* tokens[]);
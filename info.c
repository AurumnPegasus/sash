#include "header.h"

char* getHost(void) {
    size_t hostsize = MAXLEN;
    char* hostname = (char *) malloc(sizeof(char)*hostsize);
    if (gethostname(hostname, hostsize) == -1) {
        printf("Error Number: %d\n", errno);
        perror("gethost: ");
        return NULL;
    } else {
        return hostname;
    }
}

char* getUser(void) {
    struct passwd *username;
    uid_t uid = getuid();
    username = getpwuid(uid);
    return username->pw_name;
}

void prompt() {
    char* hostname = getHost();
    char* username = getUser();

    if (hostname == NULL || username == NULL) {
        printf("Error Number: %d\n", errno);
        perror("prompt: ");
    }

    char* abs = getAbsolute();
    char* rel = getRelative(home, abs);
    printf("<%s@%s:%s> ", username, hostname, rel);
}
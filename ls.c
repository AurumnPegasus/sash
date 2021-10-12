#include "header.h"

bool isDir(char* path) {
    char* copy = path;
    if (strcmp(copy, "~") == 0) {
        return true;
    }

    DIR *dir = opendir(path);
    if (dir) {
        return true;
    } else {
        return false;
    }
}

void displayFile(char* path, bool flag_a) {
    bool isfile = !isDir(path);
    char dir = (isfile) ? '-':'d';
    char* filename = (isfile) ? fileName(path, strlen(path)) : fileName(path, strlen(path));
    if(flag_a == 0 && filename[0] == '.') {
        return;
    }

    struct stat file;
    int f = stat(path, &file);

    char user_read = (file.st_mode & S_IRUSR)? 'r':'-';
    char user_write = (file.st_mode & S_IWUSR) ? 'w':'-';
    char user_execute = (file.st_mode & S_IXUSR) ? 'x':'-';
    char group_read = (file.st_mode & S_IRGRP) ? 'r':'-';
    char group_write = (file.st_mode & S_IWGRP) ? 'w':'-';
    char group_execute = (file.st_mode & S_IXGRP) ? 'x':'-';
    char other_read = (file.st_mode & S_IROTH) ? 'r':'-';
    char other_write =  (file.st_mode & S_IWOTH) ? 'w':'-';
    char other_execute = (file.st_mode & S_IXOTH) ? 'x':'-';

    struct passwd *pw = getpwuid(file.st_uid);
    struct group *gr = getgrgid(file.st_gid);

    char* time = ctime(&file.st_mtime);
    time[strlen(time) -1] = '\0';
    char* formatted = (char *) malloc(sizeof(char) * strlen(time));
    int index = 0;
    for(int i=4;i<=15;i++) {
        formatted[index] = time[i];
        index++;
    }
    formatted[index] = '\0';

    long filesize;
    if(isfile) {
        filesize = file.st_size;
    } else {
        filesize = DIRSIZE;
    }

    long links = file.st_nlink;
    
    printf("%c%c%c%c%c%c%c%c%c%c  %ld  %s  %s  %ld  %s  %s\n", dir, user_read, user_write, user_execute, group_read, group_write, group_execute, other_read, other_write, other_execute, links, pw->pw_name, gr->gr_name, filesize, formatted, filename);
}

void getFiles(char* paths[], bool flag_l, bool flag_a, long len) {
    bool display_name = (len == 2) ? false: true;
    long index = 0;
    while(paths[index]) {
        char* path = paths[index];
        if (!isDir(path)) {
            int fd = access(path, F_OK);
            if (fd < 0) {
                printf("%s: Error Number: %d\n", path, errno);
                perror("bad fd: ");
                index++;
                continue;
            }
            
            if(display_name)
                printf("%s: \n", fileName(path, strlen(path)));
            if(flag_l) {
                displayFile(path, flag_a);
            } else {
                char* fname = fileName(path, strlen(path));
                if(fname[0] == '.' && flag_a == 0) {
                    index++;
                    continue;
                } else {
                    printf("%s\n", path);
                }
            }
        } else {

            char* cp = malloc(sizeof(char)*10000);
            if (strcmp(path, "~") == 0) {
                strcpy(cp, home);
            } else {
                strcpy(cp, path);
            }

            struct dirent *dir_pointer;
            DIR *dir = opendir(cp);
            if(!dir) {
                printf("%s: Error Number: %d\n", path, errno);
                perror("readdir: ");
                index++;
                continue;
            }
            dir_pointer = readdir(dir);

            if (display_name)
                if(path[strlen(path) - 1] == '/') {
                    printf("%s: \n", fileName(path, strlen(path) -1));    
                } else {
                    printf("%s: \n", fileName(path, strlen(path)));
                }                
                
            
            while(dir_pointer != NULL) {
                char* fname = dir_pointer->d_name;
                char* temp = (char *) malloc(sizeof(char)*1000);
                if(strcmp(cp, home) == 0) {
                    strcpy(temp, home);
                } else {
                    temp = getAbsolute();
                }
                
                if(strcmp(path, "~") == 0) {
                    temp = strcat(temp, "/");
                } else {
                    if(cp[strlen(cp) - 1] == '/') {
                    temp = strcat(strcat(temp, "/"), cp);
                    } else {
                        temp = strcat(strcat(strcat(temp, "/"), cp), "/");
                    }
                }
                if (strcmp(cp, ".") != 0) {
                    temp = strcat(temp, fname);
                } else {
                    temp = strcpy(temp, fname);
                }

                if(flag_l) {
                    // printf("print: %s\n", temp);
                    displayFile(temp, flag_a);
                } else {
                    if (fname[0] == '.' && flag_a == 0) {
                        ;
                    } else {
                        printf("%s   ", dir_pointer->d_name);
                    }
                }
                free(temp);
                dir_pointer = readdir(dir);
            }
            fflush(stdout);
            free(cp);
        }

        index++;
        printf("\n");
    }
}

void parseLS(char* tokens[]) {
    bool flag_l = false;
    bool flag_a = false;
    char* paths[MAXLEN];
    long index = 0;
    long i_path = 0;
    while(tokens[index]) {
        char* current = tokens[index];
        if(strcmp(current, "-l") == 0) {
            flag_l = true;
        } else if(strcmp(current, "-a") == 0) {
            flag_a = true;
        } else if(strcmp(current, "-la") == 0) {
            flag_a = true;
            flag_l = true;
        } else if(strcmp(current, "-al") == 0) {
            flag_a = true;
            flag_l = true;
        } else if (strcmp(current, "ls") != 0) {
            paths[i_path] = current;
            i_path++;
        }
        index++;
    }
    if(i_path == 0) {
        paths[i_path] = ".";
        i_path++;
    }
    paths[i_path] = NULL;
    i_path++;
    getFiles(paths, flag_l, flag_a, i_path);
    printf("\n");
}
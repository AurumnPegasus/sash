#include "header.h"

void setup(void) {
    struct sigaction setup;
    sigemptyset(&setup.sa_mask);
    sigaddset(&setup.sa_mask, SIGCHLD);
    sigaddset(&setup.sa_mask, SIGINT);
	sigaddset(&setup.sa_mask, SIGQUIT);
    sigaddset(&setup.sa_mask, SIGTSTP);
    setup.sa_handler = signal_handler;
    setup.sa_flags = SA_RESTART;

    if(sigaction(SIGCHLD, &setup, NULL) < 0) {
        printf("Error Number: %d\n", errno);
        perror("sigchild: ");
    }

    if(sigaction(SIGTERM, &setup, NULL) < 0) {
        printf("Error Number: %d\n", errno);
        perror("sigterm: ");
    }

    signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void signal_handler(int signum) {

    if(signum == SIGTERM)
	{
        printf("Process %d terminated\n", getpid());
		exit(1);
	} else if (signum == SIGTSTP) {
        printf("here\n");
        addProc(fg_name, getpid());
        signal(SIGTSTP, SIG_DFL);
        kill(getpid(), SIGTSTP);
    } else if (signum == SIGCHLD) {
        int status;
        pid_t pid;
        while((pid = waitpid(-1, &status, WNOHANG)) > 0) {
            int index;
            for(index = 0;index<plen;index++) {
                if(processes[index].pid == pid) {
                    break;
                }
            }

            if(WIFEXITED(status)) {
                fprintf(stderr, "\n%s with pid %d exited normally\n", processes[index].name, processes[index].pid);
            } else {
                fprintf(stderr, "\n%s with pid %d exited abnormally\n", processes[index].name, processes[index].pid);
            }   
        delProc(pid);
        }
    }
    return;
}
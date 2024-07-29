#include "headers.h"

int kill_process_pid(int pid,int signal){
    if (kill(pid, signal) == -1) {
        if (errno == ESRCH) {
            printf("Error: No such process with PID %d exists.\n",pid);
        }  
     return 0;
    }
    printf("Sent signal %d to process with pid %d\n",signal,pid);
    return 1;
}
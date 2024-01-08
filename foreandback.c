#include"headers.h"

void fore_back(char* command,int back_cond,Queue q){
        char *args[4]; 
        int argCount = 0;
        args[0]="sh";
        args[1]="-c";
        args[2]=command;
        args[3] = NULL;

         struct timespec stime, etime;
        double time;

        int id = fork();
        if (id == 0) { 
            if(back_cond){
            printf("[%d]%d\n",q->element,getpid());
            }
            execvp("sh",args);
            perror("Error executing command");
            exit(1);
        } else if (id > 0) {
            if (!back_cond) {
                clock_gettime(CLOCK_REALTIME,&stime); 
                waitpid(id,NULL,0);  
                clock_gettime(CLOCK_REALTIME,&etime);  
                time=(etime.tv_sec-stime.tv_sec)+(etime.tv_nsec-stime.tv_nsec)/1e9;
                int r_time = round(time);
                if(r_time>2){
                    char* process_name=strtok(args[2]," \t");
                    char showing[300];
                    snprintf(showing,300,"%s:%d secs",process_name,r_time);
                    strcpy(promptprocess,showing);
                }
            } else {
            Push(q,id,args[2]);
            }
        } else {
            perror("Fork failed");
        }
        return;
}
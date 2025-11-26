#include"headers.h"

void fore_back(char* command,int back_cond,Queue q){
    int size=strlen(command)+1;
    char*arr=(char*)malloc(sizeof(char)*size);
    char*savepointer=NULL;
    strcpy(arr,command);
    arr[size-1]='\0';
        char *args[30]; 
        int argCount = 0;
        char *token = strtok_r(arr," \t'",&savepointer);
        while (token != NULL) {
            int w=strlen(token)+1;
            args[argCount]=(char*)malloc(sizeof(char)*w);
        strcpy(args[argCount],token);
        argCount++;
        token = strtok_r(NULL," \t",&savepointer);
        }
        args[argCount] = NULL;
        
         struct timespec stime, etime;
        double time;

        int id = fork();
        if (id == 0) { 
            int pid=getpid();
            int parent_pid=__getpgid(pid);
             
            if(back_cond){
            // printf("[%d]%d\n",q->element,pid);
            setpgid(pid,pid);
            }
            execvp(args[0],args);
            perror("Error executing command");
            exit(1);
            // if(back_cond){
            // setpgid(pid,parent_pid);
            // }
        } else if (id > 0) {
            // int r=id;
            if(back_cond){
             printf("[%d]%d\n",q->element,id);
            }
            if (!back_cond) {
                clock_gettime(CLOCK_REALTIME,&stime); 
                foreground_running=id;
               while(1){
                int stat; 
                int r=waitpid(id,&stat,WUNTRACED);
                if(WIFEXITED(stat) || r>0){
                    break;
                }

                if(WIFSTOPPED(stat)){
                    break;
                }
                }  
            // waitpid(id,NULL,0);
                foreground_running=0;
                clock_gettime(CLOCK_REALTIME,&etime);  
                time=(etime.tv_sec-stime.tv_sec)+(etime.tv_nsec-stime.tv_nsec)/1e9;
                int r_time = round(time);
                if(r_time>2){
                    char* process_name=args[0];
                    char showing[300];
                    snprintf(showing,300,"%s:%d secs",process_name,r_time);
                    strcpy(promptprocess,showing);
                }
            } 
            // else{
            Push(q,id,args[0],back_cond);
            // }
        } else {
            perror("Fork failed");
        }
        return;
}
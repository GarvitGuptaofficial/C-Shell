#include "headers.h"

void fgandbg(int pid,Queue q,int fgorbg){
    int foreorback=0; // 1 for background
    int back=0;
    Queue temp=q->next;
    while(temp!=NULL){
        if(temp->element==pid){
             back=1;
             foreorback=temp->fg_or_bg;
             break;
        }
        temp=temp->next;
    }

    if(back==0){
        printf("Process Not found with pid:%d\n",pid);
        return;
    }
    char *path=(char*)malloc(sizeof(char)*300);
    snprintf(path,300,"/proc/%d/status",pid);
    FILE* f=fopen(path,"r");
    if(f==NULL){
        printf("Process Not found with pid:%d\n",pid);
        return;
    }
    char status_file[2];
    char size_file[10];
    char*store_statusfile=(char*)malloc(sizeof(char)*300);
    int line=1;  
     while (fgets(store_statusfile,300,f)) {  
        if (strncmp(store_statusfile, "State:", 6) == 0) {
            sscanf(store_statusfile, "State: %s", status_file);
            break;
        }
     }
     fclose(f);
     free(path);
    int stop=0;
    int run=0;
    // printf("%s\n",store_statusfile);
     if(strncmp(status_file,"T",1)==0){
        stop=1;
     }else if(strncmp(status_file,"R",1)==0 || strncmp(status_file,"S",1)==0){
        run=1;
     }
     free(store_statusfile);
        
     if(fgorbg){
        //  printf("Hellos\n");
        
        if(run && foreorback){
            waitpid(pid,NULL,0);
            find_delete(q,pid);
            // printf("1\n"); 
        }else if(stop){
            kill(pid,SIGCONT);
            waitpid(pid,NULL,0);
            find_delete(q,pid);
            // printf("2\n"); 
        }     
     }else{
        //  printf("Hellosfsfere%d\n",stop);
        if(stop){
            // int y=fork();
            // if(y==0){
            setpgid(pid,pid);
            kill(pid,SIGCONT);
            // }
        }
     }
     return;
}
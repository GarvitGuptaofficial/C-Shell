#include "headers.h"

void ctrlC(int signal){
    if(signal==SIGINT){
        if(foreground_running!=0){
            int r=kill(foreground_running,SIGINT);
            foreground_running=0;
        }
    }
}

void sighandler(int sig_num)
{
    if(foreground_running!=0){
        kill(foreground_running,SIGTSTP);
        foreground_running=0;
    }
}

int main()
{
    // Keep accepting commands
    char curr_path[500];
    signal(SIGINT,ctrlC);
    signal(SIGTSTP,sighandler);
    if(getcwd(curr_path,500)==NULL){
        perror("getcwd");
    }else{
        strcpy(initial_dir,curr_path);
    }   
    FILE*A=fopen("./commandstore.txt","a");
    if(A==NULL){
        printf("File does not exist\n");
    }
    fclose(A);
    ori_stdin_fd = dup(STDIN_FILENO);
    ori_stdout_fd = dup(STDOUT_FILENO);
    snprintf(file_path,350,"%s/commandstore.txt",initial_dir);
    char*comm_saved[15];
    for(int l=0;l<15;l++){
        comm_saved[l]=(char*)malloc(sizeof(char)*4096);
    }
    store_comm(comm_saved);
    Queue q=(Queue)malloc(sizeof(struct queue)*1);
    q->rear=NULL;
    q->next=NULL;
    q->element=0;

    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt();
        if(strlen(promptprocess)!=0){
            strcpy(promptprocess,"");
        }
        char input[4096];
        char store_command[4096];
        if(fgets(input,4096,stdin)==NULL){
            kill(0,SIGTERM);
        }
        int len_input=strlen(input);
        if(strcmp(input,"exit\n")==0){
            break;
        }
        strcpy(store_command,input);
        Queue temp=q->next;
        while(temp!=NULL){
            if(temp->fg_or_bg==0){
                temp=temp->next;
                continue;
            }
            int pid=temp->element;
            // if(temp->fg_or_bg==1){
            
            int status;
            int result = waitpid(pid, &status,WNOHANG);
            if (result == -1) {
                printf("Error:%d\n",pid);
                perror("waitpid");
               
            } else if (result == 0) {
            } else {
                // fg_or_bg=1 for background
               
                if (WIFEXITED(status)) {
                    printf("%s exited normally(%d)\n",temp->str,pid);
                }else if (WIFSIGNALED(status)) {
                    printf("%s exited abnormally(%d)\n",temp->str,pid);
                }
              
                find_delete(q,pid);
            }
            temp=temp->next;
        }
        runcommand_tok(q,comm_saved,input,store_command);
    
    }
    return 0;
}

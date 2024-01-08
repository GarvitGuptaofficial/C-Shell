#include "headers.h"

int main()
{
    // Keep accepting commands
    char curr_path[500];
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
        fgets(input,4096,stdin);
        int len_input=strlen(input);
        strcpy(store_command,input);
         Queue temp=q->next;
        while(temp!=NULL){
            int pid=temp->element;
            int status;
            int result = waitpid(pid, &status,WNOHANG);
            if (result == -1) {
                perror("waitpid");
                return 1;
            } else if (result == 0) {
            } else {
                if (WIFEXITED(status)) {
                    printf("%s exited normally(%d)\n",temp->str,pid);
                }else if (WIFSIGNALED(status)) {
                    printf("%s exited abnormally(%d)\n",temp->str,pid);
                }
                find_delete(q,pid);
            }
            temp=temp->next;
        }
        runcommand(q,comm_saved,input,store_command);
    
    }
    return 0;
}

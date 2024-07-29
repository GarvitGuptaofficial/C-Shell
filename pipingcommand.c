#include "headers.h"

void runcommand_pipe(Queue q,char**comm_saved,char*inputs,char*store_command){
        int input_len=strlen(inputs);
        char*input=(char*)malloc(sizeof(char)*(input_len+1));
        strcpy(input,inputs);
        int pipe_len=0;
        for(int i=0;i<input_len;i++){
            if(input[i]=='|'){
                pipe_len++;
            }
        }
        char**commands_pipelist=(char**)malloc(sizeof(char*)*(pipe_len+1)); 
        
        int pipes_fd[pipe_len][2];
        for (int i = 0; i <pipe_len; i++)
            {
           if (pipe(pipes_fd[i]) == -1)
           {
            perror("Pipe failed");
            return;
           }
            }
        char delimiter[]="|";
        char* tok=strtok(input,delimiter);
        int j=0;
        while(tok!=NULL){
            int r=strlen(tok)+1;
            commands_pipelist[j]=(char*)malloc(sizeof(char)*r);
            strcpy(commands_pipelist[j],tok);
            tok=strtok(NULL,delimiter);
            j++;
        }
  
        for(int i=0;i<j;i++){
            if(i==pipe_len){
                dup2(ori_stdout_fd,STDOUT_FILENO);
            }
            if (i>0){
            dup2(pipes_fd[i - 1][0], STDIN_FILENO);
            }
       
        if(i<pipe_len){
            
            dup2(pipes_fd[i][1], STDOUT_FILENO);
       
          }

            int len=strlen(commands_pipelist[i]);
            char* commands_pipe=(char*)malloc(sizeof(char)*(len+1));
            char* store_commands_pipe=(char*)malloc(sizeof(char)*(len+1));
            strcpy(commands_pipe,commands_pipelist[i]);
            strcpy(store_commands_pipe,commands_pipelist[i]);
            runcommand(q,comm_saved,commands_pipe,store_commands_pipe);
             
        
            if (i > 0)
            {
                close(pipes_fd[i - 1][0]);
            }

            if (i < pipe_len)
            { 
                close(pipes_fd[i][1]);
            }
            
        }
        dup2(ori_stdout_fd,STDOUT_FILENO);
        dup2(ori_stdin_fd,STDIN_FILENO);
 
     for(int k=0;k<j;k++){
        free(commands_pipelist[k]);
     }
     free(commands_pipelist);
    return;
        
}

void runcommand_io(Queue q,char**comm_saved,char*inputs,char*store_command){
    // printf("Hi\n");
        int input_len=strlen(inputs);
        char*input=(char*)malloc(sizeof(char)*(input_len+1));
        strcpy(input,inputs);
        int pipe_len=0;
        int double_redirect=0;
        char* del_used=(char*)malloc(sizeof(char)*200);
        for(int i=0;i<input_len;i++){
            if(input[i]=='>' || input[i]=='<'){
                if(double_redirect && input[i]=='>'){
                    continue;
                }
                
                if(i+1<input_len && input[i]=='>' && input[i+1]=='>'){
                    double_redirect=1;
                }
                
                del_used[pipe_len]=input[i];
                pipe_len++;
            }
        }
   char**commands_pipelist=(char**)malloc(sizeof(char*)*(pipe_len+1));

        char delimiter[]="><";
        char* tok=strtok(input,delimiter);
        int j=0;
        while(tok!=NULL){
            int r=strlen(tok)+1;
            commands_pipelist[j]=(char*)malloc(sizeof(char)*r);
            strcpy(commands_pipelist[j],tok);
            // printf("%s\n",commands_pipelist[j]);
            tok=strtok(NULL,delimiter);
            j++;
        }
        int prev_stdout=dup(STDOUT_FILENO);
        int prev_stdin=dup(STDIN_FILENO);
        if(pipe_len==1){
            if(j==1){
                printf("No file input is given\n");
                return;
            }else if(j==2){
                char*path=(char*)malloc(sizeof(char)*256);
                char*pathfile=(char*)malloc(sizeof(char)*400);
                char*filename=(char*)malloc(sizeof(char)*140);
                getcwd(path,256);
                int file_len=strlen(commands_pipelist[1]);
                int file_i=0;
                for(int a=0;a<file_len;a++){
                    if(commands_pipelist[1][a]!=' ' && commands_pipelist[1][a]!='\t'){
                        filename[file_i++]=commands_pipelist[1][a];
                    }
                }
                filename[file_i]='\0';
                // printf("%s\n",filename);
                snprintf(pathfile,400,"%s/%s",path,filename);
                if(del_used[0]=='<'){
                    int read_file=open(pathfile,O_RDONLY);
                    if(read_file<0){
                     printf("Input file not found\n");
                     return;
                    }
                    if (dup2(read_file, STDIN_FILENO) == -1) {
                       perror("dup2");
                       return;
                    }
                    close(read_file);
                    int len=strlen(commands_pipelist[0]);
                    char* commands_pipe=(char*)malloc(sizeof(char)*(len+1));
                    char* store_commands_pipe=(char*)malloc(sizeof(char)*(len+1));
                    strcpy(commands_pipe,commands_pipelist[0]);
                    strcpy(store_commands_pipe,commands_pipelist[0]);
                    runcommand(q,comm_saved,commands_pipe,store_commands_pipe);
                    if (dup2( prev_stdin, STDIN_FILENO) == -1) {
                       perror("dup2");
                       return;
                    }
                }else if(del_used[0]=='>'){
                    int write_file;
                    int val=access(pathfile,F_OK);
                    if(double_redirect==1){
                        if(val==-1){
                         write_file=open(pathfile,O_WRONLY | O_APPEND | O_CREAT, 0644);
                        }else{
                          write_file=open(pathfile,O_WRONLY | O_APPEND, 0644);  
                        }
                        
                    }else{
                        if(val==-1){
                         write_file=open(pathfile,O_WRONLY  | O_CREAT | O_TRUNC, 0644);
                        }else{
                          write_file=open(pathfile,O_WRONLY | O_TRUNC, 0644);  
                        }
                    }
                    
                    if(write_file<0){
                     printf("Input file not found\n");
                     return;  
                    }
                    if (dup2(write_file, STDOUT_FILENO) == -1) {
                       perror("dup2");
                       return;
                    }
                    int len=strlen(commands_pipelist[0]);
                    char* commands_pipe=(char*)malloc(sizeof(char)*(len+1));
                    char* store_commands_pipe=(char*)malloc(sizeof(char)*(len+1));
                    strcpy(commands_pipe,commands_pipelist[0]);
                    strcpy(store_commands_pipe,commands_pipelist[0]);
                    runcommand(q,comm_saved,commands_pipe,store_commands_pipe);
                    close(write_file);
                    // close(STDOUT_FILENO);
                    if (dup2( prev_stdout, STDOUT_FILENO) == -1) {
                       perror("dup2");
                       return;
                    }
                }
                free(path);
                free(filename);
                free(pathfile);
            }
        }else if(pipe_len==2){
            if(j<3){
                printf("Input Files not provided\n");
                return;
            }else if(j==3){
                char*path=(char*)malloc(sizeof(char)*256);
                getcwd(path,256);
                char*pathfile1=(char*)malloc(sizeof(char)*400);
                char*filename1=(char*)malloc(sizeof(char)*140);
                int file_len1=strlen(commands_pipelist[1]);
                int file_i1=0;
                for(int a=0;a<file_len1;a++){
                    if(commands_pipelist[1][a]!=' ' && commands_pipelist[1][a]!='\t'){
                        filename1[file_i1++]=commands_pipelist[1][a];
                    }
                }
                filename1[file_i1]='\0';
                snprintf(pathfile1,400,"%s/%s",path,filename1);
                int file1=open(pathfile1,O_RDONLY);
                if(file1<0){
                    printf("Input file not found1\n");
                    return;
                }

                char*pathfile2=(char*)malloc(sizeof(char)*400);
                char*filename2=(char*)malloc(sizeof(char)*140);
                int file_len2=strlen(commands_pipelist[2]);
                int file_i2=0;
                for(int a=0;a<file_len2;a++){
                    if(commands_pipelist[2][a]!=' ' && commands_pipelist[2][a]!='\t'){
                        filename2[file_i2++]=commands_pipelist[2][a];
                    }
                }
                filename2[file_i2]='\0';
                 snprintf(pathfile2,400,"%s/%s",path,filename2);
                int val1=access(pathfile2,F_OK);
                int file2;
                if(double_redirect){
                    if(val1==-1){
                    file2=open(pathfile2, O_WRONLY | O_APPEND | O_CREAT, 0644);
                    }else{
                        file2=open(pathfile2, O_WRONLY | O_APPEND, 0644); 
                    }
                }else{
                    if(val1==-1){
                    file2=open(pathfile2, O_WRONLY  | O_CREAT | O_TRUNC, 0644);
                    }else{
                        file2=open(pathfile2, O_WRONLY | O_TRUNC, 0644); 
                    }
                }

                if(file2<0){
                    printf("Input file not found2\n");
                    return;
                }


                if(del_used[0]=='<' && del_used[1]=='>'){
                    if (dup2(file1, STDIN_FILENO) == -1) {
                       perror("dup2");
                       return;
                    }
                    close(file1);
                    if (dup2(file2, STDOUT_FILENO) == -1) {
                       perror("dup2");
                       return;
                    }
                    close(file2);
                    int len=strlen(commands_pipelist[0]);
                    char* commands_pipe=(char*)malloc(sizeof(char)*(len+1));
                    char* store_commands_pipe=(char*)malloc(sizeof(char)*(len+1));
                    strcpy(commands_pipe,commands_pipelist[0]);
                    strcpy(store_commands_pipe,commands_pipelist[0]);
                    runcommand(q,comm_saved,commands_pipe,store_commands_pipe);
                    if (dup2( prev_stdin, STDIN_FILENO) == -1) {
                       perror("dup2");
                       return;
                    }
                    if (dup2( prev_stdout, STDOUT_FILENO) == -1) {
                       perror("dup2");
                       return;
                    }
                }
                free(path);
                free(filename1);
                free(pathfile1);
                free(filename2);
                free(pathfile2);
            }
        }
 
     for(int k=0;k<j;k++){
        free(commands_pipelist[k]);
     }
     free(commands_pipelist);
    return;
        
}
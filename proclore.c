#include "headers.h"

 void process(char* str_pid,int current){
    int pid;
    if(current!=-1){
       pid=current;
    }else{
       pid==atoi(str_pid);
    }
    
    char path[300];
    snprintf(path,300,"/proc/%d/status",pid);
    FILE* f=fopen(path,"r");
    if(f==NULL){
        printf("Process Not found with pid:%d\n",pid);
        return;
    }
    char status_file[2];
    char size_file[10];
    char store_statusfile[1024];
    int line=1;
    while (fgets(store_statusfile,1024,f)) {
        
        if (strncmp(store_statusfile, "State:", 6) == 0) {
            sscanf(store_statusfile, "State: %s", status_file);
        }
        
        if (strncmp(store_statusfile, "VmSize:", 7) == 0) {
            //  char*toka=strtok(store_statusfile," \t");
            //  toka=strtok(NULL," \t");
             int i=0;
             while(store_statusfile[i]!=' ' && store_statusfile[i]!='\t'){i++;}
             while(store_statusfile[i]==' ' || store_statusfile[i]=='\t'){i++;}
             int j=0;
              while(store_statusfile[i]!=' ' && store_statusfile[i]!='\t'){
                size_file[j]=store_statusfile[i];
                j++;
                i++;
                }
             size_file[j]='\0';
            // printf("found\n");
             break;
        }

    }

    char executable_size[300];
     snprintf(path,300,"/proc/%d/exe",pid);
     int perform=readlink(path,executable_size,300);
     if(perform==-1){
        strcpy(executable_size,"Executable Path Not found");
     }

     int gpid=__getpgid(pid);
     if(gpid==-1){
        printf("Error founding gpid\n");
     }

     printf("pid :%d\n",pid);
     printf("process Status :%s\n",status_file);
     printf("Process Group :%d\n",gpid);
     printf("Virtual memory :%s\n",size_file);
     printf("executable Path :%s\n",executable_size);

return;
}
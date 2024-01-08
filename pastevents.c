#include "headers.h"

void store_comm(char** ptr){
    int count=0;
    FILE*A=fopen(file_path,"r");
    if(A==NULL){
    return;
    } 
    char*line=(char*)malloc(sizeof(char)*4096);
    
        while(fgets(line,4096,A)){
           strcpy(ptr[count],line);
           count++;
        }
        free(line);
        fclose(A);
        comm_count=count;
        return;

}


int compare_str(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 == ' ' || *str1 == '\t') {
            str1++; 
            continue;
        }
        if (*str2 == ' ' || *str2 == '\t') {
            str2++; 
            continue;
        }
        if (*str1 != *str2) {
            return 0;  
        }
        str1++;
        str2++;
    }

     
    while (*str1 == ' ' || *str1 == '\t') {
        str1++;
    }
    while (*str2 == ' ' || *str2 == '\t') {
        str2++;
    }

    return (*str1 == '\0' && *str2 == '\0');  
}

void show_pastevents(char ** ptr){
        for(int i=0;i<comm_count;i++){
            printf("%s",ptr[i]);
        }
        return;
}

void delete(){
       FILE*A=fopen(file_path,"w");
        if(A==NULL){
        perror("Error opening file");
        return;
        } 
        comm_count=0;
        fclose(A);
        return;
}

void store(char* command,char**ptr){
    
    if(comm_count>0){
        int r=comm_count;
        int cond=compare_str(ptr[r-1],command);
        if(cond==1){
            return;
        }
    }
    int len=strlen(command);
    char* m=(char*)malloc(sizeof(char)*len);
    strcpy(m,command);
    
     if(comm_count<15){
         strcpy(ptr[comm_count],command);
         comm_count=comm_count+1;
   FILE*file = fopen(file_path, "a"); 
   if (file == NULL) {
        perror("Error opening the file");
        return;
    }
  
         fprintf(file,"%s",command); 
         fclose(file);
     }else{
 
    for (int i=0;i<14;i++) {
        strcpy(ptr[i],ptr[i+1]);
    }
     strcpy(ptr[14],command);
    
     }
     return;
    }


void  passevents_execute(int index,char**ptr,Queue q){
    if(index>comm_count){
        printf("Wrong Index\n");
        return;
    } 
    
    
    int r=comm_count;
    int cal_index=r-index;
    store(ptr[cal_index],ptr);
    int len=strlen(ptr[cal_index]);
    char* input=(char*)malloc(sizeof(char)* (len+1));
    char* sinput=(char*)malloc(sizeof(char)* (len+1));
    strcpy(input,ptr[cal_index]);
    strcpy(sinput,ptr[cal_index]);
    runcommand(q,ptr,input,sinput);
    return;
}

void format_change(char**ptr){
        FILE*file = fopen(file_path, "w"); 
        if (file == NULL) {
            perror("Error opening the file");
            return;
        }
         for(int i=0;i<comm_count;i++){
            fprintf(file,"%s",ptr[i]);
         }
        fclose(file);
        return;
}
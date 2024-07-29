#include "headers.h"

typedef struct arr* Arr;

struct arr{
    int pid;
    char*name;
    char Status[11];
};

int compare_func(const void *a, const void *b) {
     Arr A=(Arr)a;
     Arr B=(Arr)b;
     return strcmp(A->name,B->name);
}

void activities(Queue q){
    int elements=q->element;
    Arr starr=(Arr)malloc(sizeof(struct arr)*(elements));
    Queue temp=q->next;
    int i=0;
    while(temp!=NULL){
        int pid=temp->element;
         char path[300];
        snprintf(path,300,"/proc/%d/status",pid);
        FILE* f=fopen(path,"r");
        if(f==NULL){
            temp=temp->next;
            continue;
        }
        char status_file[2];
        char store_statusfile[1024];
        while (fgets(store_statusfile,1024,f)){
            if (strncmp(store_statusfile, "State:", 6) == 0) {
            sscanf(store_statusfile, "State: %s", status_file);
            break;
        }
        }

        if(status_file[0]=='Z'){
            delete(pid);
            fclose(f);
            continue;
        }
        
        int size=strlen(temp->str);
        starr[i].name=(char*)malloc(sizeof(char)*(size+1));
        strcpy(starr[i].name,temp->str);
        starr[i].pid=pid;
        if(status_file[0]=='S' || status_file[0]=='R'){
            strcpy(starr[i].Status,"Running\0");
        }else if( status_file[0]=='T'){
            strcpy(starr[i].Status,"Stopped\0");
        }else{
            strcpy(starr[i].Status,"Nostatus\0");
        }

        fclose(f);
        temp=temp->next;
        i++;
    }

    if(i!=0){
    qsort(starr,i, sizeof(struct arr), compare_func);
    
    for(int j=0;j<i;j++){
        printf("%d : %s - %s\n",starr[j].pid,starr[j].name,starr[j].Status);
    }
    }
    for(int h=0;h<i;h++){
        free(starr[h].name);
    }
    free(starr);
    return;

}
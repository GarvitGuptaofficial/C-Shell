#include "headers.h"


 char* convertdir_to_original(char*dir){
    char *arr;
    if(strlen(dir)==1 && (strcmp(dir,"")==0 || strcmp(dir,".")==0 || strcmp(dir,"..")==0 || strcmp(dir,"-")==0)){
        return dir;
    }else{
        if(dir[0]=='~'){
            int dlen=strlen(dir);
            int ilen=strlen(initial_dir);
            int g= dlen+ilen;
            arr=(char*)malloc(sizeof(char)*g);
            int i=0;
            for(;i<ilen;i++){
                arr[i]=initial_dir[i];
            }
            for(;i<g-1 ;i++){
                arr[i]=dir[i-(ilen-1)];
            }
            arr[i]='\0';
        }else{
            return dir;
        }
    }
    return arr;
}

char* covert_to_prompt(char*A,char*B){
    int a=strlen(A);
    int b=strlen(B);
    char*arr;
    if( a<b){
        return A;
    }else{
        int f=1;
        int i=0;
        while(i<b){
            if(A[i]!=B[i]){
                f=0;
                break;
            }
            i++;
        }
          
        if(f==1){
            
            int l=2+a-b;
            arr=(char*)malloc(sizeof(char)*l);
            int j=0;
            arr[j++]='~';
            while(j<l-1){
            arr[j]=A[j+b-1];
            j++;
            }
            arr[j]='\0';
        }else{
            return A;
        }
    }
        return arr;
}

   char* convert_to_print(char*dir){
    char*arr;
    if(dir[0]=='~'){
        struct passwd *home_dir = getpwuid(getuid());
       int a=strlen(home_dir->pw_dir);
       int b=strlen(dir);
       arr=(char*)malloc(sizeof(char)*350);
       int i=0;
       for(;i<a;i++){
        arr[i]=home_dir->pw_dir[i];
       }
       
       
       int j=1;
       for(;j<b;j++){
        arr[i+j-1]=dir[j];
       }
       arr[i+j-1]='\0';
     

    }else{
        return dir;
    }
    return arr;
}

void change_dir(char*dir,int c){
    char*dir_change=convertdir_to_original(dir);

    // Previous Directory Saving
    char curr_warp_dir[256];
    if(getcwd(curr_warp_dir,sizeof(curr_warp_dir))==NULL){
    perror("Not able to open current directory\n");
    }
     strcpy(prev_dir,covert_to_prompt(curr_warp_dir,initial_dir));


     //Current Directory Changing
    if(strcmp(dir_change,"")==0 || strcmp(dir_change,"~")==0){
       if (chdir(initial_dir) != 0) {
        printf("Error opening following Directory %s",dir);
        return;
    } 
    }else{
     if (chdir(dir_change) != 0) {
        printf("Error opening following Directory %s",dir);
        return;
    } 
    }

    //Getting Current Directory
    if(getcwd(curr_warp_dir,sizeof(curr_warp_dir))==NULL){
    perror("Not able to open current directory\n");
    return;
    }

    char*w=covert_to_prompt(curr_warp_dir,initial_dir);
    strcpy(curr_dir,w);
     char*e=convert_to_print(w);
     prevdir_condition=1;
     if(c){
    printf("%s\n",e);
     }
}
 //c 0 for not printing path
 //c 1 for printing path
void warp_func(char* dir,int c){
    if(strcmp(dir,"-")==0 && prevdir_condition==0){
        printf("OLDPWD not set\n");
    }else if(strcmp(dir,"-")==0 && prevdir_condition==1){
        change_dir(prev_dir,c);
    }else{
    change_dir(dir,c);
    }   
   return;
}
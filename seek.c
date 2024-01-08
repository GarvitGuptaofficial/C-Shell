#include "headers.h"

int check_names(char *search,char *file) {
    int cond=0;
     int search_l = strlen(search);
    for(int i=0;i<search_l;i++){
        if(search[i]=='.'){
            cond=1;
            break;
        }
    }
     int file_l=0;
     if(cond){
        file_l=strlen(file);
     }else{
     while(file_l<strlen(file) && file[file_l]!='.'){
         file_l++;
     }
     }
    if(search_l==file_l){
        if(strncmp(search,file,search_l)==0) {
            return 1; 
        }
    }
    return 0;  
}

char* give_relpath(char*A,char*B){
       int a=strlen(A);
       int b=strlen(B);
       if(b<a){
        return NULL;
       }
       char*arr=(char*)malloc(sizeof(char)*(b-a+1));
       arr[0]='.';
       int i;
       for(i=a;i<b;i++){
        arr[i-(a-1)]=B[i];
       }
       arr[i]='\0';
       return arr;
}
//0 for  none
//1 for -d
//2 for -f
//3 for -e
//4 for -e -d
//5 for -e -f



void search_seek_count(char*search,char*path,int*file_count,int*dir_count,char*copy_path ){
       struct dirent *store_files;
       DIR *dir = opendir(path);
       if (dir == NULL) {
        perror("opendir");
        return;
       }
        store_files=readdir(dir);
        while((store_files=readdir(dir))!=NULL){
            if(strcmp(store_files->d_name,".")==0 || strcmp(store_files->d_name,"..")==0){
                continue;
            }
            int r=strlen(path);
            char*file_path=(char*)malloc(sizeof(char)*(200+r));
            snprintf(file_path,200+r,"%s/%s",path,store_files->d_name);

        struct stat files_stat;
            if (stat(file_path,&files_stat)==-1) {
                continue;
            }

        if(S_ISDIR(files_stat.st_mode)){
            if(check_names(search,store_files->d_name)){
               *dir_count=*dir_count+1;
               strcpy(copy_path,file_path);
            }
            search_seek_count(search,file_path,file_count,dir_count,copy_path);
        }else if (check_names(search,store_files->d_name)) {
            *file_count=*file_count+1;
            strcpy(copy_path,file_path);
        }
        
        }
        return;
}


void search_seek(char*search,char*path,int flag_cond,char* ori_path){
       struct dirent *store_files;
       DIR *dir = opendir(path);
       if (dir == NULL) {
        perror("opendir");
        return;
       }
        store_files=readdir(dir);
        while((store_files=readdir(dir))!=NULL){
            if(strcmp(store_files->d_name,".")==0 || strcmp(store_files->d_name,"..")==0){
                continue;
            }
            int r=strlen(path);
            char*file_path=(char*)malloc(sizeof(char)*(200+r));
            snprintf(file_path,200+r,"%s/%s",path,store_files->d_name);

        struct stat files_stat;
            if (stat(file_path,&files_stat)==-1) {
                printf("Missing File Permission : %s\n",file_path);
                continue;
            }

        if(S_ISDIR(files_stat.st_mode)){
            if(flag_cond!=2 && flag_cond!=5 && check_names(search,store_files->d_name)){
               char*rel_path=give_relpath(ori_path,file_path);
               if(rel_path==NULL){
                printf("Rel Path Not found\n");
               }else{
                printf("%s\n",rel_path);
               }
            }
            search_seek(search,file_path,flag_cond,ori_path);
        }else if ( flag_cond!=1  && flag_cond!=4 && check_names(search,store_files->d_name)) {
            char*rel_path=give_relpath(ori_path,file_path);
               if(rel_path==NULL){
                printf("Rel Path Not found\n");
               }else{
                printf("%s\n",rel_path);
               }
        }
        
        }
        return;
}



void seek(char*search,char*target_dir,int flag_cond){
      char*path=convertdir_to_original(target_dir);
      if(strcmp(path,"-")==0){
        if(prevdir_condition){
            strcpy(path,prev_dir);
        }else{
            return;
        }
      }
       if(flag_cond<3){
      search_seek(search,path,flag_cond,path);
       }else{
           int dir=0;
           int file=0;
           char*copy_path=(char*)malloc(sizeof(char)*300);
           search_seek_count(search,path,&file,&dir,copy_path);
           if(file==0 && dir==0){
            printf("No matches found\n");
            return;
           }
           if(((dir==1 && file==0) || (file==1 && dir==0))){
            //    search_e(search,path,flag_cond,path,copy_path);
              
            if(flag_cond!=5){
               char*rel_path=give_relpath(path,copy_path);
               if(rel_path==NULL){
                printf("Rel Path Not found\n");
               }else{
                printf("%s\n",rel_path);
                warp_func(copy_path,0);
                return;
               }
            
        }else if ( flag_cond!=4) {
            char*rel_path=give_relpath(path,copy_path);
               if(rel_path==NULL){
                printf("Rel Path Not found\n");
               }else{
                printf("%s\n",rel_path);
                FILE *f=fopen(copy_path,"r");
                if(f==NULL){
                    printf("Missing file permission%s\n",search);
                    return;
                }
                char buffer[500];
                while(fgets(buffer,500,f)!=NULL){
                    printf("%s",buffer);
                }
                fclose(f);
               }
           }
           }else{
                search_seek(search,path,flag_cond,path);
           }
       }
       return;
}
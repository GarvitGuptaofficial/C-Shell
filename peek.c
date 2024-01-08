#include "headers.h"

void information_about_file(struct dirent * dir_info,char *dir_path) {
    struct stat fileinfo;
    if (stat(dir_path,&fileinfo)==-1) {
         printf("Stat not working\n");
        return;
    }

    printf((S_ISDIR( fileinfo.st_mode)) ? "d" : "-");
    printf(( fileinfo.st_mode & S_IRUSR) ? "r" : "-");
    printf(( fileinfo.st_mode & S_IWUSR) ? "w" : "-");
    printf(( fileinfo.st_mode & S_IXUSR) ? "x" : "-");
    printf(( fileinfo.st_mode & S_IRGRP) ? "r" : "-");
    printf(( fileinfo.st_mode & S_IWGRP) ? "w" : "-");
    printf(( fileinfo.st_mode & S_IXGRP) ? "x" : "-");
    printf(( fileinfo.st_mode & S_IROTH) ? "r" : "-");
    printf(( fileinfo.st_mode & S_IWOTH) ? "w" : "-");
    printf(( fileinfo.st_mode & S_IXOTH) ? "x" : "-");

    struct passwd *username = getpwuid(fileinfo.st_uid);
    struct group *grp = getgrgid(fileinfo.st_gid);
    printf(" %s %s", ( username != NULL) ?  username->pw_name : "unknown", (grp != NULL) ? grp->gr_name : "unknown");
    printf(" %lld",(long long)fileinfo.st_size);

    char  arr[30];
    struct tm * tinfo = localtime(& fileinfo.st_mtime);
    strftime(arr,sizeof(arr),"%b %d %H:%M",tinfo);
    printf(" %s",arr);

// white -- regular files
// green -- executables
// blue -- directories


  if( dir_info->d_type==DT_DIR){
    printf("\033[34m");
    printf(" %s\n",dir_info->d_name);
    printf("\033[0m");
  }else if(fileinfo.st_mode & S_IXUSR){
    printf("\033[32m");  
    printf(" %s\n",dir_info->d_name);
    printf("\033[0m");
  }else if( dir_info->d_type==DT_REG){
    printf("\033[37m");  
    printf(" %s\n",dir_info->d_name);
    printf("\033[0m");  
  }
}

int hidden_filter(const struct dirent * q){
    if(q->d_name[0]=='.'){
        return 0;
    }
    return 1;
}

// 0 for ls
// 1 for ls -l
// 2 for ls -a
// 3 for ls -l-a

void peek(char*path,int condition){
  char*argument;
  if(strcmp(path,"-")==0 && prevdir_condition==0){
           printf("First Set OLDPWD to use Peek\n");
           return;
  }else if(strcmp(path,"-")==0 && prevdir_condition==1){
     argument=convertdir_to_original(prev_dir);
  }else{
     argument=convertdir_to_original(path);
  }
    struct dirent** m;
    int w;
    
    if(condition==0 || condition==2){
         if(condition==0){
        w=scandir(argument,&m,hidden_filter,alphasort);
        }else{
          w=scandir(argument,&m,NULL,alphasort);   
        }
        if(w==-1){
            perror("Scandir Failed\n");
            return;
        }
        for(int i=0;i<w;i++){
            printf("%s\n",m[i]->d_name);
            free(m[i]);
        }
        free(m);
    }else if(condition==1 || condition==3){

        int w;
        if(condition==1){
        w=scandir(argument,&m,hidden_filter,alphasort);
        }else{
          w=scandir(argument,&m,NULL,alphasort);   
        }
        if(w==-1){
            perror("Scandir Failed\n");
            return;
        }
             int a=strlen(argument);
        for(int i=0;i<w;i++){
            int b=strlen(m[i]->d_name);
             char*arr=(char*)malloc(sizeof(char)*(a+b+2));
              strcpy(arr,argument);
              arr[a]='/';
               for(int j=a+1;j<a+b+1;j++){
                arr[j]=m[i]->d_name[j-(a+1)];
               }
               arr[a+b+1]='\0';
              information_about_file(m[i],arr);
            free(arr);
            free(m[i]);
        } 
        free(m);
    } 


    }
    
  
#include "headers.h"
void prompt() {
    
   
    char username[256];

    struct passwd *pw = getpwuid(getuid());
    if(pw==0){
        perror("System Name not found");
        return;
    }else if(gethostname(username,sizeof(username))!=0){
        perror("User Name not found");
        return;
    }
       printf("<%s@%s:%s %s>",pw->pw_name,username,curr_dir,promptprocess);
 
     
    
}

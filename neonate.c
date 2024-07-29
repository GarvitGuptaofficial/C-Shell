#include "headers.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;


void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}
 
int breaking=0;




void print_latestprocess(int time){
    char*path=(char*)malloc(sizeof(char)*250);
    strcpy(path,"/proc/loadavg\0");
    while(1){
   FILE* file=fopen(path,"r");
    if(file==NULL){
        printf("No able to retrieve Latest process pid\n");
        return;
    }
    int latestpid;
    fscanf(file,"%*f %*f %*f %*s %d",&latestpid);
    printf("%d\n",latestpid);
    fclose(file);
    sleep(time);
    }
    free(path);
    return;
}

void neonate(int time){
    char c;
     enableRawMode();
    int id=fork();
    if(id==0){
        print_latestprocess(time);   
    }else if(id>0){  
     setbuf(stdout, NULL);
        while (read(STDIN_FILENO, &c, 1) == 1) {
             if(c=='x'){
                kill(id,SIGKILL);
                break;
             }     
        }
    }
      disableRawMode(); 

    return; 
}
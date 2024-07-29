#include "headers.h"

void man_func(char*command){

    struct sockaddr_in man_address;
    struct hostent* man_server;
    man_server=gethostbyname("man.he.net");
    if(man_server==NULL){
        printf("Not able to resolve DNS\n");
        return;
    }
    int man_socket_fd=socket(AF_INET, SOCK_STREAM, 0);
    if(man_socket_fd<0){
        printf("Not able to open socket\n");
        return;
    }
    man_address.sin_port=htons(80);
    man_address.sin_family=AF_INET;
    int len=man_server->h_length;
    memcpy(& man_address.sin_addr,man_server->h_addr,man_server->h_length);
     connect(man_socket_fd,(struct sockaddr*)&man_address,sizeof(man_address));
    char*link=(char*)malloc(sizeof(char)*600);
    snprintf(link,600, "GET http://man.he.net/?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command);
    int e=write(man_socket_fd, link, strlen(link));
    if(e<0){
        return;
    }

    char*buffer=(char*)malloc(sizeof(char)*1024);
    char*line=(char*)malloc(sizeof(char)*1024);
    int start=0;
   int lenline = 0;
   int l;
   int skip_cond=0;
    while ((l = read(man_socket_fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < l; i++) {
            if(buffer[i]=='<'){
               skip_cond=1;
            }

            if(buffer[i]=='>'){
                skip_cond=0;
            }

            if (buffer[i] == '\n') {
                line[lenline] = '\0'; 
                    if(strncmp(line,"NAME",4)==0){
                    start=1;
                    }
                    if(start==1){
                    printf("%s\n", line);
                    }
                lenline = 0;
            } else if (lenline < 1024) {
                if(skip_cond==1 || buffer[i]=='>'){
                    continue;
                }
                line[lenline++] = buffer[i];
                
            }
        }
    }
    free(buffer);
    free(line);
    free(link);
    close(man_socket_fd);
return;
}

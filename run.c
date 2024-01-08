#include "headers.h"

void runcommand(Queue q,char**comm_saved,char*input,char*store_command){
int store_comm_cond=1;
        int del_count=0;
        input[strcspn(input,"\n")] = '\0';
        int input_len=strlen(input);
        char del_used[100];
        for(int i=0;i<input_len;i++){
             if(input[i]=='&' || input[i]==';'){
                   del_used[del_count++]=input[i];  
             }
        }
        if(!(input[input_len-1]=='&' || input[input_len-1]==';')){
            del_used[del_count++]='0';
        }
         
        char delimiter[]="\n;&";
        char* tok=strtok(input,delimiter);
        char** commandlist=(char**)malloc(sizeof(char*)*(del_count));
        int i=0;
        while(tok!=NULL){   
            int r=strlen(tok);
            commandlist[i]=(char*)malloc(sizeof(char)*(r+2));
            strcpy(commandlist[i],tok);
            
            
            i++;
            tok=strtok(NULL,delimiter);
        }

        int j=0;
        while(j<del_count){
            int r=strlen(commandlist[j]);
            char* copy_comm=(char*)malloc(sizeof(char)*(r+1));
            strcpy(copy_comm,commandlist[j]); 
              
            
            char*tok_ele=strtok(copy_comm," \t");
            int not_comm=1;
            while(tok_ele!=NULL){
                not_comm=1;

            if(strcmp(tok_ele,"warp")==0){
                tok_ele=strtok(NULL," \t");
                int condition=1;
                while(tok_ele!=NULL){
                warp_func(tok_ele,1);
                condition=0;
                tok_ele=strtok(NULL," \t");
               }
               if(condition){
                    warp_func(curr_dir,1);
               }
               not_comm=0;
            }else if(strcmp(tok_ele,"peek")==0){
                tok_ele=strtok(NULL," \t");
                    int correct_option=1;
                int arr[4]={0,0,0,0};
                while( tok_ele!=NULL && tok_ele[0]=='-' ){
                    int hyp=0;
                    int len=strlen(tok_ele);
                    int s=0;
                    while(s<len){
                        if(tok_ele[s]=='-'){
                            arr[2]++;
                            hyp++; // For "-"
                        }else if(tok_ele[s]=='l'){
                            arr[1]++; //For "l"
                        }else if(tok_ele[s]=='a'){
                            arr[0]++; // For 'a'
                        }else{
                            arr[3]++;
                        }
                        s++;
                    }
                    if(hyp>1){
                        correct_option=0;
                    } 
                   
                    tok_ele=strtok(NULL," \t");
                }
                 if(arr[3]!=0){
                        correct_option=0;
                    }
                if(!(arr[0]+arr[1]>=arr[2]  && arr[0]<2 && arr[1]<2)){
                    correct_option=0;
                }

                int condition=1;
                int option;
                if(arr[0]==0 && arr[1]==0){
                    option=0; // ls
                }else if(arr[0]==0 && arr[1]==1){
                    option=1; // ls -l
                }else if(arr[0]==1 && arr[1]==0){
                    option=2; // ls -a
                }else if(arr[0]==1 && arr[1]==1){
                    option=3;  // ls -a -l
                }
            if(correct_option){
                while(tok_ele!=NULL){
                peek(tok_ele,option);
                condition=0;
                tok_ele=strtok(NULL," \t");
               }
               if(condition){
                 peek(curr_dir,option);
               }
               not_comm=0;
            }else{
                printf("Invalid Flags\n");
            }
            }else if(strcmp(tok_ele,"pastevents")==0){
               tok_ele=strtok(NULL," \t");
               int option=0;  // only pastevents
               char num_str[2];
                while(tok_ele!=NULL){
                if(strcmp(tok_ele,"purge")==0){
                    option=1;  // for purge
                }else if(strcmp(tok_ele,"execute")==0){
                    option=2;  // for execute
                }else if(option==2){
                    option=3;
                    int r=2;
                    int l=strlen(tok_ele);
                    if(l<r){
                        r=l;
                    }
                    strncpy(num_str,tok_ele,r);
                }
                
                tok_ele=strtok(NULL," \t");
                }

                if(option==0){
                    show_pastevents(comm_saved);
                    store_comm_cond=0;
                }else if(option==1){
                    delete();
                    store_comm_cond=0;
                }else if( option==3){
                    store_comm_cond=0;
                    int num=atoi(num_str);
             
                    if(num>0 && num<15){
                        passevents_execute(num,comm_saved,q);
                    }else{
                        printf("Can't use pastevents execute\n");
                    }
                }else{
                    printf("Not a command\n");
                }
                not_comm=0;
            }else if(strcmp(tok_ele,"proclore")==0){
                 tok_ele=strtok(NULL," \t");
                 int condition=1;
                 while(tok_ele!=NULL){
                    condition=0;
                    process(tok_ele,-1);
                    tok_ele=strtok(NULL," \t");
                 }
                 if(condition){
                    int p=getpid();
                    process(" ",p);
                 }
                 not_comm=0;
            }else if(strcmp(tok_ele,"seek")==0){
                 tok_ele=strtok(NULL," \t");
                 //arr[0]  -
                 //arr[1]  d
                 //arr[2]  f
                 //arr[3]  e
                 int arr[5]={0,0,0,0,0};
                    int correct_option=1;
                  while( tok_ele!=NULL && tok_ele[0]=='-' ){
                    int hyp=0;
                    int len=strlen(tok_ele);
                    int s=0;
                    while(s<len){
                        if(tok_ele[s]=='-'){
                            arr[0]++;  
                            hyp++;
                        }else if(tok_ele[s]=='d'){
                            arr[1]++;  
                        }else if(tok_ele[s]=='f'){
                            arr[2]++;  
                        }else if(tok_ele[s]=='e'){
                            arr[3]++;
                        }else{
                            arr[4]++;
                        }
                        s++;
                    }
                    if(hyp>1){
                        correct_option=0;
                    }
                    // printf("%s1\n",tok_ele);
                    tok_ele=strtok(NULL," \t");
                }
                   if(arr[4]!=0){
                    correct_option=0;
                   }
                   else if((arr[1]+arr[2]+arr[3]>=arr[0]) && (arr[1]<=1 && arr[2]<=1 && arr[3]<=1)){
                          if(arr[1]==1 && arr[2]==1){
                            correct_option=0;
                          }
                   }else{
                            correct_option=0;
                   }

                    int option;
                if(arr[1]==0 && arr[2]==0 && arr[3]==0){
                    option=0; // none
                }else if(arr[1]==1 && arr[2]==0 && arr[3]==0){
                    option=1; //  d
                }else if(arr[1]==0 && arr[2]==1 && arr[3]==0){
                    option=2; //  f
                }else if(arr[1]==0 && arr[2]==0 && arr[3]==1){
                    option=3;  //  e
                }else if(arr[1]==1 && arr[2]==0 && arr[3]==1){
                    option=4;  // d e
                }else if(arr[1]==0 && arr[2]==1 && arr[3]==1){
                    option=5;  // f e
                }
                char search[100];
                char target[256];
                int q=0;
                if(correct_option){
                while(tok_ele!=NULL){
                if(q==0){
                    strcpy(search,tok_ele);
                }
                 q++;
                 if(q==2){
                    strcpy(target,tok_ele);
                } 
                tok_ele=strtok(NULL," \t");
               }
                if(q==2){
                    seek(search,target,option);
                    not_comm=0;
               }else if(q==1){
                char cu[2];
                cu[0]='.';
                cu[1]='\0';
                    seek(search,cu,option);
                    // printf("%s %s %d\n",search,cu,option);
                      not_comm=0;
               } 
                }else{
                    printf("Invalid Flags\n");
                    not_comm=0;
                }
               
              
            }
            
            // if(not_comm){
            //     printf("Command Not Found:%s\n",commandlist[j]);
            // }else{
            //     //store command
            // }
                tok_ele=strtok(NULL," \t");
            // }

        }
         
         if(not_comm==1){
            int cond;
            if(del_used[j]!='&'){
                cond=0;
            }else{
                cond=1;
            }
            fore_back(commandlist[j],cond,q);
         }
            j++;
    }
     if(store_comm_cond){
        store(store_command,comm_saved);
        if(comm_count==15){
            format_change(comm_saved);
        }
     }
     
     
    
    return;
}
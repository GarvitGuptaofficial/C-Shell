#include "queue.h"

 
void Push(Queue head,int val,char*com){
      Queue f=(Queue)malloc(sizeof(struct queue));
      f->element=val;
      f->next=NULL;
      int len=strlen(com);
      f->str=(char*)malloc(sizeof(char)*len);
      strcpy(f->str,com);

      if(head->next==NULL){
       head->next=f;
        head->rear=f;
      }else{
    Queue back=head->rear;
    back->next=f;
    head->rear=f;
      }
    head->element++;  
} 

int Pop(Queue head){

    Queue temp=head->next;

    if(temp==NULL){
        return -1;
    }
    
    int e=temp->element;

    if(temp->next==NULL){
        head->next=NULL;
        free(temp);
    }else{
        Queue store=temp->next;
        head->next=store;
        free(temp);
    }
    head->element--;
    return e;
}

void find_delete(Queue head,int e){
    Queue prev=NULL;
    Queue temp=head->next;
    while(temp!=NULL){
        if(temp->element==e){
            if(prev==NULL){
                free(head->next);
                head->next=NULL;
                head->rear=NULL;
                head->element--;
                break;
            }else{
                prev->next=temp->next;
                if(temp==head->rear){
                    head->rear=prev;
                }
                free(temp);
                 head->element--;
                break;
            }
        }
        prev=temp;
        temp=temp->next;
    }
    return;
}


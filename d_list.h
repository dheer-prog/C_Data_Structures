#include <stdlib.h>
#include <stdio.h>
typedef struct list list; 
struct list{
    void* data; 
    list* next; 
    list* prev; 
};
void* init(){
    list* l=(list*)malloc(sizeof(list)); 
    l->next=NULL; 
    l->prev=NULL; 
    l->data=NULL;
    return (void*)(l); 
}
#define insert_list(t,value)\
do{\
    typeof(value)* d=(typeof(value)*)malloc(sizeof(value));\
    *d=value;\
    if(t->data==NULL){\
        t->data=d;\
        break;\
    }\
    list* nexter=t->next;\
    list* t_next=(list*)(malloc(sizeof(list)));\
    t->next=t_next;\
    t_next->data=d;\
    t_next->prev=t;\
    t_next->next=nexter;\
    if(nexter!=NULL){\
        nexter->prev=t_next;\
    }\
}while(0)

void erase(list* t){
    list* prev=t->prev; 
    list* next=t->next; 
    if(prev!=NULL){
        prev->next=next;
    }
    if(next!=NULL){
        next->prev=prev;
    }
    t->prev=NULL; 
    t->next=NULL;
    free(t->data);  
    free(t); 
    return; 
}
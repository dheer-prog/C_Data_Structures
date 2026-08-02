#include <stdlib.h>
#define list_create(type,name) \
typedef struct name{\
    type data; \
    struct name* prev;\
    struct name* next;\
    unsigned char first;\
} name;
#define list_init(ptr) \
do{\
    ptr=(typeof(*ptr)* )(malloc(sizeof(typeof(*ptr))));\
    ptr->prev=NULL;\
    ptr->next=NULL;\
    ptr->data=(typeof(ptr->data)){0};\
    ptr->first=1;\
}while(0); 


#define insert_list(t,value)\
do{\
    if(t->first==1){\
        t->data=value;\
        t->first=0;\
        break;\
    }\
    typedef typeof(*t) name;\
    name* nexter=t->next;\
    name* t_next=(name*)(malloc(sizeof(name)));\
    t_next->data=value;\
    t_next->prev=t;\
    t_next->next=nexter;\
    t_next->first=0;\
    if(t!=NULL){\
        t->next=t_next;\
    }\
    if(nexter!=NULL){\
        nexter->prev=t_next;\
    }\
}while(0);

#define erase_list(t) do{\
    typedef typeof(*t) name\
    name* prev=t->prev;\
    name* next=t->next;\
    if(prev!=NULL){\
        prev->next=next;\
    }\
    if(next!=NULL){\
        next->prev=prev;\
    }\
    t->prev=NULL; \
    t->next=NULL \
    free(t); \
}while(0); 
 

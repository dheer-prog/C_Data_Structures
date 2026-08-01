
#ifndef D_ARR
#define D_ARR
#include<stdlib.h>
 
 
#define vec_push_back(ptr,val)\
do{\
    if(*(ptr+ptr[-1])==ptr[-2]){\
        ptr=ptr-2; \
        ptr=(typeof(*ptr)*)(realloc(ptr,sizeof(typeof(*ptr))*(ptr[0]*2))); \
        ptr[0]=ptr[0]*2; \
        ptr=ptr+2;\
    }\
    *(ptr+ptr[-1])=val; \
    (ptr[-1])++;\
}\
while(0); 
#define vec_pop_back(ptr)\
{\
    ptr[-1]--; \
    if(ptr[-1]==0){\
        ptr=ptr-2;\
        free(ptr); \
    }\
}\
 
 
#define front(ptr)\
ptr[0]

#define back(ptr)\
*(ptr+ptr[-1]-1)

#define vec_init(capacity,ptr)\
do{\
    ptr=(typeof(*ptr)*)(malloc(sizeof(typeof(*ptr))*(capacity+2))); \
    ptr[0]=capacity; \
    ptr[1]=0; \
    ptr=ptr+2;\
}while(0);
 
#endif 

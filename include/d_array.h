
#ifndef D_ARR
#define D_ARR
#include<stdlib.h>
/*
The size and capacity values are stored in the array itself 
so you'll have to take care of truncation for example for 
if you have a char array of size greater than 128/256
*/
 
#define vec_push_back(ptr,val) do{\
    if(ptr[-1]==ptr[-2]){\
        ptr=ptr-2; \
        ptr=(typeof(*ptr)*)(realloc(ptr,sizeof(typeof(*ptr))*(ptr[0]*2))); \
        ptr[0]=ptr[0]*2; \
        ptr=ptr+2;\
    }\
    ptr[ptr[-1]]=val; \
    ptr[-1]++;\
}while(0); 

#define vec_pop_back(ptr)\
do{\
    ptr[-1]--; \
    if(ptr[-1]==0){\
        ptr=ptr-2;\
        free(ptr); \
    }\
}while(0); 
 
 
#define front(ptr)\
ptr[0]

#define back(ptr)\
*(ptr+ptr[-1]-1)

#define vec_init(ptr,capacity)\
do{\
    ptr=(typeof(*ptr)*)(malloc(sizeof(typeof(*ptr))*(capacity+2))); \
    ptr[0]=capacity; \
    ptr[1]=0; \
    ptr=ptr+2;\
}while(0);
 
#endif 

#ifndef D_P_QUEUE
#define D_P_QUEUE
#include "d_array.h"
#include <limits.h>
#define SWAP(a,b)\
do{\
    typeof(a) temp=a;\
    a=b;\
    b=temp;\
}while(0)

#define p_queue_init(ptr,maxer) do{\
vec_init(ptr,50);\
vec_push_back(ptr,maxer);\
ptr=ptr+1;\
}while(0);

#define p_push(ptr,val)\
do{\
    ptr--; \
    vec_push_back(ptr,val);\
    ptr++; \
    \
    int i=ptr[-2]-2;\
    while(i>=0){\
        int t=(i-1)/2;\
        if(t<0){break;}\
        if(ptr[-1]==0){\
            if(ptr[t]<=ptr[i]){\
                break;\
            }\
            else{\
                SWAP(ptr[t],ptr[i]);\
                \
                i=t;\
            }\
        }\
        else{\
            if(ptr[t]>=ptr[i]){\
                break;\
            }\
            else{\
                SWAP(ptr[t],ptr[i]);\
                \
                i=t;\
            }\
        }\
    } \
}while(0); 
#define p_pop(ptr) do{\
    ptr[0]=ptr[ptr[-2]-2];\
    ptr[-2]--;\
    int i=0;\
    if(ptr[-1]==0){\
        while(i<(ptr[-2]-1)){\
            int i1=(2*i)+1; \
            int i2=(2*i)+2;\
            if(i1>=(ptr[-2]-1)){\
                break;\
            }\
            else if(i1<ptr[-2] && i2>=(ptr[-2]-1)){\
                if(ptr[i]>ptr[i1]){\
                    SWAP(ptr[i],ptr[i1]);\
                }\
                break;\
            }\
            else{\
                if(ptr[i1]<=ptr[i2]){\
                    if(ptr[i1]<ptr[i]){SWAP(ptr[i],ptr[i1]);i=i1;}\
                    else{\
                        break;\
                    }\
                }\
                else{\
                    if(ptr[i2]<ptr[i]){SWAP(ptr[i],ptr[i2]);i=i2;}\
                    else{\
                        break; \
                    }    \
                }\
            }\
        }\
    }\
    else{\
        while(i<(ptr[-2]-1)){\
            int i1=(2*i)+1; \
            int i2=(2*i)+2;\
            if(i1>=ptr[-2]){\
                break;\
            }\
            else if(i1<ptr[-2] && i2>=(ptr[-2]-1)){\
                if(ptr[i]<ptr[i1]){\
                    SWAP(ptr[i],ptr[i1]);\
                }\
                break;\
            }\
            else{\
                if(ptr[i1]>=ptr[i2]){\
                    if(ptr[i1]>ptr[i]){SWAP(ptr[i],ptr[i1]);i=i1;}\
                    else{\
                        break;\
                    }\
                }\
                else{\
                    if(ptr[i2]>ptr[i]){SWAP(ptr[i],ptr[i2]);i=i2;}\
                    else{\
                        break; \
                    }    \
                }\
            }\
        }\
    }\
}while(0); 
#define p_top(ptr) ptr[0]
#endif
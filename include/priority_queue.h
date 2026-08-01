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
typedef struct priority_queue p_queue; 
struct priority_queue{
    vector* v;
    int maxer;
};
static inline p_queue* p_queue_init(size_t size_single,int maxer){
    p_queue* p=(p_queue*)(malloc(sizeof(p_queue)));
    p->v=vec_init(size_single,50);
    p->maxer=maxer;
    return p;
}
#define p_push(p,val)\
do{\
    vec_push_back(p->v,val);\
    \
    int i=(int)p->v->size-1;\
    while(i>=0){\
        int t=(i-1)/2;\
        if(t<0){break;}\
        if(p->maxer==0){\
            if(p->v[t]<=p->v->data[i]){\
                break;\
            }\
            else{\
                SWAP(p->v[t],p->v->data[i]);\
                \
                i=t;\
            }\
        }\
        else{\
            if(p->v[t]>=p->v->data[i]){\
                break;\
            }\
            else{\
                SWAP(p->v[t],p->v->data[i]);\
                \
                i=t;\
            }\
        }\
    } \
}while(0); 
#define p_pop(p) do{\
    p->v[0]=p->v[size-1];\
    p->v->size--;\
    int i=0; \
    if(p->maxer==0){\
        while(i<p->v->size){\
            int i1=(2*i)+1; \
            int i2=(2*i)+2;\
            if(i1>=p->v->size){\
                break;\
            }\
            else if(i1<p->v->size && i2>=p->v->size){\
                if(p->v->data[i]>p->v->data[i1]){\
                    SWAP(p->v->data[i],p->v->data[i1]);\
                    break;\
                }\
            }\
            else{\
                if(p->v->data[i1]<=p->v->data[i2]){\
                    if(p->v->data[i1]<p->v->data[i]){SWAP(p->v->data[i],p->v->data[i1]);i=i1;}\
                    else{\
                        break;\
                    }\
                }\
                else{\
                    if(p->v->data[i2]<p->v->data[i]){SWAP(p->v->data[i],p->v->data[i2]);i=i2;}\
                    else{\
                        break; \
                    }    \
                }\
            }\
        }\
    }\
    else{\
        int i1=(2*i)+1; \
        int i2=(2*i)+2;\
        if(i1>=p->v->size){\
            break;\
        }\
        else if(i1<p->v->size && i2>=p->v->size){\
            if(p->v->data[i]<p->v->data[i1]){\
                SWAP(p->v->data[i],p->v->data[i1]);\
                break;\
            }\
        }\
        else{\
            if(p->v->data[i1]>=p->v->data[i2]){\
                if(p->v->data[i1]>p->v->data[i]){SWAP(p->v->data[i],p->v->data[i1]);i=i1;}\
                else{\
                    break;\
                }\
            }\
            else{\
                if(p->v->data[i2]>p->v->data[i]){SWAP(p->v->data[i],p->v->data[i2]);i=i2;}\
                else{\
                    break; \
                }    \
            }\
        }\
    }\
}while(0); 
#endif

#ifndef D_ARR
#define D_ARR
#include<stdlib.h>
#include<string.h>
typedef struct vector vector;
struct vector{
    void* data; 
    size_t size; 
    size_t max_cap;
    size_t size_single;
};
#define vec_push_back(v,val)\
do{\
    typeof(val)* t=(typeof(val)*)(malloc(sizeof(typeof(val))));\
    *t=val;\
    if(v->size==v->max_cap){\
        void* resized = realloc(v->data, v->max_cap * 2 * v->size_single);\
        if(resized == NULL){\
            break;\
        }\
        v->data = resized;\
        v->max_cap=v->max_cap*2; \
    }\
    memcpy((char *)v->data + v->size * v->size_single, (void*)t, v->size_single);\
    v->size++;\
}\
while(0); 

void* get(vector* v,int index){
    if(index < 0 || (size_t)index >= v->size){return NULL;}
    void* ans=(void *)((char*)v->data+(v->size_single*index)); 
    return ans; 
}
void* front(vector* v){
    return v->data;
}
void* back(vector* v){
    return (void *)((char*)v->data+(v->size_single*(v->size-1))); 
}
void* init(size_t size_single,size_t max_cap){
    if(max_cap==0){
        max_cap=50; 
    }
    vector* v=(vector*)(malloc(sizeof(vector))); 
    v->data=malloc(size_single*max_cap); 
    v->size=0; 
    v->max_cap=max_cap;
    v->size_single=size_single; 
    return (void *)v;
}
#endif 

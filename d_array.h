
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
    void(*push_back)(vector*,void *);
    void* (*get)(vector*,int);
    void* (*front)(vector*); 
    void* (*back)(vector*); 
     
};

void push_back(vector* v,void* val){
    if(v->size==v->max_cap){
        v->data=realloc(v->data,v->max_cap*2);
        v->max_cap=v->max_cap*2; 
    }
    memcpy((char *)v->data + v->size * v->size_single, val, v->size_single);
    v->size++; 
    return; 
}
void* get(vector* v,int index){
    if(index>v->size){return NULL;}
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
    v->push_back=push_back; 
    v->get=get;
    return (void *)v;
}
#endif 
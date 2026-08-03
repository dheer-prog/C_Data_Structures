#ifndef D_PTR
#define D_PTR
#include <stdint.h>

#include "d_list.h"
#define init_bucket_count 20
//The hash function being used
uint64_t splitmix64(uint64_t x)
{
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}
#define umap_create(type_k,type_v,pair_name,name) \
typedef struct pair_name{\
    type_k key;\
    type_v val;\
}pair_name;\
\
list_create(pair_name,name);\
typedef struct umap{\
    name* bucket[init_bucket_count];\
    pair_name* pair_data_type;\
    name* list_data_type;\
    int bucket_count;\
    int elements;\
    int elements_threshold;\
}umap; 

#define umap_init(ptr) do{\
    ptr=(umap *)(malloc(sizeof(umap)));\
    ptr->pair_data_type=(typeof(*(ptr->pair_data_type))*)NULL;\
    ptr->list_data_type=(typeof(*(ptr->list_data_type))*)NULL;\
    ptr->bucket_count=init_bucket_count;\
    ptr->elements=0;\
    ptr->elements_threshold=(3/4)*(ptr->bucket_count);\
    for(int i=0;i<ptr->bucket_count;i++){\
        list_init(ptr->bucket[i]); \
    }\
}while(0); 

#define umap_insert(u,k,v) \
do{\
    if(__builtin_types_compatible_p(typeof(k), typeof(int))){\
        uint64_t h=splitmix64(k); \
        int index=h%(u->bucket_count); \
        typeof(*(u->pair_data_type)) t={k,v};\
        insert_list(u->bucket[index],t);\
        u->elements++;\
    }\
}while(0); 


#define umap_size(u) u->elements

#define umap_erase(u,k) \
do{\
    int found=0;\
    if(__builtin_types_compatible_p(typeof(k), typeof(int))){\
        uint64_t h=splitmix64(k);\
        int index=h%(u->bucket_count);\
        typeof(*(u->list_data_type))* starter=u->bucket[index];\
        while(starter!=NULL){\
            if(starter->data.key==k){\
                erase_list(starter);\
                u->elements--;\
                found=1;\
                break;\
            }\
            starter=starter->next;\
        }\
    }\
}while(0);

#define umap_get(u,k) ({ \
    typeof((u)->pair_data_type->val) _result = (typeof((u)->pair_data_type->val)){0}; \
    int _found = 0; \
    if (__builtin_types_compatible_p(typeof(k), typeof(int))) { \
        uint64_t _h = splitmix64(k); \
        int _index = _h % ((u)->bucket_count); \
        typeof((u)->list_data_type) _root = (u)->bucket[_index]; \
        while (_root != NULL) { \
            if (_root->data.key == (k)) { \
                _result = _root->data.val; \
                _found = 1; \
                break; \
            } \
            _root = _root->next; \
        } \
    } \
    _result; \
})
#endif

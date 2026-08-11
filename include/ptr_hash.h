#ifndef D_ptr
#define D_ptr
#include <stdint.h>

#include "d_list.h"
#define init_bucket_count 20
#ifndef CAT_FUNC
#define CAT_FUNC
#define CAT(a,b) a##b
#define XCAT(a,b) CAT(a,b)
#endif

//The hash function being used
uint64_t splitmix64(uint64_t x)
{
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}
#define umap_create(name_map,type_k,type_v) \
typedef struct XCAT(name_map,__pair__){\
    type_k key;\
    type_v val;\
}XCAT(name_map,__pair__);\
list_create(XCAT(name_map,__pair__),XCAT(name_map,__list__));\
typedef struct name_map{\
    XCAT(name_map,__list__)** bucket;\
    XCAT(name_map,__pair__)* pair_data_type;\
    XCAT(name_map,__list__)* list_data_type;\
    int bucket_count;\
    int elements;\
    int elements_threshold;\
}name_map;


#define umap_init(ptr) do{\
    ptr=(typeof(*ptr) *)(malloc(sizeof(typeof(*ptr))));\
    ptr->pair_data_type=(typeof(*(ptr->pair_data_type))*)NULL;\
    ptr->list_data_type=(typeof(*(ptr->list_data_type))*)NULL;\
    ptr->bucket_count=init_bucket_count;\
    ptr->elements=0;\
    ptr->elements_threshold=10;\
    ptr->bucket=(typeof(*(ptr->list_data_type))**)(malloc(sizeof(typeof(ptr->list_data_type))*init_bucket_count));\
    for(int i=0;i<ptr->bucket_count;i++){\
        list_init(ptr->bucket[i]);\
    }\
}while(0); 

#define map_rehash(u) do{\
    typeof(*u)* ptr=u;\
    printf("REhashing\n"); \
    size_t old_count=u->bucket_count;\
    u->bucket_count=u->bucket_count*2; \
    typeof(*(ptr->list_data_type))** temp=(typeof(*(ptr->list_data_type))**)(malloc(sizeof(typeof(ptr->list_data_type))*u->bucket_count));\
    for(size_t i=0;i<u->bucket_count;i++){\
        list_init(temp[i]); \
    }\
    typeof(*(u->pair_data_type)) __finder_data_type__={0};\
    typeof(__finder_data_type__.key) type_key={0}; \
    typeof(__finder_data_type__.val) type_val={0};     \
    for(size_t i=0;i<old_count;i++){\
        typeof(*(u->list_data_type))* temp_root=u->bucket[i]; \
        while(temp_root!=NULL){\
            if (__builtin_types_compatible_p(typeof(temp_root->data.key), typeof(int))){\
                uint64_t h=splitmix64(temp_root->data.key); \
                int index=h%u->bucket_count;\
                insert_list(temp[index],temp_root->data);\
            }  \
            temp_root=temp_root->next;\
        }\
    }\
    typeof(*(ptr->list_data_type))** to_delete=u->bucket; \
    u->bucket=temp; \
    free(to_delete); \
    u->elements_threshold=u->elements_threshold*2;\
}while(0);

#define umap_insert(u,k,v) \
do{\
    if(__builtin_types_compatible_p(typeof(k), typeof(int))){\
        uint64_t h=splitmix64(k);\
        int index=h%(u->bucket_count);\
        typeof(*(u->pair_data_type)) __temp_inserter={k,v};\
        insert_list(u->bucket[index],__temp_inserter);\
        u->elements++;\
        if(u->elements>=u->elements_threshold){\
            map_rehash(u);\
        }\
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

#define umap_get(u,k) ({\
    typeof((u)->pair_data_type->val) _result = (typeof((u)->pair_data_type->val)){0};\
    int _found = 0;\
    if (__builtin_types_compatible_p(typeof(k), typeof(int))) {\
        uint64_t _h = splitmix64(k);\
        int _index = _h % ((u)->bucket_count);\
        typeof((u)->list_data_type) _root = (u)->bucket[_index];\
        while (_root != NULL) {\
            if (_root->data.key == (k)) {\
                _result = _root->data.val;\
                _found = 1;\
                break;\
            }\
            _root = _root->next;\
        }\
    }\
    _result;\
})
#define uset_create(name_set,type_k) umap_create(name_set,type_k,unsigned char)
#define uset_init(ptr) umap_init(ptr)
#define uset_insert(u,k)({\
    unsigned char __temp__t__=1;\
    umap_insert(u,k,__temp__t__);\
})

#define uset_erase(u,k) umap_erase(u,k)
#define uset_size(u) u->elements
#define uset_get(u,k) umap_get(u,k)  
#endif

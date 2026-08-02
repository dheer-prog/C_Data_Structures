#ifdef D_PTR
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
typedef struct umap umap; 
struct umap{
    list* arr[bucket_count]; 
    int bucket_count=init_bucket_count;
}
static inline umap* umap_init(){
    umap* u=(umap *)(malloc(sizeof(umap)));
    u->bucket_count=init_bucket_count;   
    for(int i=0;i<init_bucket_count;i++){
        u->arr[i]=list_init(); 
        vec_init(u->arr[i],20); 
    }
    return u; 
}
#define umap_insert_ptr(u,k,v) do{\
    uint64_t hash=splitmix64((uintptr_t)k); \
    int index=hash%u->bucket_count; 
    insert_list()
}while(0); \

static inline void* umap_get(umap* u,uintptr_t k){
    uint64_t hash=splitmix64(ptr);
    int index=hash%u->bucket_count; 
}

#endif
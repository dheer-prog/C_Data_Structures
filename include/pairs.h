#ifndef D_PAIR 
#define D_PAIR

#define pair_create(name,type1,type2)\
do{\
    typedef struct name{\
        type1 first;\
        type2 second;\
    }name;\
}while(0); 

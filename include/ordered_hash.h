#ifndef ORD_HASH
#define ORD_HASH
#ifndef CAT_FUNC
#define CAT_FUNC
#define CAT(a,b) a##b
#define XCAT(a,b) CAT(a,b)
#endif 

#define typeof(*ptr) map_type

typedef unsigned char uchar;
#define left_rotate(x) do{\
    typeof(*x)* y=x; \
    x->right=y->left; \
    if(y->left!=NULL){\
        y->left->parent=x; \
    }\
    y->parent=x->parent; \
    if(x->parent==NULL){\
        root=y;\
    }\
    else if(x==x->parent->left){\
        x->parent->left=y; \
    }\
    else{\
        x->parent->right=y;\
    }\
    y->left=x; \
    x->parent=y;\
}while(0); 
#define right_rotate(x) do{\
    typeof(*x)* y=x; \
    x->left=y->right; \
    if(y->right!=NULL){\
        y->right->parent=x; \
    }\
    y->parent=x->parent; \
    if(x->parent==NULL){\
        root=y;\
    }\
    else if(x==x->parent->left){\
        x->parent->left=y; \
    }\
    else{\
        x->parent->right=y;\
    }\
    y->right=x; \
    x->parent=y;\
}while(0); 

#define rb_tree_create(name_rb,type_k,type_v) ({\
typedef struct XCAT(name_map,__pair__){\
    type_k key;\
    type_v val;\
}XCAT(name_rb,__pair__);\
typedef struct name_rb{\
    XCAT(name_rb,__pair__) data;\
    rb_tree* left; \
    rb_tree* right; \
    rb_tree* parent;\
    rb_tree* root; 
    uchar color;    \
    uchar init;\
    size_t count;\
}name_rb;\
create_ptr_checker();})\
 
#define rb_init(ptr)do{\
    ptr=(map_type*)(malloc(sizeof(map_type))); 
    ptr->data={0};
    ptr->left=NULL; 
    ptr->right=NULL; 
    ptr->parent=NULL; 
    ptr->color=1; 
    ptr->root=ptr;
    //1 means black
    ptr->init=0;\
    ptr->is_root=1;\
    ptr>count=0;\
}while(0);

#define __r_b_property__(ptr)do{\
    if(ptr->parent->color==1){break;}\
    map_type* _X_=ptr;\
   \
    while(g!=NULL){\
        map_type* p=_X_->parent;\
        map_type* g=p->parent;\
        if(g==NULL){break;}\
        map_type* u=p->left; \
        if(u==NULL || u->color==1){\
            if(p->left==_X_ && g->left==p){\
                left_rotate(g);\
            }\
            else if(p->right==_X_ && g->right==p){\
                right_rotate(g); \
            }\
            else if(p->left==_X_ && g->right==p){\
                left_rotate(p); \
                right_rotate(g); \
            }\
            else{\
                right_rotate(p); \
                left_rotate(g); \
            }\
        }\
        else{\
            u->color=1; \
            p->color=1; \
            g->color=0; \
            g=_X_;\
        } \
    } \
    ptr->root->color=1;\
}while(0);

//Note this returns an iterator like C++ std::map .find() function
//TODO: Make this change in ptr_hash.h also
#define map_get(ptr,val) ({
    map_type* __result__=ptr->root;
    while(__result__!=NULL && __result__->data!=val){
        if(__result__->data.key<val){
            __result__=__result__->right;
        }
        else{
            __result__=__result__->left; 
        }
    }
    __result__;\
})

#define __bst__insert(ptr,val,val_val)do{\
    map_type* __finder_iter__=map_get(ptr,val);\
    if(ptr!=NULL){\
        ptr->count++;\
        break;\
    }\
    if(ptr->init==0){ptr->data=0;ptr->init=1;break;}\
    map_type* curr=ptr; 
    map_type* prev_ptr=NULL;\
    while(curr!=NULL){\
        prev_ptr=curr; \
        if(curr->data.key>=val){\
            curr=curr->left; \
        }\
        else{\
            curr=curr->right; \
        }\
    }\
    map_type* __temp_new__=(map_type*)(malloc(sizeof(map_type)));\
    //Placing a lot of trust in the user LOL; 
    __temp_new__->data={val,val_val};\
    __temp_new__->init=1;  \
    __temp_new__->parent=prev_ptr;\
    __temp_new__->color=0;\
    if(prev_ptr->data>=val){\
        prev_ptr->left=__temp_new__;\
    }\
    else{\
        prev_ptr->right=__temp_new__;\
    }\
    __temp_new__->root=prev_ptr->root;\
    __r_b_property__(__temp_new__);\
}while(0);
#define get_right_min(ptr) ({
    map_type* returner=ptr; 
    while(returner->right!=NULL){
        returner=returner->right; 
    }
    returner;
})
#define bst_erase(ptr,val) do{
    uchar is_black=0; 
    if(__builtin_types_compatible_p(typeof(ptr), typeof(val))){

    } 
    else{
        _Static_assert(__builtin_types_compatible_p(map_type, typeof(val)),"WRONG DATA TYPE");\
        map_type* must_delete=map_get(ptr,val);\
        is_black=must_delete->color; 
        if(must_delete->left==NULL){
            if(must_delete->parent->left==must_delete){
                must_delete->parent->left=must_delete->right;
            }
            else{
                must_delete->parent->right=must_delete->right;
            }
            must_delete->right->parent=must_delete->parent; 
            free(must_delete);
            break;
        }
        else if(must_delete->right==NULL){
            if(must_delete->parent->left==must_delete){
                must_delete->parent->left=must_delete->left;
            }
            else{
                must_delete->parent->right=must_delete->left;
            }
            must_delete->left->parent=must_delete->parent; 
            free(must_delete); 
            break; 
        }
        //TODO 
        //NEED TO ADD while loop for bst erase
    }
}while(0); 

#endif 
#ifndef ORD_HASH
#define ORD_HASH
#ifndef CAT_FUNC
#define CAT_FUNC
#define CAT(a,b) a##b
#define XCAT(a,b) CAT(a,b)
#endif 
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

#define rb_tree_create(name_rb,type_k,type_v) do{\
typedef struct XCAT(name_map,__pair__){\
    type_k key;\
    type_v val;\
}XCAT(name_rb,__pair__);\
typedef struct name_rb{\
    XCAT(name_rb,__pair__);\
    rb_tree* left; \
    rb_tree* right; \
    rb_tree* parent;\
    rb_tree* root; 
    uchar color;    \
    uchar init;\
}name_rb;\
}while(0);
 
#define rb_init(ptr)do{\
    ptr=(typeof(*ptr)*)(malloc(sizeof(typeof(*ptr)))); 
    ptr->data={0};
    ptr->left=NULL; 
    ptr->right=NULL; 
    ptr->parent=NULL; 
    ptr->color=1; 
    ptr->root=ptr;
    //1 means black
    ptr->init=0;\
    ptr->is_root=1;\
}while(0);

#define __r_b_property__(ptr)do{\
    if(ptr->parent->color==1){break;}\
    typeof(*ptr)* _X_=ptr;\
   \
    while(g!=NULL){\
        typeof(*ptr)* p=_X_->parent;\
        typeof(*ptr)* g=p->parent;\
        if(g==NULL){break;}\
        typeof(*ptr)* u=p->left; \
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

#define __bst__insert(ptr,val,val_val)do{\
    if(ptr->init==0){ptr->data=0;ptr->init=1;break;}\
    typeof(*ptr)* curr=ptr; 
    typeof(*ptr)* prev_ptr=NULL;\
    while(curr!=NULL){\
        prev_ptr=curr; \
        if(curr->data>=val){\
            curr=curr->left; \
        }\
        else{\
            curr=curr->right; \
        }\
    }\
    typeof(*ptr)* __temp_new__=(typeof(*ptr)*)(malloc(sizeof(typeof(*ptr))));\
    //Placing a lot of trust in the user LOL; 
    __temp_new__->data={val,val_val};\ 
    __temp_new__->data=val;\
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


//Note this returns an iterator like C++ std::map .find() function
//TODO: Make this change in ptr_hash.h also
#define map_get(ptr,val) ({
    typeof(*ptr)* __result__=ptr->root;
    while(__result__->data!=val){
        if(__result__->data<val){
            __result__=__result__->right;
        }
        else{
            __result__=__result__->left; 
        }
    }
    __result__;\
})

#endif 
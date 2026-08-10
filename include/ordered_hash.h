#ifndef ORD_HASH
#define ORD_HASH
#ifndef CAT_FUNC
#define CAT_FUNC
#define CAT(a,b) a##b
#define XCAT(a,b) CAT(a,b)
#endif 
typedef unsigned char uchar;

#define rb_tree_create(name_rb,data_type) do{\
typedef struct name_rb{\
    typeof(data_type) data;\
    rb_tree* left; \
    rb_tree* right; \
    rb_tree* parent;\ 
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
    ptr->init=0;
}while(0); 
#define __bst__insert(ptr,val)do{\
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
    __temp_new__->data=val;\
    __temp_new__->init=1;  \
    __temp_new__->parent=prev_ptr;\
    if(prev_ptr->data>=val){\
        prev_ptr->left=__temp_new__;\
    }\
    else{\
        prev_ptr->right=__temp_new__;\
    }\
}while(0);


void left_rotate(rb_tree* x,rb_tree* root){
    rb_tree* y=x; 
    x->right=y->left; 
    if(y->left!=NULL){
        y->left->parent=x; 
    }
    y->parent=x->parent; 
    if(x->parent==NULL){
        root=y;
    }
    else if(x==x->parent->left){
        x->parent->left=y; 
    }
    else{
        x->parent->right=y;
    }
    y->left=x; 
    x->parent=y;
}
void right_rotate(rb_tree* x,rb_tree* root){
    rb_tree* y=x; 
    x->left=y->right; 
    if(y->right!=NULL){
        y->right->parent=x; 
    }
    y->parent=x->parent; 
    if(x->parent==NULL){
        root=y;
    }
    else if(x==x->parent->left){
        x->parent->left=y; 
    }
    else{
        x->parent->right=y;
    }
    y->right=x; 
    x->parent=y;
}
 
#endif 
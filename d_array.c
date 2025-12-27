//THis is the implementation of dynamic arrays in C
#include<stdio.h> 
union data_array
{
    int integer;
    float floating_point; 
    double double_point; 
    char character; 
    char* string; 
};

union data_array* create_darray_int(union data_array input[])
{
    size_t size=sizeof(input)/sizeof(input[0]);
    union data_array *ptr=malloc(size*sizeof(union data_array));
    for(int i=0;i<size;i++)
    {
        *ptr=(union data_array)input[i];
        ptr++; 
    }
    ptr=ptr-size; 
    return ptr;
}
union data_array* append_array(union data_array current_array[],union data_array input[])
{
    int new_size=(sizeof(current_array)/sizeof(current_array[0]))+(sizeof(input)/sizeof(input[0]));
    union data_array* current_array_tmp=realloc(current_array,new_size);
    if(current_array_tmp !=NULL)
    {
        current_array=current_array_tmp;
    }
    else
    {
        printf("ERROR"); 
    }
    return current_array;
}
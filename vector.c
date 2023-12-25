typedef struct Vector {
    int sizeof_el;
    int size;
    void * ptr;
    int real_size;

} vector ;
typedef struct User{
    int age;
    char gender[7];//male or female
    char tg_name[15];
    char Name[10];


} User;
void resize(vector* vec,int a)
{
    //printf("ccc");
    void *arr=calloc(a+10,vec->sizeof_el);
    for(int i=0;i<a&&i<vec->size;i++)
    {
        memcpy((arr+i*vec->sizeof_el),(vec->ptr+i*vec->sizeof_el),vec->sizeof_el);
    }
    //printf("ddd");
    free(vec->ptr);
    //printf("eee");
    vec->ptr=arr;
    vec->real_size=a;

}
void insert(vector* vec,int place,void* val)
{   if(vec->size==vec->real_size){
    void *arr=calloc(vec->size+1+10,vec->sizeof_el);
    for(int i=0;i<place;i++)
    {
        memcpy((arr+i*vec->sizeof_el),(vec->ptr+i*vec->sizeof_el),vec->sizeof_el);
    }
    memcpy((arr+place*vec->sizeof_el),(val),vec->sizeof_el);
    for(int i=place;i<vec->size;i++)
    {
        memcpy((arr+(i+1)*vec->sizeof_el),(vec->ptr+i*vec->sizeof_el),vec->sizeof_el);
    }
    free(vec->ptr);
    vec->ptr=arr;
    vec->size++;
    vec->real_size=vec->size+10;
}
    else
    {
        for(int i=vec->size;i>place;i--)
        {
            memcpy((vec->ptr+(i)*vec->sizeof_el),(vec->ptr+(i-1)*vec->sizeof_el),vec->sizeof_el);
        }
        memcpy(vec->ptr+place*vec->sizeof_el,val,vec->sizeof_el);
        vec->size++;

    }
}
void push_back(vector *vec,void* val)
{   if(vec->size==vec->real_size){
    void *arr=calloc(vec->size+1+10,vec->sizeof_el);
    for(int i=0;i<vec->size;i++)
    {
        memcpy((arr+i*vec->sizeof_el),(vec->ptr+i*vec->sizeof_el),vec->sizeof_el);
    }
    memcpy((arr+vec->size*vec->sizeof_el),(val),vec->sizeof_el);
    free(vec->ptr);
    vec->ptr=arr;
    vec->size++;
    vec->real_size=vec->size+10;
    }
    else
    {
        memcpy(vec->ptr+vec->size*vec->sizeof_el,val,vec->sizeof_el);
        vec->size++;
    }


}
void push_first(vector *vec,void * val)
{   if(vec->size==vec->real_size)
    {
    void *arr=calloc(vec->size+1+10,vec->sizeof_el);
    memcpy((arr),(val),vec->sizeof_el);
    for(int i=0;i<vec->size;i++)
    {

        memcpy((arr+(i+1)*vec->sizeof_el),(vec->ptr+i*vec->sizeof_el),vec->sizeof_el);
    }
    free(vec->ptr);
    vec->ptr=arr;
    vec->size++;
    vec->real_size=vec->size+10;
    }
    else
    {
        for(int i=vec->size;i>0;i--)
        {
            memcpy(vec->ptr+i*vec->sizeof_el,vec->ptr+(i-1)*vec->sizeof_el,vec->sizeof_el);
        }
        memcpy(vec->ptr,val,vec->sizeof_el);
        vec->size++;
    }
}
void pop_back(vector* vec)
{   vec->size--;

}
void pop_first(vector* vec)
{   if(vec->size==vec->real_size){
    void* arr=calloc(vec->size-1,vec->sizeof_el);
    for(int i=0;i<vec->size-1;i++)
    {
        //arr[i]=vec->ptr[i+1];
        memcpy((arr+i*vec->sizeof_el),(vec->ptr+(i+1)*vec->sizeof_el),vec->sizeof_el);
    }
    free(vec->ptr);
    vec->ptr=arr;
    vec->size--;
    }
    else
    {   for(int i=0;i<vec->size-1;i++)
        {
        //arr[i]=vec->ptr[i+1];
        memcpy((vec->ptr+i*vec->sizeof_el),(vec->ptr+(i+1)*vec->sizeof_el),vec->sizeof_el);

        }
        vec->size--;
    }

}
void print(vector vec)
{
    for(int i=0;i<vec.size;i++)
    {
        printf("%3d",i);
    }
    printf("\n");
    for(int i=0;i<vec.size;i++)
    {
        printf("%3d",*((int*)(vec.ptr+i*vec.sizeof_el)));
    }
    printf("\n");
}
void erase(vector* vec,int place)
{
    for(int i=place;i<vec->size-1;i++)
    {
        memcpy(vec->ptr+i*vec->sizeof_el,vec->ptr+(i+1)*vec->sizeof_el,vec->sizeof_el);

    }
    vec->size--;
}
void* search(vector *vec,User q)
{
    for(int i=0;i<vec->size;i++)
    {
        if(((User *)vec->ptr+i)->age==q.age&&((User *)vec->ptr+i)->Name[0]==q.Name[0])
            return vec->ptr+i*sizeof(User);
    }
}

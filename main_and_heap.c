#include <stdio.h>
#include <stdlib.h>
#include "vvv.c"
#include <time.h>
#include <string.h>

int comp_int(void* v1,void* v2)
{
    if(*(int*)v1>=*(int*)v2)
        return 1;

    return 0;
}
typedef struct Heap{
    vector vect;

}Heap;
int comp_age(void* v1,void* v2)
{
    if((*(User*)v1).age>=(*(User*)v2).age)
        return 1;

    return 0;
}

int comp_gender(void* v1,void* v2)
{
    if(((*(User*)v1).gender=="male")||(*(User*)v1).gender=="female")
        return 1;

    return 0;
}
int comp_name(void* v1,void* v2)
{
    User us1=*(User*)v1;
    User us2=*(User*)v2;
    for(int i=0;i<10;i++)
    {
        if(us1.tg_name[i]>us2.tg_name[i])
            return 1;
    }
    return 0;
}
int comp_tg_name(void* v1,void* v2)
{
    User us1=*(User*)v1;
    User us2=*(User*)v2;
    for(int i=0;i<15;i++)
    {
        if(us1.tg_name[i]>us2.tg_name[i])
            return 1;
    }
    return 0;
}
void push_up(Heap *heap,void * ptr)
{   if(heap->vect.size==heap->vect.real_size){
   // printf("aaa");
    //printf(" size=%d\n",heap->vect.size);
    //printf("11");
        resize(&(heap->vect),heap->vect.size+10);
        //printf("bbb");
}
    push_back(&(heap->vect),ptr);
    /*printf("after push_back\n");
        print(heap->vect);*/
    int ok=0;
    //int priv=heap->vect.size;
    int priv=heap->vect.size-1;
    int next=(heap->vect.size)/2;
    if(next>0)
        next--;

    while(next>=0&&!ok)
    {



       /* if(comp_int(heap->vect.ptr+next*heap->vect.sizeof_el,heap->vect.ptr+priv*heap->vect.sizeof_el)){
            ok=1;*/
        if(comp_age(heap->vect.ptr+next*heap->vect.sizeof_el,heap->vect.ptr+priv*heap->vect.sizeof_el)){
            ok=1;


        }
        else
        { /*printf("before changement\n");
            print(heap->vect);
            printf("priv= %d\tnext= %d\n",priv,next);*/
             void *pt=malloc(heap->vect.sizeof_el);
            memcpy(pt,heap->vect.ptr+(next)*heap->vect.sizeof_el,heap->vect.sizeof_el);
            memcpy(heap->vect.ptr+(next)*heap->vect.sizeof_el,heap->vect.ptr+priv*heap->vect.sizeof_el,heap->vect.sizeof_el);
            memcpy(heap->vect.ptr+priv*heap->vect.sizeof_el,pt,heap->vect.sizeof_el);
            priv=next;
            next=(priv-1)/2;
            //if(next>0)
            //next--;
            /*printf("after changement\n");
            print(heap->vect);
            printf("\n");*/




        }




    }
}
void push_down(Heap *heap)
{
    int priv=0;
    int next=priv*2+1;
    int ok=0;
    while(next<heap->vect.size&&!ok)
    {
        if(comp_age(heap->vect.ptr+(next+1)*heap->vect.sizeof_el,heap->vect.ptr+(next)*heap->vect.sizeof_el))
            next++;
        if(comp_age(heap->vect.ptr+(priv)*heap->vect.sizeof_el,heap->vect.ptr+(next)*heap->vect.sizeof_el))
            ok=1;
        else
        {
            void *pt=malloc(heap->vect.sizeof_el);
            memcpy(pt,heap->vect.ptr+(priv)*heap->vect.sizeof_el,heap->vect.sizeof_el);
            memcpy(heap->vect.ptr+(priv)*heap->vect.sizeof_el,heap->vect.ptr+(next)*heap->vect.sizeof_el,heap->vect.sizeof_el);
            memcpy(heap->vect.ptr+(next)*heap->vect.sizeof_el,pt,heap->vect.sizeof_el);
            priv=next;
            next=priv*2+1;
        }
    }
}
void print_heap_age( Heap  *heap)
{
    for(int i=0;i<heap->vect.size;i++)
        printf("%4d",i);
    printf("\n");
    for(int i=0;i<heap->vect.size;i++)
     {

     printf("%4d",((User *)(heap->vect.ptr+i*heap->vect.sizeof_el))->age);

     }
     printf("\n");

}
void print_user(User *user)
{

printf("%s\t",user->Name);
printf("%d\n",user->age);
}

void make_heap(Heap *heap,vector *vec)
{   if(heap->vect.size==0)
        heap->vect.ptr=NULL;
    heap->vect.sizeof_el=vec->sizeof_el;
    heap->vect.size=0;
    heap->vect.real_size=0;
    //resize(&heap->vect,vec->size);
   // for(int i=0;i<vec->size;i++)
    //{
       // memcpy(heap->vect.ptr+i*heap->vect.sizeof_el,vec->ptr+i*vec->sizeof_el,vec->sizeof_el);


    //}
    for(int i=0;i<vec->size;i++)
    {
           // printf("ккк\n");
        push_up(heap,vec->ptr+i*vec->sizeof_el);

       // printf("ккк\n");


    }

}
void push_heap(Heap *heap,void* pt)
{
    push_up(heap,pt);
}
void * get_first(Heap *heap)
{
    void *pt=malloc(heap->vect.sizeof_el);
            memcpy(pt,heap->vect.ptr+0*heap->vect.sizeof_el,heap->vect.sizeof_el);
            memcpy(heap->vect.ptr+0*heap->vect.sizeof_el,heap->vect.ptr+(heap->vect.size-1)*heap->vect.sizeof_el,heap->vect.sizeof_el);
            pop_back(&heap->vect);
            push_down(heap);
            return pt;

}
char Names[663][10]={"abbey","abram","acker","adair","adam","adams","adamson","addison","adkins","aiken","akerman","akers","albert","albertson","albinson","alexander","alfredson","alger","alvin","anderson","andrews","ansel","appleton","archer","armistead","arnold","arrington","arthur","arthurson","ashworth","atkins","atkinson","austin","avery","babcock","bagley","bailey","baker","baldwin","bancroft","banister","banks","banner","barber","barker","barlow","bass","bates","baxter","beake","beasley","beck","beckett","beckham","bell","bellamy","bennett","benson","bentley","benton","bernard","berry","beverley","bird","black","blackburn","bond","bonham","bourke","braddock","bradford","bradley","brand","brandon","breckenridge","brewer","brewster","brigham","bristol","brook","brooke","brown","bryson","buckley","bullard","bullock","burnham","burrell","burton","bush","byrd","cantrell","carl","carlisle","carlyle","carman","carpenter","carter","cartwright","carver","caulfield","causer","chadwick","chamberlain","chance","chandler","chapman","chase","cheshire","chlarke","church","clark","clarkson","clay","clayton","clemens","clifford","clifton","cline","clinton","close","coburn","coke","colbert","cole","coleman","colton","comstock","constable","cook","cooke","cookson","cooper","corey","cornell","courtney","cox","crawford","crewe","croft","cropper","cross","crouch","cummins","curtis","dalton","danell","daniel","darby","darrell","darwin","daubney","david","davidson","davies","davis","dawson","day","dean","deering","delaney","denman","dennel","dennell","derby","derrick","devin","devine","dickens","dickenson","dickinson","dickman","donalds","donaldson","downer","draper","dudley","duke","dunn","durand","durant","dustin","dwight","dyer","dyson","eason","easton","eaton","edgar","edison","edwards","edwarson","eliot","eliott","elliott","ellis","ellison","emerson","emmett","endicott","ericson","evanson","evelyn","everett","fairbarn","fairburn","fairchild","fay","fields","fisher","fleming","fletcher","ford","forest","forester","forrest","foss","foster","fox","frank","franklin","freeman","frost","fry","fuller","gardener","gardner","garfield","garland","garner","garnet","garrard","garrett","garry","geary","gibbs","gibson","gilbert","giles","gilliam","gladwin","glover","goddard","goode","goodwin","granger","grant","gray","green","greene","griffin","gully","hackett","hadaway","haden","haggard","haight","hailey","haley","hall","hallman","hamilton","hamm","hancock","hanley","hanson","hardy","harford","hargrave","harlan","harley","harlow","harman","harper","hart","harvey","hathaway","hawk","hawking","hawkins","hayes","haywood","heath","hedley","henderson","henry","henson","herbert","herman","hewitt","hibbert","hicks","hightower","hill","hilton","hobbes","hobbs","hobson","hodges","hodson","holmes","holt","hooker","hooper","hope","hopper","horn","horne","horton","house","howard","howe","hudson","hughes","hull","hume","hunt","hunter","hurst","huxley","huxtable","ingram","irvin","irvine","irving","irwin","ivers","jack","jackson","jacobs","jacobson","james","jameson","jamison","janson","jardine","jarrett","jarvis","jefferson","jeffries","jekyll","jenkins","jepson","jerome","jinks","johns","johnson","jones","jordan","judd","kay","keen","kelsey","kemp","kendall","kendrick","kerry","kersey","key","kidd","king","kingsley","kingston","kinsley","kipling","kirby","knight","lacy","lamar","landon","lane","langley","larson","lawson","leach","leavitt","lee","leigh","leon","levitt","lewin","lincoln","lindsay","linton","little","loman","london","long","lovell","lowell","lowry","lucas","lyndon","lynn","lyon","madison","mann","mark","marley","marlow","marshall","martel","martin","mason","massey","masters","masterson","mathers","matthews","may","mayes","maynard","meadows","mercer","merchant","merrill","merritt","michael","michaels","michaelson","mills","mitchell","moore","morris","myers","nathanson","neville","newell","newman","newport","nichols","nicholson","nielson","niles","nixon","noel","norman","oakley","odell","ogden","oliver","oliverson","olson","osborne","otis","overton","page","parker","parsons","patrick","patton","paulson","payne","pearce","pearson","penny","perkins","perry","peters","peyton","philips","pickering","pierce","pierson","piper","pitts","platt","poole","pope","porcher","porter","potter","pound","powers","prescott","pressley","preston","pryor","purcell","putnam","quigley","quincy","radcliff","raines","ramsey","randall","ray","reed","reeve","rey","reynolds","rhodes","richards","rider","ridley","roach","robbins","robert","roberts","robertson","rogers","rogerson","rollins","roscoe","ross","rowe","rowland","royce","roydon","rush","russell","ryder","sadler","salvage","sampson","samson","samuel","sanders","sandford","sanford","sargent","savage","sawyer","scarlett","seaver","sergeant","shelby","shine","simmons","simon","simons","simonson","simpkin","simpson","sims","sinclair","skinner","slater","smalls","smedley","smith","snelling","snider","sniders","snyder","spalding","sparks","spear","spears","spence","spencer","spooner","spurling","stacy","stafford","stamp","stanton","statham","steed","steele","stephens","stephenson","stern","stone","strange","strickland","stringer","stroud","strudwick","styles","summerfield","summers","sumner","sutton","sydney","tailor","tanner","tash","tasker","tate","taylor","teel","tennyson","terrell","terry","thacker","thatcher","thomas","thompson","thorne","thorpe","timberlake","townsend","tracy","travers","travis","trent","trevis","truman","tucker","tuft","turnbull","turner","tyler","tyrell","tyson","underhill","underwood","upton","vance","vernon","victor","vincent","walker","wallace","walsh","walton","warner","warren","warwick","washington","waters","wayne","weaver","webb","webster","wells","wembley","west","wheeler","whitaker","white","whitney","whittle","wickham","wilcox","wilkie","wilkins","willard","williams","williamson","willis","wilson","winchester","winfield","winship","winslow","winston","winthrop","witherspoon","wolf","wolfe","womack","woodcock","woodham","woodward","wortham","wray","wright","wyatt","wyndham","yates","york","young"};
void Set_rand_vect(vector *vec,long int size)
{
    resize(vec,size);
    for( long int i=0;i<size;i++)
    {   int b=rand();
        (*(User *)(vec->ptr+i*vec->sizeof_el)).age=b%100;
        if(b%2==0)
        strcpy((*(User *)(vec->ptr+i*vec->sizeof_el)).gender,"male");
        else
            strcpy((*(User *)(vec->ptr+i*vec->sizeof_el)).gender,"female");
        strcpy((*(User *)(vec->ptr+i*vec->sizeof_el)).Name,Names[b%663]);
        strcpy((*(User *)(vec->ptr+i*vec->sizeof_el)).tg_name  ,Names[b%663]);


    }
    vec->size=size;
}
 void Set_rand_vect_int(vector *vec,int size)
 {
     resize(vec,size);
     for(int i=0;i<vec->real_size;i++)
     {
         int c=rand()%100;
         push_back(vec,(void *)(&c));
     }
 }
void print_heap_user(const Heap *heap)
{
    for(int i=0;i<heap->vect.size;i++)
        printf("%4d %s %d\n",i,((User*)(heap->vect.ptr+i*heap->vect.sizeof_el))->Name,((User*)(heap->vect.ptr+i*heap->vect.sizeof_el))->age);
}
void print_vect_user(const vector *vect)
{
    for(int i=0;i<vect->size;i++)
        printf("%4d %s %d\n",i,((User*)(vect->ptr+i*vect->sizeof_el))->Name,((User*)(vect->ptr+i*vect->sizeof_el))->age);
}
int main()
{
/*int a=5;
vector vec={sizeof(User)};
resize(&vec,100);
//printf("vec.size=%d\n",vec.size);*/
//printf("vec.realsize=%d\n",vec.real_size);
/*vector vec2={sizeof(User)},vec3={sizeof(User)};
User us1={37,"male","aloha223","Steave"};
void *p1=&us1;
printf("aloha");
double arrins[100];


//for(int i=10000;i<=100000;i+=1000)
//{
//Set_rand_vect(100000,&vec2);
//Set_rand_vect(1000000,&vec3);



/*clock_t begin=clock();

insert(&vec,1,p1);
insert(&vec,2,p1);
insert(&vec,3,p1);
insert(&vec,4,p1);
insert(&vec,5,p1);
insert(&vec,6,p1);
insert(&vec,7,p1);
insert(&vec,8,p1);
insert(&vec,9,p1);
insert(&vec,10,p1);
insert(&vec,11,p1);
insert(&vec,12,p1);
insert(&vec,13,p1);
insert(&vec,13,p1);
insert(&vec,100000,p1);
//insert(&vec3,13378,p1);
//insert(&vec3,13378,p1);
clock_t end=clock();
printf("\t%.20f\n",(double)(end-begin)/(CLOCKS_PER_SEC));
//arrins[(i-10000)/1000]=(double)(end-begin)/CLOCKS_PER_SEC;
//}*/
Heap heap,heap2,heap3;
vector vec={sizeof(User)};
vector vec2={sizeof(User)};
vector vec3={sizeof(User)};
User us1={37,"male","aloha223","Steave"};
void *p=&us1;
FILE *fp=fopen("time_heap_set.txt","w");
if(fp==NULL)
    printf("Error\n");
//for(int i=250000;i<=1000000;i+=10000)
//{
clock_t begin=clock();
int i=350000;
Set_rand_vect(&vec,i);
//Set_rand_vect(&vec2,i);//три структуры и в каждой по пять операций
//Set_rand_vect(&vec3,i);


make_heap(&heap,&vec);
//make_heap(&heap2,&vec2);
//make_heap(&heap3,&vec3);
////
/*vector vect={sizeof(User)};
Set_rand_vect(&vect,100000);
//print(vect);
Heap heap;
make_heap(&heap,&vect);
print_heap_user(&heap);


*/
////

/*int arr[50];
for(int i=0;i<50;i++)
    arr[i]=rand()%(i-100);
clock_t begin=clock();
for(int i=0;i<50;i++)
{   us1.age=arr[i];
    push_heap(&heap,(void*)(&us1));
    //search(&vec,us1);
    //insert(&vec,arr[i],p);
    //erase(&vec,arr[i]);
}
for(int i=0;i<50;i++)
{
    us1.age=arr[i];
    push_heap(&heap2,(void*)(&us1));
    //insert(&vec2,arr[i],p);
    //erase(&vec,arr[i]);
    //search(&vec2,us1);
}
for(int i=0;i<50;i++)
{
    us1.age=arr[i];
    push_heap(&heap3,(void*)(&us1));
    //insert(&vec3,arr[i],p);
    //erase(&vec,arr[i]);
    //search(&vec3,us1);
}*/
clock_t end=clock();
double time=(double)(end-begin)/(CLOCKS_PER_SEC);
//time=time/150;
fprintf(fp,"%d\t%.20f\n",i,time);
//}

//clock_t end = clock();*/
//printf("%f",(double)(end-begin)/CLOCKS_PER_SEC);
/*FILE *fp;
fp=fopen("time.txt","w");
fprintf("")
for(int i=1000;i<=10000;i+=1000)
{


}
User us1={37,"male","aloha223","Steave"};
vector vec={sizeof(User)};
vector vec={sizeof(User)};
vector vec={sizeof(User)};
Set_rand_vect(10000,&vec);
/*void *p=&us1;
push_back(&vec,p);
void*q=find_el(&vec,us1);
printf("%d %s %s",((User *)q)->age,((User *)q)->Name,((User *)q)->tg_name,((User *)q)->gender);*/
/*vector vect={sizeof(User)};
Set_rand_vect(&vect,100000);
//print(vect);
Heap heap;
make_heap(&heap,&vect);
print_heap_user(&heap);
/*User us1={37,"male","aloha223","Steave"};
void *p1=&us1;
push_back(&heap.vect,p1);
push_back(&heap.vect,p1);
print_heap_user(&heap);
//for(int i=0;i<15;i++)
//{
  //  print_user((User*)(heap.vect.ptr+i*heap.vect.sizeof_el));
//}
/*User us1={89,"male","aloha223","Steave"};
void *p=&us1;
push_heap(&heap,p);
push_heap(&heap,p);
push_heap(&heap,p);
push_heap(&heap,p);

print_heap_age(&heap);
/*int c=80;
push_heap(&heap,(void *)(&c));
print(heap.vect);
get_first(&heap);
print(heap.vect);*/


}

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

typedef struct Polynome
{
    int deg;
    float cof;
    struct Polynome *next;
}*Polynome;

void AjouterDebut(Polynome *start_ref, int deg,float cof);
void Sort(Polynome start);
void swap(Polynome a,Polynome b);
void printList(Polynome start);
char * toString(Polynome l);
Polynome Cree();
Polynome add(Polynome a,Polynome b);
Polynome sub(Polynome a,Polynome b);
void changSign(Polynome a);
bool cmp(Polynome a,Polynome b);
Polynome drv(Polynome a);
void trace(int nbarg,...);
double eval(double x,Polynome p);
void racin(int k,double x,Polynome p);



int main()
{
    //Polynome p1,p2,p3;
    //p1 = Cree();
    //p2 = Cree();


    Polynome p1,p2,p3,p4;
    p1 =(Polynome)malloc(sizeof(struct Polynome));
    p2 =(Polynome)malloc(sizeof(struct Polynome));
    p3 =(Polynome)malloc(sizeof(struct Polynome));
    p4 =(Polynome)malloc(sizeof(struct Polynome));
    //p1 =  Cree();       //qui créent le polynome  et remplir le polyome with les valeurs de l'utilisateur.
    //Sort(p1);     //fct de triage de liste chainee
    printf("\n\n");
    p1->deg=2;
    p1->cof =2;
    p1->next=p2;
    p2->deg=3;
    p2->cof=-2;
    p2->next=p3;
    p3->deg=0;
    p3->cof=1;
    p3->next=p4;
    p4->deg=1;
    p4->cof=1;
    p4->next=NULL;
    Sort(p1);
    char * poly = toString(p1); //fct return: le polynome se forme d'un chaine caract
    printf("%s \n",poly);
    printf("\n\n");
//    changSign(p1);
    racin(6,1,p1);
     //printf("2eme Polynome : \n");
    // p2 = Cree();
    // Sort(p2);
//     char * poly2 = toString(p1);
//     printf("%s \n",poly2);
//     printf("\n\n");
    // if(cmp(p1,p2))
    //      printf("Equal");
    // else
    //      printf("Equal");
    //p3 = add(p1,p2);
    // p3 = sub(p1,p2);
    //char * poly3 = toString(p3);
     //printf("%s \n",poly3);
    // p3 = drv(p1);
    // char * poly3 = toString(p3);
    // printf("%s \n",poly3);
     trace(1,p1);
    return 0;
}


void AjouterDebut(Polynome *start_ref, int deg,float cof){
    Polynome ptr1 = (Polynome)malloc(sizeof(struct Polynome));
    ptr1->deg = deg;
    ptr1->cof = cof;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}
void Sort(Polynome start){
    int swapped, i;
    Polynome ptr1;
    Polynome lptr = NULL;

    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->deg > ptr1->next->deg)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
void swap(Polynome a,Polynome b){
    int temp = a->deg;
    a->deg = b->deg;
    b->deg = temp;
    float tmp = a->cof;
    a->cof = b->cof;
    b->cof = tmp;
}
Polynome Cree(){
    Polynome start = NULL;
    int d;
    float c;
    while(1){
        do
        {   printf("degree du monome courant (-1 pour finir) : ");
            scanf("%d",&d);
        }while (d < -1);
        if (d == -1)
            break;
        printf("coeff de x^%d : ",d);
        scanf("%f",&c);
        AjouterDebut(&start, d,c);
    }
    Sort(start);
    return start;
}
Polynome add(Polynome a,Polynome b){
    Polynome start = NULL;

    while (a && b)
    {
        if (a->deg == b->deg)
        {
            AjouterDebut(&start, a->deg,a->cof + b->cof);
            a = a->next;
            b = b->next;
        }
        else if (a->deg > b->deg)
        {
            AjouterDebut(&start,b->deg,b->cof);
            b = b->next;
        }else{
            AjouterDebut(&start,a->deg,a->cof);
            a = a->next;
        }        
    }
    if (a!=NULL)
    {
        while (a)
        {
            AjouterDebut(&start,a->deg,a->cof);
            a = a->next;
        }
        
    }if(b!=NULL)
    {
        while (b)
        {
            AjouterDebut(&start,b->deg,b->cof);
            b = b->next;
        }   
    }
    Sort(start);
    return  start;
}
void changSign(Polynome a){
    while (a)
    {
        a->cof = -(a->cof);
        a = a->next;
    }
}
Polynome sub(Polynome a,Polynome b){
    Polynome start = NULL;

    while (a && b)
    {
        if (a->deg == b->deg)
        {
            if ( (a->cof - b->cof) != 0)
                AjouterDebut(&start, a->deg,a->cof - b->cof);
            a = a->next;
            b = b->next;
        }
        else if (a->deg > b->deg)
        {
            AjouterDebut(&start,b->deg,-(b->cof));
            b = b->next;
        }else{
            AjouterDebut(&start,a->deg,a->cof);
            a = a->next;
        }        
    }
    if (a!=NULL)
    {
        while (a)
        {
            AjouterDebut(&start,a->deg,a->cof);
            a = a->next;
        }
        
    }if(b!=NULL)
    {
        while (b)
        {
            AjouterDebut(&start,b->deg,-(b->cof));
            b = b->next;
        }   
    }
    Sort(start);
    return  start;
}
bool cmp(Polynome a,Polynome b) {
    while (a && b) {
        if (a->deg == b->deg) {
            if (a->cof == b->cof) {
                a = a->next;
                b = b->next;
            }
        }
    }
    if (b==NULL && a == NULL){
        return true;
    }
    else
        return false;
    
    
    
}
Polynome drv(Polynome a){
    Polynome start = NULL;
    if (a->deg == 0)
        a = a->next;
    while (a){
        AjouterDebut(&start, a->deg - 1 ,a->cof * a->deg);
        a = a->next;
    }
    Sort(start);
    return start;
}
char * toString(Polynome l){
    char *buffer = malloc(sizeof(char)*2000);
    char *pnt = buffer;
    Polynome p;
    p = l;
    if(p->deg == 0 ){
        pnt += sprintf(pnt, "%6.2f ",p->cof);
        p = p->next;
    }else{
        pnt += sprintf(pnt, "%6.2f*x**%d ",p->cof,p->deg);
        p = p->next;
    }
    while (p)
    {            
        if (p->cof > 0)
            pnt += sprintf(pnt, "+%6.2f*x**%d ",p->cof,p->deg);
        else
            pnt += sprintf(pnt, "%6.2f*x**%d ",p->cof,p->deg);
        p = p->next;
    }
    return buffer;
}
void trace(int nbarg,...){
   
    char buf[2000];
    char *pf=buf;
    va_list ap;
    va_start(ap,nbarg);
    pf += sprintf(pf,"gnuplot -p -e \"plot [0:10]");
    for (int i = 0; i < nbarg; i++)
    {
        Polynome p = va_arg(ap,Polynome);
        pf += sprintf(pf,"%s",toString(p));
        if (nbarg > i+1 )
            pf += sprintf(pf,",");
    }
    pf += sprintf(pf,";\"");
    va_end(ap);
    



    puts(buf);
    system(buf);
}
double eval(double x,Polynome p){
    double r = 0;
    while (p)
    {
        r += pow(x,p->deg) * p->cof;
        p = p->next;
    }
    return r;
}
void racin(int k,double x,Polynome p){
    Polynome pd;
    pd = drv(p);
    char * p1 = toString(p);
    char * p2 = toString(pd);
    printf("\n\n");
    printf("p(x) = %s\n",p1);
    printf("p'(x) = %s\n",p2);
    for (int i = 0; i <= k; i++)
    {
        printf("K=%d\tx=%.9f\tp(x)=%.9f\n",i,x,eval(x,p));
        x = x - (eval(x,p) / eval(x,pd));
    }
    


}
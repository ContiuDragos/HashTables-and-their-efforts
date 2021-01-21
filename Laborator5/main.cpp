#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"

void printHash(int* usedTable, int spots)
{
    for(int i=0;i<spots;i++)
        printf("%d ",usedTable[i]);
    printf("\n");
}
int hashFunction(int key, int i, int spots)
{
    return ((key%spots)+i+i*i)%spots;
}
void create(int **usedTable, int spots)
{
    int *p=NULL;
    if(usedTable==NULL)
    {
        printf("Can't create!\n");
        exit(-2);
    }
    p=(int*)calloc(spots,sizeof(int));
    if(p==NULL)
    {
        printf("Not enough memory!\n");
        exit(-1);
    }
    *usedTable=p;
}
int addElement(int *usedTable, int key, int spots)
{
    int nr;
    for(int i=0;i<spots;i++)
    {
        nr=hashFunction(key,i,spots);
        if(usedTable[nr]==0 || usedTable[nr]==-1)
        {
            usedTable[nr]=key;
            return key;
        }
    }
    return -1;
}
int searchElement(int *usedTable, int key, int spots,int *efort)
{
    int nr;
    for(int i=0;i<spots;i++)
    {
        nr=hashFunction(key,i,spots);
        (*efort)++;

        if(usedTable[nr]==0)
           return -1;

        if(usedTable[nr]==key)
            return 0;
    }
    return -1;
}
void deleteElement(int *usedTable, int key, int spots)
{
    int i=0;
    int nr=hashFunction(key,i,spots);
    while(usedTable[nr]!=key)
    {
        i++;
        nr=hashFunction(key,i,spots);
    }
    usedTable[nr]=-1;

}
int* insertFactorUmplere(int *usedTable, int spots, float factorDeUmplere)
{
    int *v=(int*)calloc(spots,sizeof(int));
    FillRandomArray(v,spots,1,25000,true,0);

    float n=0;
    for(int i=0;i<spots;i++)
    {
        if(addElement(usedTable,v[i],spots)!=-1)
                  n++;
        if((float)n/spots>=factorDeUmplere)
            break;
    }
    if((float)n/spots<factorDeUmplere)
        printf("\nNot enough elements inserted %.2f\n",factorDeUmplere);

    return v;
}
void calculeazaEfort(int *usedTable, int *v, int spots, float factorDeUmplere)
{
    int efortElement=0,efortMaxim=-1, efortTotal=0;
    int *negasite=(int*)calloc(1501,sizeof(int));
    for(int i=0;i<1500;i++)
    {
        efortElement=0;
        searchElement(usedTable,v[i],spots,&efortElement);
        if(efortElement>efortMaxim)
            efortMaxim=efortElement;
        efortTotal+=efortElement;
    }
    printf("\nPentru factorul de umplere %.2f\nEfortul mediu pentru gasite este %.2f\nEfortul maxim pentru gasite este %d\n",factorDeUmplere,efortTotal/1500.0,efortMaxim);

    FillRandomArray(negasite,1500,25000,30000,false,0);

    efortMaxim=0;
    efortTotal=0;
    for(int i=0;i<1500;i++)
    {
        efortElement=0;
        searchElement(usedTable,negasite[i],spots,&efortElement);
        if(efortElement>efortMaxim)
            efortMaxim=efortElement;
        efortTotal+=efortElement;
    }
    printf("Efortul mediu pentru negasite este %2.f\nEfortul maxim pentru negasite este %d\n",efortTotal/1500.0,efortMaxim);
}
void initHash(int **usedTable, int spots)
{
    for(int i=0;i<spots;i++)
        (*usedTable)[i]=0;
}
void demo()
{
    int *HashTable=NULL;

    int nrLocuri=10007;
    float factorDeUmplere[]={0.8,0.85,0.9,0.95,0.99};
    int *v=NULL;

    create(&HashTable,nrLocuri);

    for(int contor=0;contor<5;contor++)
    {
        initHash(&HashTable,nrLocuri);
        v=insertFactorUmplere(HashTable,nrLocuri,factorDeUmplere[contor]);
        calculeazaEfort(HashTable,v,nrLocuri,factorDeUmplere[contor]);
    }

    /*
    int v[]={78,53,36,74,34,25,36,57,65,34,93,6,91,93,49,85,96,28,63};
    int nrLocuri=20;
    create(&HashTable,nrLocuri);

    printHash(v,nrLocuri-1);
    for(int i=0;i<19;i++)
        addElement(HashTable,v[i],nrLocuri);

    ///afisez hash-ul ca sa vad cum sunt ordonate numerele
    printHash(HashTable,nrLocuri);
    int nimic=0;
    int poz=searchElement(HashTable,63,20,&nimic);
    if(poz==-1)
        printf("Elementul cautat nu se afla in hash\n");
    else
        printf("Elementul cautat se afla pe pozitia %d\n",poz);

    deleteElement(HashTable,65,nrLocuri);
    printHash(HashTable,nrLocuri);
    */
}
int main() {
    demo();
    return 0;
}

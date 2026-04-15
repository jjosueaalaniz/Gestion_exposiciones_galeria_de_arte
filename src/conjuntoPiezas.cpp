#include "../include/conjuntoPiezas.h"

struct rep_conjuntopiezas
{
   int*arr;
   bool vacio=true;
   int maxcantidad;
   int cantini=0;
};
TConjuntoPiezas crearTConjuntoPiezas(int cantMax)
{
    TConjuntoPiezas conjunto=new rep_conjuntopiezas;
    conjunto->maxcantidad=cantMax;
    conjunto->arr=new int[cantMax+1];
    int i=0;
    while (i!=cantMax)
    {
        conjunto->arr[i]=-1;
        i++;
    }
    return conjunto; 
}

bool esVacioTConjuntoPiezas(TConjuntoPiezas c)
{
    return c->vacio; 
}
void insertarTConjuntoPiezas(TConjuntoPiezas &c, int id)
{
    if (id < c->maxcantidad)
    {   
        c->arr[id]=id;
        c->vacio=false;
        c->cantini++;
    }
}

void borrarDeTConjuntoPiezas(TConjuntoPiezas &c, int id)
{
    if (id < c->maxcantidad)
    {
        if (c->arr[id]!=-1)
        {
            c->arr[id]=-1;
            c->cantini--;
        }
    }
}

bool perteneceTConjuntoPiezas(TConjuntoPiezas c, int id)
{ 
    bool retornar=false;
    if (id < c->maxcantidad)
    { 
        retornar=c->arr[id]==id;    
    }    
    return retornar; 
}

int cardinalTConjuntoPiezas(TConjuntoPiezas c)
{ 
    return c->cantini; 
}
int cantMaxTConjuntoPiezas(TConjuntoPiezas c)
{ 
    return c->maxcantidad; 
}

void imprimirTConjuntoPiezas(TConjuntoPiezas c)
{
    if (!c->vacio)
    {
        int i=0;
        while (i!=c->maxcantidad)
        {
            if (c->arr[i]!=-1)
            {
                printf("%d", c->arr[i]);
                printf(" ");
            }
            i++;
        }
    }
    printf("\n");    
}
void liberarTConjuntoPiezas(TConjuntoPiezas &c)
{
    delete []c->arr;
    delete c;
    c=NULL;
}

TConjuntoPiezas unionTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2)
{ 
    TConjuntoPiezas Union=crearTConjuntoPiezas(c1->maxcantidad);
    int i=0;
    while (i<c1->maxcantidad)
    {
        if (c1->arr[i]!=c2->arr[i])
        {
            if (c1->arr[i]!=-1)
            {
                insertarTConjuntoPiezas(Union, c1->arr[i]);
            }
            else
            {
                insertarTConjuntoPiezas(Union, c2->arr[i]);
            }
        }
        else 
        {
            if (c1->arr[i]!=-1)
                insertarTConjuntoPiezas(Union, c1->arr[i]);
        }
        i++;
    }
    return Union; 
}

TConjuntoPiezas interseccionTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2)
{ 
    TConjuntoPiezas interseccion=crearTConjuntoPiezas(c1->maxcantidad);
    int i=0;
    while (i<c1->maxcantidad)
    {
        if (c1->arr[i]==c2->arr[i])
        {
            if (c1->arr[i]!=-1)
            {
                insertarTConjuntoPiezas(interseccion, c1->arr[i]);
            }
        }
        i++;
    }
    return interseccion; 
}

TConjuntoPiezas diferenciaTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2)
{ 
    TConjuntoPiezas diff=crearTConjuntoPiezas(c1->maxcantidad);
    int i=0;
    while (i<c1->maxcantidad)
    {
        if (c1->arr[i]!=-1 && c2->arr[i]==-1)
        {
            insertarTConjuntoPiezas(diff, c1->arr[i]);
        }
        i++;
    }
    return diff; 
}
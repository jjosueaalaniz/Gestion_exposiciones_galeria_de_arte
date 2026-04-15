
#include "../include/hashVisitaDia.h"

struct nodoLista
{
    TVisitaDia y;
    nodoLista* sig;   
};
typedef nodoLista* TLista;
struct rep_hashvisitadia 
{
    TLista* lista;
    int cant;
};

// interna funcion hash
int funcionHash(TFecha fecha, int cantEstimadas){
    return (31 * (int) mesTFecha(fecha) + (int) diaTFecha(fecha)) % cantEstimadas;
}

THashVisitaDia crearTHashVisitaDia(int cantEstimadas)
{
    THashVisitaDia retornar=new rep_hashvisitadia;
    retornar->cant=cantEstimadas;
    retornar->lista=new TLista[cantEstimadas];
    for (int i=0;i<cantEstimadas;i++)
    {
        retornar->lista[i]=NULL;
    }
    return retornar;
}

void agregarVisitaDiaTHashVisitaDia(THashVisitaDia hash, TVisitaDia visitaDia)
{  
    int posicion=0;
    posicion=funcionHash(fechaTVisitaDia(visitaDia),hash->cant);
    if (hash->lista[posicion]==NULL)
    {
        hash->lista[posicion]=new nodoLista;
        hash->lista[posicion]->y=visitaDia;
        hash->lista[posicion]->sig=NULL;
    }
    else
    {
        TLista aux=hash->lista[posicion];
        hash->lista[posicion]=new nodoLista;
        hash->lista[posicion]->y=visitaDia;
        hash->lista[posicion]->sig=aux;
    }
}

void imprimirTHashVisitaDia(THashVisitaDia hash)
{
    for (int i=0;i<hash->cant;i++)
    {
        if (hash->lista[i]!=NULL)
        {
            TLista aux=hash->lista[i];
            printf("Elementos en la posicion %d de la tabla:\n",i);
            while (aux!=NULL)
            {
                imprimirTVisitaDia(aux->y);
                aux=aux->sig;
            }
        }
        else
        {
            printf("No hay elementos guardados la posicion %d de la tabla.\n",i);
        }
    }
}

TVisitaDia obtenerVisitaDiaTHashVisitaDia(THashVisitaDia hash, TFecha fecha)
{
    TVisitaDia retornar=NULL;
    int posicion=0;
    posicion=funcionHash(fecha,hash->cant);
    if (hash->lista[posicion]!=NULL)
    {
        TLista aux=hash->lista[posicion];
        while(aux!=NULL)
        {
            if (compararTFechas(fecha,fechaTVisitaDia(aux->y))==0)
            {    
                retornar=hash->lista[posicion]->y;
            }
            aux=aux->sig;    
        }    
    }
    return retornar;
}

bool perteneceVisitaDiaTHashVisitaDia(THashVisitaDia hash, TFecha fecha)
{
    int posicion=0;
    posicion=funcionHash(fecha,hash->cant);
    bool retornar=false;
    if (hash->lista[posicion]!=NULL)
    {
        TLista aux=hash->lista[posicion];
        while (aux!=NULL)
        {
            if (compararTFechas(fecha,fechaTVisitaDia(aux->y))==0)
            {    
                retornar=true;
            }
            aux=aux->sig;    
        }
    }    
    return retornar;
}

void liberarTHashVisitaDia(THashVisitaDia &hash)
{
    for(int i=0; i<hash->cant;i++)
    {
        while (hash->lista[i]!=NULL)
        {
            TLista aux=hash->lista[i];
            if (aux!=NULL)
            {    
                hash->lista[i]=hash->lista[i]->sig;
                liberarTVisitaDia(aux->y);
                delete aux;
            }            
        }
    }
    delete [] hash->lista;
    delete hash;
    hash=NULL;
}

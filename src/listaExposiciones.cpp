#include "../include/listaExposiciones.h"
typedef struct listexpo* Tlistexpo;
struct listexpo
{
    TExposicion elemento;
    Tlistexpo sig,ant;
};
struct rep_listaexposiciones
{
    Tlistexpo inicio;
    Tlistexpo fin;
    bool vacia=true;
};

TListaExposiciones crearTListaExposicionesVacia()
{
    TListaExposiciones lista= new rep_listaexposiciones;  
    lista->inicio=NULL;
    lista->fin=NULL;
    return lista; 
}

void agregarExposicionTListaExposiciones(TListaExposiciones &listaExposiciones, TExposicion expo)
{
    if (listaExposiciones->vacia)
    {
        listaExposiciones->inicio=new listexpo;
        listaExposiciones->inicio->elemento=expo;
        listaExposiciones->fin=listaExposiciones->inicio;
        listaExposiciones->inicio->sig=NULL;
        listaExposiciones->inicio->ant=NULL;
    }
    else
    {
        Tlistexpo aux = listaExposiciones->inicio;
        while (aux!=NULL && compararTFechas(fechaInicioTExposicion(expo),fechaInicioTExposicion(aux->elemento))!=-1)
        {
            aux=aux->sig;
        }
        
        if (aux==NULL)
        {
            listaExposiciones->fin->sig=new listexpo;
            listaExposiciones->fin->sig->ant=listaExposiciones->fin;
            listaExposiciones->fin=listaExposiciones->fin->sig;
            listaExposiciones->fin->sig=NULL;
            listaExposiciones->fin->elemento=expo;
        }
        else if (aux!=NULL && aux->ant!=NULL)
        {
            Tlistexpo auxnue=new listexpo;
            auxnue->elemento=expo;
            auxnue->sig=aux;
            auxnue->ant=aux->ant;
            aux->ant=auxnue;
            auxnue->ant->sig=auxnue;
        }
        else if (aux->ant==NULL)
        {
            listaExposiciones->inicio->ant=new listexpo;
            listaExposiciones->inicio->ant->elemento=expo;
            listaExposiciones->inicio->ant->sig=listaExposiciones->inicio;
            listaExposiciones->inicio=listaExposiciones->inicio->ant;
            listaExposiciones->inicio->ant=NULL;
        }
    }
    listaExposiciones->vacia=false;
}

bool perteneceExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo)
{ 
    bool retornar=false;    
    if (!listaExposiciones->vacia)
    {    
        Tlistexpo aux=listaExposiciones->inicio;
        while (aux!=NULL && idTExposicion(aux->elemento)!=idExpo)
        {
            aux=aux->sig;
        } 
        if (aux!=NULL)
        {
            retornar=idTExposicion(aux->elemento)==idExpo;
        }
    }    
    return retornar; 
}
TExposicion obtenerExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo)
{ 
    TExposicion retornar;
    Tlistexpo aux=listaExposiciones->inicio;
    while (aux!=NULL && (idTExposicion(aux->elemento)!=idExpo))
    {
        aux=aux->sig;
    } 
    retornar=aux->elemento;
    return retornar; 
}
bool esVaciaTListaExposiciones(TListaExposiciones listaExposiciones)
{ 
    return listaExposiciones->vacia; 
}
void imprimirTListaExposiciones(TListaExposiciones listaExposiciones)
{
    if (!(listaExposiciones->vacia))
    {
        Tlistexpo aux=listaExposiciones->inicio;
        while(aux!=NULL)
        {
            imprimirTExposicion(aux->elemento);
            aux=aux->sig;
        }
    }
}

void liberarTListaExposiciones(TListaExposiciones &listaExposiciones, bool liberarExposiciones)
{
    Tlistexpo rec;        
    Tlistexpo aux=listaExposiciones->inicio;    
    if (liberarExposiciones)
    {
        while(aux!=NULL) 
        {
            liberarTExposicion(aux->elemento);
            rec=aux;
            aux=aux->sig;
            delete rec;
        }
    }
    else
    {
        while(aux!=NULL)
        {
            rec=aux;
            aux=aux->sig;
            delete rec;
        }    
    }
    delete listaExposiciones;
    listaExposiciones=NULL;
}


void agregarExposicionTListaExposiciones2 (TListaExposiciones &listaExposiciones,TExposicion expo)
{
    if (listaExposiciones->vacia)
    {
        listaExposiciones->inicio=new listexpo;
        listaExposiciones->inicio->elemento=expo;
        listaExposiciones->fin=listaExposiciones->inicio;
        listaExposiciones->inicio->sig=NULL;
        listaExposiciones->inicio->ant=NULL;
    }
    else
    {
        listaExposiciones->fin->sig=new listexpo;
        listaExposiciones->fin->sig->ant=listaExposiciones->fin;
        listaExposiciones->fin=listaExposiciones->fin->sig;
        listaExposiciones->fin->elemento=expo;
        listaExposiciones->fin->sig=NULL;
    }
    listaExposiciones->vacia=false;    
}
TListaExposiciones obtenerExposicionesFinalizadas(TListaExposiciones &listaExposiciones, TFecha fecha)
{ 
    TListaExposiciones nueva=new rep_listaexposiciones;
    nueva->inicio=NULL;
    nueva->fin=NULL;
    if (!listaExposiciones->vacia)
    {
        Tlistexpo aux=listaExposiciones->inicio;
        while (aux!=NULL)
        {
            if (compararTFechas(fecha,fechaFinTExposicion(aux->elemento))==1)
            {
                Tlistexpo rec=aux;
                agregarExposicionTListaExposiciones2(nueva,aux->elemento);
                if (aux->ant==NULL && aux->sig==NULL)
                {
                    delete aux;
                    listaExposiciones->inicio=NULL;
                    listaExposiciones->fin=NULL;
                    listaExposiciones->vacia=true;
                    aux=NULL;
                }
                else if (aux->ant==NULL && aux->sig!=NULL)
                {
                    aux->sig->ant=NULL;
                    listaExposiciones->inicio=aux->sig;
                    aux=aux->sig;
                    delete rec;
                }
                else if (aux->ant!=NULL && aux->sig==NULL)
                {
                    aux->ant->sig=NULL;
                    listaExposiciones->fin=aux->ant;
                    delete aux;
                    aux=NULL;
                }
                else if (aux->ant!=NULL && aux->sig!=NULL)
                {
                    aux->ant->sig=aux->sig;
                    aux->sig->ant=aux->ant;
                    aux=aux->sig;
                    delete rec;
                }
            }
            else
            {
                aux=aux->sig;
            }
        }
    }
    return nueva; 
}              
TListaExposiciones obtenerExposicionesActivas(TListaExposiciones &listaExposiciones, TFecha fecha)
{ 
    TListaExposiciones nueva=new rep_listaexposiciones;
    nueva->inicio=NULL;
    nueva->fin=NULL;  
    if (!listaExposiciones->vacia)
    {
        Tlistexpo aux=listaExposiciones->inicio;
        while (aux!=NULL)
        {
            if ((compararTFechas(fecha,fechaFinTExposicion(aux->elemento))==-1) && (compararTFechas(fecha,fechaInicioTExposicion(aux->elemento))==1 || compararTFechas(fecha,fechaInicioTExposicion(aux->elemento))==0))
            {
                Tlistexpo rec=aux;
                agregarExposicionTListaExposiciones2(nueva,aux->elemento);
                if (aux->ant==NULL && aux->sig==NULL)
                {
                    delete aux;
                    listaExposiciones->inicio=NULL;
                    listaExposiciones->fin=NULL;
                    listaExposiciones->vacia=true;
                    aux=NULL;
                }
                else if (aux->ant==NULL && aux->sig!=NULL)
                {
                    aux->sig->ant=NULL;
                    listaExposiciones->inicio=aux->sig;
                    aux=aux->sig;
                    delete rec;
                }
                else if (aux->ant!=NULL && aux->sig==NULL)
                {
                    aux->ant->sig=NULL;
                    listaExposiciones->fin=aux->ant;
                    delete aux;
                    aux=NULL;
                }
                else if (aux->ant!=NULL && aux->sig!=NULL)
                {
                    aux->ant->sig=aux->sig;
                    aux->sig->ant=aux->ant;
                    aux=aux->sig;
                    delete rec;
                }
            }
            else
            {
                aux=aux->sig;
            }
        }
    }
    return nueva; 
}
bool esCompatibleTListaExposiciones(TListaExposiciones listaExposiciones, TExposicion expo)
{ 
    bool sentinel=true;
    bool retornar=true;
    if (!listaExposiciones->vacia)
    { 
        Tlistexpo aux=listaExposiciones->inicio;
        while (aux!=NULL && sentinel)
        {
            if (sonExposicionesCompatibles(aux->elemento,expo))
            {
                aux=aux->sig;
            }
            else
            {
                sentinel=false;
                retornar=false;
            }
        }
    }
    else
    {
        retornar=false;
    }    
    return retornar; 
}
//retorna true si y solo si la fecha de inicio de expo1 es menor que la de expo2
bool VAPRIMERO(TExposicion expo1, TExposicion expo2)
{
    bool retornar=false;
    if (compararTFechas(fechaInicioTExposicion(expo1), fechaInicioTExposicion(expo2))==-1)
    {
        retornar=true;
    }
    return retornar;
}
TListaExposiciones unirListaExposiciones(TListaExposiciones listaExpo1, TListaExposiciones listaExpo2)
{ 
    
    TListaExposiciones unir= new rep_listaexposiciones;  
    unir->inicio=NULL;
    unir->fin=NULL;    
    if (!listaExpo1->vacia && !listaExpo2->vacia)
    {
        Tlistexpo aux1,aux2;
        aux1=listaExpo1->inicio;
        aux2=listaExpo2->inicio;
        while(aux1!=NULL && aux2!=NULL)
        {
            if(VAPRIMERO(aux1->elemento,aux2->elemento))
            {
                agregarExposicionTListaExposiciones2(unir,aux1->elemento);
                aux1=aux1->sig;
            }
            else
            {
                agregarExposicionTListaExposiciones2(unir,aux2->elemento);
                aux2=aux2->sig;
            }

        }
        if (aux1!=NULL)
        {
            while(aux1!=NULL)
            {
                agregarExposicionTListaExposiciones2(unir,aux1->elemento);
                aux1=aux1->sig;
            }
        }
        else if (aux2!=NULL)
        {
            while(aux2!=NULL)
            {
                agregarExposicionTListaExposiciones2(unir,aux2->elemento);
                aux2=aux2->sig;
            }
        }
    }
    else if (listaExpo1->vacia && !listaExpo2->vacia)
    {
        Tlistexpo aux=listaExpo2->inicio;
        while (aux!=NULL)
        {
            agregarExposicionTListaExposiciones2(unir,aux->elemento);
            aux=aux->sig;
        }
    }
    else if (!listaExpo1->vacia && listaExpo2->vacia)
    {
        Tlistexpo aux=listaExpo1->inicio;
        while (aux!=NULL)
        {
            agregarExposicionTListaExposiciones2(unir,aux->elemento);
            aux=aux->sig;
        }
    }
    return unir; 
}
// Función para obtener la cantidad de exposiciones en la lista de exposiciones.
// La funcion es O(n) peor caso, siendo n la cantidad de exposiciones en la lista.
int cantidadExposicionesTListaExposiciones(TListaExposiciones listaExpo)
{
    int i=0;
    if (!listaExpo->vacia)
    {
        Tlistexpo rec=listaExpo->inicio;
        while (rec!=NULL)
        {
            i++;
            rec=rec->sig;
        }
    }    
    return i;
}

// Función para obtener una exposición de la lista dado su índice.
// La funcion es O(n) peor caso, siendo n la cantidad de exposiciones en la lista de exposiciones.
// La primer exposición de la lista tiene índice 1.
// PRE: cantidadExposicionesListaExposiciones(grupo) >= n
// PRE: n > 0 
TExposicion obtenerNesimaExposicionTListaExposiciones(TListaExposiciones listaExpo, int n)
{
    Tlistexpo recor=listaExpo->inicio;
    int i=1;
    while (recor!=NULL && i!=n)
    {
        recor=recor->sig;
        i=i+1;
    }
    return recor->elemento;
}
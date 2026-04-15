#include "../include/exposicion.h"
struct rep_exposicion
{
    int id;
    TFecha inicio,fin;
    TConjuntoPiezas piezas;
};

TExposicion crearTExposicion(int idExp, TFecha ini, TFecha fin, int cantMax)
{ 
    TExposicion retornar = new rep_exposicion;
    retornar->inicio = ini;
    retornar->fin = fin;
    retornar->id = idExp;
    retornar->piezas=crearTConjuntoPiezas(cantMax);
    return retornar; 
}

void agregarATExposicion(TExposicion &exp, TPieza p)
{
    int i=idTPieza(p);
    insertarTConjuntoPiezas(exp->piezas,i);
}

bool perteneceATExposicion(TExposicion exp, TPieza p)
{ return perteneceTConjuntoPiezas(exp->piezas,idTPieza(p)); }

int idTExposicion(TExposicion exp)
{ return exp->id; }

void imprimirTExposicion(TExposicion exp)
{
    printf("Exposicion #%d ",exp->id);
    printf("del ");
    imprimirTFecha(exp->inicio);
    printf(" al ");
    imprimirTFecha(exp->fin);
    printf("\n");
    printf("Piezas: ");
    imprimirTConjuntoPiezas(exp->piezas);
}

TFecha fechaInicioTExposicion(TExposicion exp)
{ return exp->inicio; }

TFecha fechaFinTExposicion(TExposicion exp)
{ return exp->fin; }

// Devuelve true si las exposiciones expo1 y expo2 son compatibles. Una exposición es 
// compatible con otra si no comparten piezas durante un mismo período de tiempo. O
// de otra manera, no son compatibles si coinciden en el tiempo y además una misma
// pieza es parte de ambas exposiciones.
// La función es O(...)
bool sonExposicionesCompatibles(TExposicion exp1, TExposicion exp2)
{ 
    bool retornar=true;
    TConjuntoPiezas interseccion=interseccionTConjuntoPiezas(exp1->piezas,exp2->piezas);
    bool vacio=esVacioTConjuntoPiezas(interseccion);
    if (!vacio)
    {
        int inicios = compararTFechas(exp1->inicio,exp2->inicio);
        if (inicios==0)
        {
            retornar = false;
        }
        if (inicios==-1)
        {
            int iniciofinal = compararTFechas(exp1->fin,exp2->inicio);
            if (iniciofinal==1 /*|| iniciofinal==0*/)
            {
                retornar=false;
            }
        }
        if (inicios==1)
        {
            int finalfinal = compararTFechas(exp1->inicio,exp2->fin);
            if (finalfinal==-1 /*|| finalfinal==0*/)
            {
                retornar=false;
            }
        }
    }
    liberarTConjuntoPiezas(interseccion);
    return retornar;
}
// Función para comparar dos fechas representadas por elementos de tipo TFecha
// Si fecha1 es mayor que fecha2 retorna 1 
// Si fecha1 es menor que fecha2 retorna -1
// Si fecha1 es igual que fecha2 retorna 0
void liberarTExposicion(TExposicion &exp)
{
    liberarTFecha(exp->inicio);
    liberarTFecha(exp->fin);
    liberarTConjuntoPiezas(exp->piezas);
    delete exp;
    exp=NULL;
}

TConjuntoPiezas obtenerPiezasTExposicion(TExposicion expo)
{
    return expo->piezas;
}
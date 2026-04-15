#include "../include/galeria.h"

struct rep_galeria
{
    TColeccionPiezas obras=NULL;
    TConjuntoPiezas convertido=NULL;
    TFecha hoy=NULL;
    TListaExposiciones finalizadas=NULL;
    TListaExposiciones actuales=NULL;
    TListaExposiciones futuras=NULL;
    THashVisitaDia hash=NULL;
    TVisitaDia visita;
};

TGaleria crearTGaleria(TFecha fecha)
{ 
    TGaleria galeria=new rep_galeria;
    galeria->convertido=crearTConjuntoPiezas(MAX_PIEZAS);
    galeria->hoy=fecha;
    TFecha nueva = copiarTFecha(galeria->hoy);   
    galeria->actuales=crearTListaExposicionesVacia();
    galeria->finalizadas=crearTListaExposicionesVacia();
    galeria->futuras=crearTListaExposicionesVacia();
    galeria->hash=crearTHashVisitaDia(CANT_ESTIMADA_VISITA_DIA_PASADAS);
    galeria->visita=crearTVisitaDia(nueva,MAX_GRUPOS_VISITA_DIA);
    return galeria; 
}
void agregarPiezaTGaleria(TGaleria galeria, TPieza pieza)
{
    insertarPiezaColeccionPiezas(galeria->obras,pieza);
    insertarTConjuntoPiezas(galeria->convertido,idTPieza(pieza));
}
void agregarExposicionTGaleria(TGaleria galeria, TExposicion expo) //01/12/2023 01/01/2024 10 1    //hoy 01/01/2024
{
    if (true/*esCompatibleExposicionTGaleria(galeria,expo)*/)
    {
        TFecha inicio=fechaInicioTExposicion(expo);
        TFecha fin=fechaFinTExposicion(expo);
        if (compararTFechas(galeria->hoy,inicio)>=0 && compararTFechas(galeria->hoy,fin)<=0)
        {
            agregarExposicionTListaExposiciones(galeria->actuales,expo);
        }
        else if (compararTFechas(galeria->hoy,inicio)==-1)
        {
            agregarExposicionTListaExposiciones(galeria->futuras,expo);
        }
        else if (compararTFechas(galeria->hoy,fin)==1)
        {
            agregarExposicionTListaExposiciones(galeria->finalizadas,expo);
        }
    }
}

void agregarPiezaAExposicionTGaleria(TGaleria galeria, int idPieza, int idExpo)
{
    TExposicion expo;
    TPieza pieza =obtenerPiezaColeccionPiezas(galeria->obras, idPieza);
    if (perteneceExposicionTListaExposiciones(galeria->finalizadas,idExpo))
    {
        expo=obtenerExposicionTListaExposiciones(galeria->finalizadas,idExpo);
        agregarATExposicion(expo,pieza);
    }
    else if (perteneceExposicionTListaExposiciones(galeria->actuales,idExpo))
    {
        expo=obtenerExposicionTListaExposiciones(galeria->actuales,idExpo);
        agregarATExposicion(expo,pieza);        
    }
    else if (perteneceExposicionTListaExposiciones(galeria->futuras,idExpo))
    {
        expo=obtenerExposicionTListaExposiciones(galeria->futuras,idExpo);
        agregarATExposicion(expo,pieza);        
    }
}

void avanzarAFechaTGaleria(TGaleria galeria, TFecha fecha)
{
    if (galeria->visita!=NULL)
    {    
        agregarVisitaDiaTHashVisitaDia(galeria->hash,galeria->visita);
        galeria->visita=NULL;
    }    
    TListaExposiciones actuales,finalizadas,finalizadas2,actuales2;
    finalizadas=obtenerExposicionesFinalizadas(galeria->actuales,fecha);
    finalizadas2=galeria->finalizadas;
    galeria->finalizadas=NULL;
    galeria->finalizadas=unirListaExposiciones(finalizadas,finalizadas2);
    actuales=galeria->actuales;
    actuales2=obtenerExposicionesActivas(galeria->futuras,fecha);
    galeria->actuales=unirListaExposiciones(actuales,actuales2);
    liberarTListaExposiciones(actuales,false);
    liberarTListaExposiciones(actuales2,false);
    liberarTListaExposiciones(finalizadas,false);
    liberarTListaExposiciones(finalizadas2,false);
    liberarTFecha(galeria->hoy);
    galeria->hoy=fecha;
}

void imprimirExposicionesFinalizadasTGaleria(TGaleria galeria)
{
    imprimirTListaExposiciones(galeria->finalizadas);
}

void imprimirExposicionesActivasTGaleria(TGaleria galeria)
{
    imprimirTListaExposiciones(galeria->actuales);
}

void imprimirExposicionesFuturasTGaleria(TGaleria galeria)
{
    imprimirTListaExposiciones(galeria->futuras);
}

bool esCompatibleExposicionTGaleria(TGaleria galeria, TExposicion expo)
{ 
    bool retornar=true;
    if (galeria!=NULL)
    {
        if (galeria->actuales!=NULL)
        {
            retornar=esCompatibleTListaExposiciones(galeria->actuales,expo);   
        }
        if (galeria->finalizadas!=NULL && retornar)
        {
            retornar=esCompatibleTListaExposiciones(galeria->finalizadas,expo);
        }
        if (galeria->futuras!=NULL && retornar)
        {
            retornar= esCompatibleTListaExposiciones(galeria->futuras,expo);
        }
    }
    return retornar; 
}
void liberarTGaleria(TGaleria &galeria)
{
    if (galeria->actuales!=NULL)
    {    
        liberarTListaExposiciones(galeria->actuales,true);
    }    
    if (galeria->futuras!=NULL)    
    {    
        liberarTListaExposiciones(galeria->futuras,true);
    }    
    if (galeria->finalizadas!=NULL )    
    {    
        liberarTListaExposiciones(galeria->finalizadas,true);
    }
    if (galeria->hash!=NULL)
    {
        liberarTHashVisitaDia(galeria->hash);
    }
    if (galeria->visita!=NULL)
    {
        liberarTVisitaDia(galeria->visita);
    }
    if (galeria->convertido!=NULL)
    {
        liberarTConjuntoPiezas(galeria->convertido);
    }
    liberarTFecha(galeria->hoy);
    liberarColeccionPiezas(galeria->obras);
    delete galeria;
    galeria=NULL;
}

// Funciones tarea 4

TConjuntoPiezas piezasEnExposicionTGaleria(TGaleria galeria)
{
    TConjuntoPiezas retornar=crearTConjuntoPiezas(MAX_PIEZAS);
    TConjuntoPiezas borrar;
    TExposicion expo;
    int i=cantidadExposicionesTListaExposiciones(galeria->actuales);
    for (int n=1;n<=i;n++)
    {
        borrar=retornar;
        expo=obtenerNesimaExposicionTListaExposiciones(galeria->actuales,n);
        retornar=unionTConjuntoPiezas(retornar,obtenerPiezasTExposicion(expo));
        liberarTConjuntoPiezas(borrar);
    }   
    return retornar;
}

float indiceFelicidadVisitanteTGaleria(TGaleria galeria, TVisitante visitante)
{
    float retornar=1;
    TConjuntoPiezas favis=obtenerPiezasFavoritasTVisitante(visitante);
    TConjuntoPiezas inexp=piezasEnExposicionTGaleria(galeria);
    float cpf=cardinalTConjuntoPiezas(favis);
    if (cpf!=0)
    {
        TConjuntoPiezas interseccion=interseccionTConjuntoPiezas(favis,inexp);
        float cpfv=cardinalTConjuntoPiezas(interseccion);
        retornar=cpfv/cpf;
        liberarTConjuntoPiezas(interseccion);
    }
    liberarTConjuntoPiezas(inexp);
    return retornar;
}

void llegaGrupoTGaleria(TGaleria galeria, TGrupoABB grupoABB)
{
    if (galeria->visita!=NULL)
    {
        encolarGrupoTVisitaDia(galeria->visita,grupoABB);
    }    
    else
    {
        TFecha nueva=copiarTFecha(galeria->hoy);
        galeria->visita=crearTVisitaDia(nueva,MAX_GRUPOS_VISITA_DIA);
        encolarGrupoTVisitaDia(galeria->visita,grupoABB);
    }
}

TConjuntoPiezas piezasEnReservaTGaleria(TGaleria galeria)
{
    TConjuntoPiezas enExpo=piezasEnExposicionTGaleria(galeria);
    TConjuntoPiezas retornar=diferenciaTConjuntoPiezas(galeria->convertido,enExpo);
    liberarTConjuntoPiezas(enExpo);
    return retornar;
}

TVisitaDia obtenerVisitaDiaTGaleria(TGaleria galeria, TFecha fecha)
{
    TVisitaDia retornar=NULL;
    if (compararTFechas(fecha,galeria->hoy)==0)
    {
        if (galeria->visita==NULL)
        {
            TFecha nueva=copiarTFecha(galeria->hoy);
            galeria->visita=crearTVisitaDia(nueva,MAX_GRUPOS_VISITA_DIA);
        }
        retornar=galeria->visita;
    }
    else if (compararTFechas(fecha,galeria->hoy)==-1)
    {
        retornar=obtenerVisitaDiaTHashVisitaDia(galeria->hash,fecha);
    }
    return retornar;
}

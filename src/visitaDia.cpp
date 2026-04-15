#include "../include/visitaDia.h"


struct celdasvisitadia
{
  TGrupoABB elemento;
  float prioridad;
};
typedef celdasvisitadia* TCeldas;
struct rep_visitadia
{
    bool invertido;
    TCeldas grupos;
    bool* esta;
    int* ubicacion;
    TFecha dia;
    int tope;
    int cantmax;
};

TVisitaDia crearTVisitaDia(TFecha fecha, int N)
{
  TVisitaDia visita=new rep_visitadia;
  visita->dia=fecha;
  visita->tope=0;
  visita->cantmax=N;
  visita->invertido=false;
  int i=0;
  visita->grupos=new celdasvisitadia[N];
  visita->esta=new bool[N];
  visita->ubicacion=new int[N];
  while (i<=N-1)
  {  
    visita->grupos[i].elemento=NULL;
    visita->grupos[i].prioridad=0.0;
    visita->esta[i]=false;
    visita->ubicacion[i]=0;
    i++;
  }
  return visita;
}

void filtradoAscendente(int pos, TVisitaDia &visita,int id)
{  
  celdasvisitadia aux; 
  if (pos>1 && (visita->grupos[pos].prioridad < visita->grupos[pos/2].prioridad))
  {
    aux=visita->grupos[pos];
    visita->grupos[pos]=visita->grupos[pos/2];
    visita->grupos[pos/2]=aux;
    visita->ubicacion[id]=pos/2;
    filtradoAscendente(pos/2,visita,id);
  }
}

void insertarEnInvertida(int pos, TVisitaDia &visita, int id)
{
  celdasvisitadia aux;
  if (pos>1 &&visita->grupos[pos].prioridad>visita->grupos[pos/2].prioridad)
  {
    aux=visita->grupos[pos];
    visita->grupos[pos]=visita->grupos[pos/2];
    visita->grupos[pos/2]=aux;
    visita->ubicacion[id]=pos/2;
    insertarEnInvertida(pos/2,visita,id);
  }
}
void encolarGrupoTVisitaDia(TVisitaDia &visita, TGrupoABB grupo)
{
    if (visita->tope==0)
    {
      visita->esta[idGrupo(grupo)]=true;
      visita->tope=1;
      visita->grupos[1].elemento=grupo;
      visita->grupos[1].prioridad=edadPromedioTGrupoABB(grupo);
      visita->ubicacion[idGrupo(grupo)]=1;
    }
    else 
    {
      visita->esta[idGrupo(grupo)]=true;
      visita->tope=visita->tope+1;
      visita->grupos[visita->tope].elemento=grupo;
      visita->grupos[visita->tope].prioridad=edadPromedioTGrupoABB(grupo);
      visita->ubicacion[idGrupo(grupo)]=visita->tope;
      if (!visita->invertido)
      {  
        filtradoAscendente(visita->tope,visita,idGrupo(grupo));
      }  
      else
      {
        insertarEnInvertida(visita->tope,visita, idGrupo(grupo));
      }
    }  
}

int cantidadGruposTVisitaDia(TVisitaDia visitaDia){
  return visitaDia->tope;
}

int logbase2(int i)
{
  int retornar=1;
  while (i>1)
  {
    i=i/2;
    retornar=retornar+1;
  }
  return retornar;
}

void impresora(int indice, int nivel, int nivelActual, TVisitaDia visitaDia)
{
  if (indice<=visitaDia->tope)
  {
    nivelActual=logbase2(indice);
    if (nivel!=nivelActual || nivel==1)
    {
     printf("\n");
     nivel=nivelActual;
     printf("Nivel %d\n",nivel);
    }
    if (indice<=visitaDia->tope)
    {
      printf("%d) Grupo %d con edad promedio %.2f\n",indice,idGrupo(visitaDia->grupos[indice].elemento),visitaDia->grupos[indice].prioridad);
      imprimirTGrupoABB(visitaDia->grupos[indice].elemento);
    }
    indice=indice+1;
    impresora(indice,nivel,nivelActual,visitaDia);
  }
}

void imprimirTVisitaDia(TVisitaDia visitaDia)
{
  printf("Visita para dia: ");
  imprimirTFecha(visitaDia->dia);
  int indice=1;
  int nivel=1;
  int nivelActual=1;
  printf("\n");
  impresora(indice,nivel,nivelActual,visitaDia);
}

void filtradoDescendente(int pos, TVisitaDia &visita, celdasvisitadia espacio)
{
  if (logbase2(pos)!=logbase2(visita->tope))
  {
    if (visita->grupos[pos*2].prioridad<visita->grupos[(pos*2)+1].prioridad)
    {
      visita->grupos[pos]=visita->grupos[pos*2];
      visita->ubicacion[idGrupo(visita->grupos[pos].elemento)]=pos;
      filtradoDescendente(pos*2,visita,espacio);
    }
    if (visita->grupos[pos*2].prioridad>visita->grupos[(pos*2)+1].prioridad)
    {
      visita->grupos[pos]=visita->grupos[(pos*2)+1];
      visita->ubicacion[idGrupo(visita->grupos[pos].elemento)]=pos;
      filtradoDescendente((pos*2)+1,visita,espacio);      
    }
  }
  else
  {
    visita->grupos[pos]=espacio;
  }
}

TGrupoABB desencolarGrupoTVisitaDia(TVisitaDia &visitaDia)
{
  TGrupoABB retornar=visitaDia->grupos[1].elemento;
  visitaDia->esta[idGrupo(retornar)]=false;
  celdasvisitadia aux=visitaDia->grupos[visitaDia->tope];
  visitaDia->ubicacion[1]=0;
  visitaDia->tope=visitaDia->tope-1;
  int i=1;
  filtradoDescendente(i,visitaDia,aux);
  return retornar;  
}

void liberarTVisitaDia(TVisitaDia &visitaDia)
{
  int i=1;
  while(i<=visitaDia->tope)
  {
    liberarTGrupoABB(visitaDia->grupos[i].elemento);
    i++;
  }
  delete [] visitaDia->grupos;
  delete[] visitaDia->esta;
  delete[] visitaDia->ubicacion;
  liberarTFecha(visitaDia->dia);
  delete visitaDia;
  visitaDia=NULL;
}

TGrupoABB menosPrioritarioTVisitaDia(TVisitaDia visita){
	return visita->grupos[visita->tope].elemento;
}

void invertirPrioridadTVisitaDia(TVisitaDia &visita) 
{
  TVisitaDia aux = crearTVisitaDia(visita->dia, visita->cantmax);
  aux->invertido = !visita->invertido;
  
  while(visita->tope > 0){

    encolarGrupoTVisitaDia(aux, menosPrioritarioTVisitaDia(visita));
    visita->tope = visita->tope-1;
  }

  delete [] visita->grupos;
  delete[] visita->esta;
  delete[] visita->ubicacion;
  delete visita;
  
  visita = aux;
} 

bool estaEnTVisitaDia(TVisitaDia visita, int id) 
{
  return visita->esta[id];
} 

float prioridadTVisitaDia(TVisitaDia visita, int id)
{
  return visita->grupos[visita->ubicacion[id]].prioridad;
}

TGrupoABB masPrioritarioTVisitaDia(TVisitaDia visita){
	return visita->grupos[1].elemento;
}


int maxGruposTVisitaDia(TVisitaDia visita)
{
  return visita->cantmax;
}

TFecha fechaTVisitaDia(TVisitaDia visitaDia)
{
  return visitaDia->dia;
}



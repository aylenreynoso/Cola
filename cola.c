#include "cola.h"
#include <stdio.h>
#include <stdlib.h>

/* *********************************************
 *                    NODO
 * *********************************************/
struct nodo;
typedef struct nodo nodo_t;

struct nodo{
  void* dato; //puntero al dato almacenado
  nodo_t* next; //puntero al nodo siguiente
};

nodo_t* crear_nodo(void* valor){

  nodo_t* nodo = malloc(sizeof(nodo_t));
  if (!nodo){
    return NULL;
  }
  nodo->dato = valor;
  nodo->next = NULL;
  return nodo;
}

//--------------------------------------------------------

struct cola {
  nodo_t* first;
  nodo_t* last;
};

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(void){

  cola_t* cola = malloc(sizeof(cola_t));
  if (!cola){
    return NULL;
  }
   cola->first = NULL;
   cola->last = NULL;
  return cola;
}


void cola_destruir(cola_t *cola, void destruir_dato(void*)){

  while (!cola_esta_vacia(cola)){
    void* desencolado = cola_desencolar(cola);
    if(destruir_dato != NULL){
      destruir_dato(desencolado);
    }
  }
  free(cola);
}


bool cola_esta_vacia(const cola_t *cola){

  return (!(cola->first) );
}


bool cola_encolar(cola_t *cola, void* valor){

  nodo_t* nuevo_nodo = crear_nodo(valor);
  if (!(nuevo_nodo)){
    return false;
  }

  if (cola_esta_vacia(cola)){
    cola->first = nuevo_nodo;
  } else {					
    cola->last->next = nuevo_nodo;
  }
  cola->last = nuevo_nodo;

  return true;
}


void* cola_ver_primero(const cola_t *cola){
   if (cola_esta_vacia(cola)){
     return NULL;
   }
  return (cola->first->dato);
}


void* cola_desencolar(cola_t *cola){

  if (cola_esta_vacia(cola)){
    return NULL;
  }
  void* desencolado = cola_ver_primero(cola);

  nodo_t* nuevo_primero;

  if (cola->first != cola->last){
    nuevo_primero = cola->first->next;

  } else{ 
    nuevo_primero = NULL;
    cola->last = NULL;
  }
  free(cola->first);
  cola->first = nuevo_primero;
  
  return desencolado;
}

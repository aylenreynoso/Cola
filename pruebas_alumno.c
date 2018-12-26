#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#define VOLUMEN 1000000

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

/* Pruebas para una cola vacía. */

void pruebas_cola_vacia_alumno() {

    printf("INICIO DE PRUEBAS CON COLA VACÍA\n");

    cola_t* cola = cola_crear();
    char b;

    /* Pruebo creación y estado*/
    print_test("crear cola vacía", cola != NULL);
    print_test("estado vacia (true)", cola_esta_vacia(cola) == true);

    /* Pruebo que desencolar y mostrar primer elemento de una cola vacía devuelven NULL */
    print_test("desencolar cola vacía", cola_desencolar(cola) == NULL);
    print_test("mostrar primero cola vacía", cola_ver_primero(cola) == NULL);

    /* Pruebo que puedo encolar un elemento en una cola vacía */
    print_test("encolar en cola vacía es true", cola_encolar(cola, &b) == true);
    print_test("desencolar un elemento", cola_desencolar(cola) == &b);
    print_test("mostrar primero ", cola_ver_primero(cola) == NULL);


    /* Destruyo la cola (vacía)*/
    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
}

void pruebas_cola_null_alumno() {

    printf("INICIO DE PRUEBAS CON NULL\n");

    cola_t* cola = cola_crear();
    int a;

    /* Pruebo que encolar NULL es una operación válida*/
    print_test("encolar NULL es válido", cola_encolar(cola, NULL) == true);

    /* Pruebo estado y mostrar primer elemento*/
    print_test("estado cola no vacia (false)", cola_esta_vacia(cola) == false);
    print_test("mostrar primero (NULL))", cola_ver_primero(cola) == NULL);

    cola_encolar(cola, &a); //ahora Cola tiene a Null y a *a

    /* Pruebo que desencolar NULL*/
    print_test("desencolar NULL", cola_desencolar(cola) == NULL);
    print_test("mostrar nuevo primero", cola_ver_primero(cola) == &a);

    /* Destruyo la cola (no vacía)*/
    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
}

void pruebas_cola_un_elemento_alumno() {

    printf("INICIO DE PRUEBAS CON UN ELEMENTO \n");

    cola_t* cola = cola_crear();
    long a;

    /* Pruebo que encolar un elemento*/
    print_test("encolar", cola_encolar(cola, &a) == true);

    /* Pruebo estado y mostrar primer elemento*/
    print_test("estado cola no vacia (false)", cola_esta_vacia(cola) == false);
    print_test("mostrar primero ", cola_ver_primero(cola) == &a);

    /* Pruebo que desencolar */
    print_test("desencolar único elemento", cola_desencolar(cola) == &a);

    /* Pruebo estado y mostrar primer elemento*/

    print_test("estado cola no vacia (true)", cola_esta_vacia(cola) == true);
    print_test("mostrar nuevo primero (NULL)", cola_ver_primero(cola) == NULL);

    /* Destruyo la cola (no vacía)*/
    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
}

void pruebas_cola_destruir_free() {

    printf("INICIO DE PRUEBAS DESTRUIR COLA PASANDO FREE \n");

    cola_t* cola = cola_crear();

    void* a = malloc(sizeof(int)*10);
    void* b = malloc(sizeof(long)*5);
    void* c = malloc(sizeof(char)*20);
    void* d = malloc(sizeof(int)*200);
    void* e = malloc(sizeof(int)*50);

    cola_encolar(cola, &a);
    cola_encolar(cola, &b);
    cola_encolar(cola, &c);
    cola_encolar(cola, &d);
    cola_encolar(cola, &e);

    /* Destruyo la cola (no vacía)*/

    cola_destruir(cola, free);
    print_test("la cola fue destruida", true);
}

/* Pruebas de guardar y obtener algunos elementos*/

void pruebas_cola_algunos_elementos_alumno() {

    printf("INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS \n");

    cola_t* cola = cola_crear();
    long a;
    int b;
    char c;
    size_t d;

    /* Pruebo que encolar elementos*/

    print_test("encolar", cola_encolar(cola, &a) == true);
    print_test("encolar", cola_encolar(cola, &b) == true);
    print_test("encolar", cola_encolar(cola, &c) == true);
    print_test("encolar", cola_encolar(cola, &d) == true);

    /* Pruebo estado y mostrar primer elemento*/

    print_test("estado cola no vacia (false)", cola_esta_vacia(cola) == false);
    print_test("mostrar primero ", cola_ver_primero(cola) == &a);

    /* Pruebo que desencolar a */
    print_test("desencolar elemento", cola_desencolar(cola) == &a);

    /* Pruebo estado y mostrar primer elemento*/

    print_test("estado cola no vacia (false)", cola_esta_vacia(cola) == false);
    print_test("mostrar primero ", cola_ver_primero(cola) == &b);

    /* Pruebo que desencolar b */
    print_test("desencolar elemento", cola_desencolar(cola) == &b);

    /* Pruebo estado y mostrar primer elemento*/

    print_test("estado cola no vacia (false)", cola_esta_vacia(cola) == false);
    print_test("mostrar primero ", cola_ver_primero(cola) == &c);

    //Ahora la cola contiene a c y d

    /* Destruyo la cola (no vacía)*/

    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
}


/* Pruebas de la cola al trabajar con un volumen grande de elementos */

void pruebas_cola_volumen_alumno() {

    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    cola_t* cola_vol = cola_crear();
    bool ok;

    /* Pruebo encolar todos los elementos */
    ok = true;
    int* vector = malloc(VOLUMEN * sizeof(int*));
    for (size_t i=0 ; i < VOLUMEN; i++){
      vector[i] = (int)i;
      // Si algun elemento no se pudo guardar correctamente, ok sera false
      ok &= cola_encolar(cola_vol, &vector[i]);
    }
    free(vector);

    print_test("se pudieron encolar todos los elementos", ok);

    /* Pruebo que al desencolar el primero anterior coincide con el elemento a desencolar */
    ok = true;
    int* valor;
    int* first;

    for (size_t j = VOLUMEN; j>0 ; j--) {
        first = cola_ver_primero(cola_vol);
        valor = cola_desencolar(cola_vol);
        ok &= ((valor == first)); 
    }
    print_test("se pudieron desencolar todos los elementos", ok);

    /* Pruebo que al desencolar todos los elementos,
    la cola tiene el comportamiento de estar vacía*/

    print_test("estado vacia (true)", cola_esta_vacia(cola_vol) == true);
    print_test("desencolar cola vacía", cola_desencolar(cola_vol) == NULL);
    print_test("mostrar first cola vacía", cola_ver_primero(cola_vol) == NULL);

    /* Destruyo la cola (vacía)*/
    cola_destruir(cola_vol, NULL);
    print_test("la cola fue detruida", true);
}
//--------------------------------------------------------------------

void pruebas_cola_alumno() {

    cola_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);

    pruebas_cola_vacia_alumno();
    pruebas_cola_null_alumno();
    pruebas_cola_un_elemento_alumno();
    pruebas_cola_algunos_elementos_alumno();
    pruebas_cola_volumen_alumno();

}

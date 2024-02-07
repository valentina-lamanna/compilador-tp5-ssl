#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "symbol.h"

struct datoTS* buscarTS (struct datoTS* raiz, char* identificador) {
    if (raiz == NULL || strcmp(raiz->identificador, identificador) == 0)
        return raiz;

    if (strcmp(raiz->identificador, identificador) > 0)
        return buscarTS(raiz->izq, identificador);

    return buscarTS(raiz->der, identificador);
}

struct datoTS* insertarTS (struct datoTS* raiz, char* identificador, TOKEN token) {
    if (raiz == NULL)
        return nuevoDatoTS(identificador, token);   // Si estoy en una hoja, creo el dato

    if (strcmp(raiz->identificador, identificador) > 0) {           // Voy a izquierda
        raiz->izq = insertarTS(raiz->izq, identificador, token);
    } else if (strcmp(raiz->identificador, identificador) < 0) {    // Voy a derecha
        raiz->der = insertarTS(raiz->der, identificador, token);
    }

    return raiz;
}

struct datoTS* nuevoDatoTS(char* identificador, TOKEN token) {
    struct datoTS* dato = (struct datoTS*)malloc(sizeof(struct datoTS));

    strcpy(dato->identificador, identificador);
    dato->token = token;

    dato->izq = NULL;
    dato->der = NULL;

    return dato;
}



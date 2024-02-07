#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

#include "semantic.h"

struct datoTS {
    char            identificador[32];
    int             token;      // Token de Bison
    struct datoTS*  izq;
    struct datoTS*  der;
};

struct datoTS* buscarTS (struct datoTS*, char *);
struct datoTS* insertarTS (struct datoTS*, char *, TOKEN);
struct datoTS* nuevoDatoTS (char*, TOKEN);
void           inorden (struct datoTS*);
#endif

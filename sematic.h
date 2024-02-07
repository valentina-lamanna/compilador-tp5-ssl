#ifndef SEMATIC_H_INCLUDED
#define SEMATIC_H_INCLUDED

#include "parser.h"
struct datoTS* ts;

char bufferLexemas[40];

void generar (char*, char*, char*, char*);
void comenzar (void);
void terminar (void);
int declarar (void);
struct REG_EXPRESION procesarId (void);
struct REG_EXPRESION procesarCte (void);
void leer (struct REG_EXPRESION);
void escribir (struct REG_EXPRESION);
void asignar (struct REG_EXPRESION, struct REG_EXPRESION);
struct REG_EXPRESION genInfijo(struct REG_EXPRESION, int, struct REG_EXPRESION);
struct REG_EXPRESION crearTemp (void);

#endif

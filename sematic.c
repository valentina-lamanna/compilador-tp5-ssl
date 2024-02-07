#include <stdio.h>
#include "sematic.h"
#include "symbol.h"
#include "scanner.h"

int nroTemp = 1;

void generar(char* codOp, char* arg1, char* arg2, char* arg3) {
    if (!strcmp(arg3, "")) {
        printf("%s %s,%s\n",codOp, arg1, arg2);    
    } else {
        printf("%s %s,%s,%s\n",codOp, arg1, arg2, arg3);
    }
}

void comenzar (void) {
    
    ts = NULL;
    ts = insertarTS(ts, "programa", PROGRAMA);
    insertarTS(ts, "declaracion", DECLARAR);
    insertarTS(ts, "leer", LEER);
    insertarTS(ts, "escribir", ESCRIBIR);
    insertarTS(ts, "fin", FIN);

    generar("Load", "rtlib", "", "");
}

void terminar (void) {
    generar("Exit", "", "", "");
}

int declarar (void) {
    struct datoTS* busqueda = buscarTS(ts, bufferLexemas);
    if (busqueda) {
        yysemerrs++;
        strcpy(yyerrorBuffer, "Error semantico: identificador ");
        strcat(yyerrorBuffer, bufferLexemas);
        strcat(yyerrorBuffer, " ya fue declarado");
        yyerror(yyerrorBuffer);
        return 1;
    } else {
        insertarTS(ts, bufferLexemas, ID);
        generar("Reserve", bufferLexemas, "4", "");
        return 0;
    }
}

struct REG_EXPRESION procesarId (void) {
    struct REG_EXPRESION t;
    t.valor = 1; // Para verificar tirar YYERROR
    if(!buscarTS(ts, bufferLexemas)) { // IDENTIFICADOR NO DEFINIDO
        yysemerrs++;

        strcpy(yyerrorBuffer, "Error semantico: identificador ");
        strcat(yyerrorBuffer, bufferLexemas);
        strcat(yyerrorBuffer, " NO declarado");
        yyerror(yyerrorBuffer);
    } else {
        t.token = ID;
        strcpy(t.nombre, bufferLexemas);
        t.valor = 0;
    }
    return t;
}

struct REG_EXPRESION procesarCte (void) {
    struct REG_EXPRESION t;
    t.token = CONSTANTE;
    strcpy(t.nombre, bufferLexemas);
    sscanf(bufferLexemas, "%d", &t.valor);
    return t;
}

void leer (struct REG_EXPRESION in) {
    generar("Read", in.nombre, "Integer", "");
}

void escribir (struct REG_EXPRESION out) {
    generar("Write", out.nombre, "Integer", "");
}

void asignar (struct REG_EXPRESION izq, struct REG_EXPRESION der) {
    generar("Store", der.nombre, izq.nombre, "");
}

struct REG_EXPRESION genInfijo(struct REG_EXPRESION opIzq, int op, struct REG_EXPRESION opDer) {
    struct REG_EXPRESION temp = crearTemp();
    char codOp[4];
    switch (op) {
        case '+':
            strcpy(codOp, "ADD");
            break;
        case '-':
            strcpy(codOp, "SUB");
            break;
        case '*':
            strcpy(codOp, "MUL");
            break;
        case '/':
            strcpy(codOp, "DIV");
            break;
        case NEGATIVO:
            strcpy(codOp, "NEG");
    }
    generar(codOp, opIzq.nombre, opDer.nombre, temp.nombre);
    return temp;
}

struct REG_EXPRESION crearTemp (void) {
    struct REG_EXPRESION temp;
    temp.token = ID;
    snprintf(temp.nombre, sizeof temp.nombre, "Temp#%d", nroTemp);
    strcpy(bufferLexemas, temp.nombre);
    declarar();
    nroTemp++;
    return temp;
}

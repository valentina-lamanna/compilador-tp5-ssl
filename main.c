/* GRUPO 5 */
/* Integrantes: Valentina Lamanna, Micaela Raiter, y Lucila Melamed */
/* Curso K2004 (Jueves TM) */
/* Febrero 2021 */

#include <stdio.h>
#include "parser.h"


int main () {
 switch (yyparse()) {
        case 1:
            printf("Errores de compilación\n");
            break;
        case 2:
            printf("Error de memoria");
            break;
        case 0:
            printf("Compilación realizada con éxito\n");
            break;
    }
    
   printf("Errores sintácticos: %d  -  Errores léxicos: %d - Errores semánticos: %d\n", yynerrs, yylexerrs, yysemerrs);
}


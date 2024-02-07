%code top{
#include <stdio.h>
#include "scanner.h" // se tiene que relacionar con scanner.l
#include "semantic.h"
}

%code provides {
typedef enum yytokentype TOKEN;

struct REG_EXPRESION {
    TOKEN token;        
    char nombre[32];
    int valor;
};

struct YYSTYPE {        // como el pdf de bison
    char * lexema;
    struct REG_EXPRESION regExp;
};

void yyerror(const char *s);
extern int yylexerrs;  /* Contador de Errores Léxicos */
extern int yynerrs;    /* Contador de Errores Sintácticos */
extern int yysemerrs; /* Contador de Errores Semanticos */
extern char yyerrorBuffer[255];
}

%defines "parser.h"
%output "parser.c" 


%define api.value.type{struct YYSTYPE}
%define parse.error verbose /* Mas detalles cuando el Parser encuentre un error en vez de "Syntax Error" */

%token  PROGRAMA DECLARAR LEER ESCRIBIR FIN ID CONSTANTE PUNCTVALIDO ASIGNACION
%left '+' '-'
%left '*' '/'
%precedence NEGATIVO


%%

programa               : PROGRAMA { comenzar(); } listaSentencias FIN { terminar(); if (yynerrs || yylexerrs || yysemerrs) YYABORT;}
listaSentencias        : listaSentencias sentencia
                       | sentencia
                       ;
sentencia		: declaracion 
			| escritura
                       | lectura
			| asignacion
                       | error ';'
			;
declaracion		: DECLARAR ID ';' 			       { strcpy(bufferLexemas, yylval.lexema); if(declarar()) YYERROR; }
			; 
escritura		: ESCRIBIR '(' listaExpresiones ')' ';'  
			; 
lectura 		: LEER '(' listaIdentificadores ')' ';' 
			;
asignacion		: ID ASIGNACION expresion ';' 	        { asignar($3.regExp, $1.lexema); }
			;			
listaExpresiones       : listaExpresiones ',' expresion                { escribir($3.regExp); }
                       | expresion                                    { escribir($1.regExp); }
                       ;
listaIdentificadores   : listaIdentificadores ',' identificador        { leer($3.regExp); }
                       | identificador                                 { leer($1.regExp); }
                       ;
expresion              : expresion '+' expresion   { $$.regExp = genInfijo($1.regExp, '+', $3.regExp); }
                       | expresion '-' expresion   { $$.regExp = genInfijo($1.regExp, '-', $3.regExp); }
                       | expresion '*' expresion   { $$.regExp = genInfijo($1.regExp, '*', $3.regExp); }
                       | expresion '/' expresion   { $$.regExp = genInfijo($1.regExp, '/', $3.regExp); }
                       | '-' termino %prec NEGATIVO       { struct REG_EXPRESION r = { ID, "", 0 }; $$.regExp = genInfijo($2.regExp, NEGATIVO, r); }
                       | termino
                       ;
termino	        : identificador
                       | CONSTANTE                 { strcpy(bufferLexemas, yylval.lexema); $$.regExp = procesarCte(); }
                       | '(' expresion ')'         { $$.regExp = $2.regExp; }
                       ;
identificador          : ID  { strcpy(bufferLexemas, yylval.lexema); $$.regExp = procesarId(); if($$.regExp.valor) YYERROR; }
%%


int yylexerrs = 0;
int yysemerrs = 0;
char yyerrorBuffer[255];

void yyerror(const char* s){

	printf("Línea #%d: %s\n", yylineno, s);
	return;
}

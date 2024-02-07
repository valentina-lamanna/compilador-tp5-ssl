%{
#include <stdio.h>
#include <strings.h>
#include "parser.h"

void enviarErrorLexico(const char*);
%}

%{
char buffer[200];
%}

%option header-file="scanner.h"
%option outfile="scanner.c"
%option nodefault
%option noinput
%option nounput
%option yylineno

L                   [[:alpha:]]
D                   [0-9]
LD                  [[:alnum:]]
S                   [[:space:]]
E                   [[:^alnum:]]{-}[[:space:]]{-}[;,(.)]{-}[+\-\*/]    


%%
programa	                    return PROGRAMA;
declarar	                    return DECLARAR;
leer	                            return LEER;
escribir	                    return ESCRIBIR;
fin-prog		            return FIN;
{L}{LD}*                           {yylval.lexema = strdup(yytext); return ID;}
{D}+                               {yylval.lexema = strdup(yytext); return CONSTANTE;}
\+                                 return '+';
"<-"                               return ASIGNACION;
-                   		    return '-';
\*                  		    return '*';
"/"                                return '/';
"("                                return '(';
")"                                return ')';
","                                return ',';
";"                                return ';';
"##".*                          ;/* NO HACE NADA, ES UN COMENTARIO */
{S}+                            ;/* ESPACIO */
{E}+                            {yylexerrs++; sprintf(buffer,"Error Léxico:  Cadena desconocida: %s", yytext); yyerror(buffer);}
{L}{LD}*{E}({LD}|{E})*          {yylexerrs++; sprintf(buffer,"Error Léxico:  Identificador inválido: %s", yytext); yyerror(buffer);}
{D}{LD}+                        {yylexerrs++; sprintf(buffer,"Error Léxico:  Constante inválida: %s",yytext); yyerror(buffer);}
%%


void enviarErrorLexico(const char *s) {
    strcpy(yyerrorBuffer, s);
    strcat(yyerrorBuffer, yytext);
    yyerror(yyerrorBuffer);
}



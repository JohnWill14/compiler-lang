%{
#include <stdio.h>
#include "tokens.h"

%}

%option noyywrap

delim	     [ \t\n]
whites       {delim}+
letter	     [A-Za-z]
digit	     [0-9]
id	         {letter}({letter}|{digit})*
num	         [+-]?{digit}+
real         [+-]?({num}\.({num})?|({num}[df]))
comparison   "<="|"<"|"=="|"<>"|">="|">" 
alloc        "="|"+="|"-="|"/="|"*="
arit         \+|\-|\/|\*|\*\*
literal      \"(.+)\"
type         "Int"|"Long"|"String"|"Float"|"Double"|"Boolean"|"Char"
logic        "or"|"and"|"not"|"|"|">>"|"<<"
line_comment \/\/.*
block_comment \/\*([^*]|\*+[^*/])*\*+\/

%%
{whites}        ; // no action and no return
{line_comment}  ; // no action and no return
{block_comment}  ; // no action and no return
if		     return IF; 
else		 return ELSE; 
for		     return FOR;
in		     return IN; 
while		 return WHILE; 
loop	     return LOOP;
fun		     return FUN; 
var		     return VAR; 
val	         return VAL; 
{type}       return TYPE;
{logic}      return LOGIC;
{num}	     return NUM; 
{real}	     return NUM; 
{id}		 return ID; 
{comparison} return COMPARISON; 
{alloc}      return ALLOC; 
"("          return LP; 
")"          return RP; 
"{"          return LC; 
"}"          return RC; 
"["          return LB; 
"]"          return RB; 
{arit}       return MATH;
{literal}    return TEXT;
":"          return COLON;
","          return COMMA;
";"          return FINALIZE;
.            {
                printf("Term not identified\n, %s \nthere is an invalid term detected\n", yytext); 
                exit(1);    
            }
%%

int main(int argc, char *argv[]){
    yyin = fopen(argv[1], "r");

    int lookahead;
    
    while ((lookahead = yylex()) != 0){
        // trata o token recebido do analisador léxico
        switch(lookahead){
            case IF: printf("IF\n"); break;
            case ELSE: printf("ELSE\n"); break;
            case FOR: printf("FOR\n"); break;
            case IN: printf("IN\n"); break;
            case WHILE: printf("WHILE\n"); break;
            case LOOP: printf("LOOP\n"); break;
            case VAR: printf("VAR\n"); break;
            case FUN: printf("FUN\n"); break;
            case VAL: printf("VAL\n"); break;
            case TYPE: printf("TYPE: %s\n", yytext); break;
            case NUM: printf("NUM: %s\n", yytext); break;
            case ID: printf("ID: %s\n", yytext); break;
            case COMPARISON: printf("COMPARISON\n"); break;
            case ALLOC: printf("ALLOC\n"); break;
            case LP: printf("LP: %s\n", yytext); break;
            case RP: printf("RP: %s\n", yytext); break;
            case LC: printf("LC: %s\n", yytext); break;
            case RC: printf("RC: %s\n", yytext); break;
            case LB: printf("LB: %s\n", yytext); break;
            case RB: printf("RB: %s\n", yytext); break;
            case MATH: printf("MATH: %s\n", yytext); break;
            case TEXT: printf("TEXT: %s\n", yytext); break;
            case COLON: printf("COLON: %s\n", yytext); break;
            case COMMA: printf("COMMA: %s\n", yytext); break;
            case LOGIC: printf("LOGIC: %s\n", yytext); break;
            case FINALIZE: printf("FINALIZE: %s\n", yytext); break;
        }
    }

    fclose(yyin);
}
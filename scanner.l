/***************************************************************************
Scanner for the ELFR language
***************************************************************************/
%{
/*=========================================================================
C-libraries and Token definitions
=========================================================================*/
#include <string.h> /* for strdup */
#include <stdlib.h> /* for atoi */
#include "Parser.tab.h" /* for token definitions and yylval */
%}
/*=========================================================================
TOKEN Definitions
=========================================================================*/
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
type         "Int"|"Long"|"String"|"Float"|"Double"|"Boolean"|"Char"|"Void"
logic        "or"|"and"|"not"|"|"|">>"|"<<"
line_comment \/\/.*
block_comment \/\*([^*]|\*+[^*/])*\*+\/
print        "print"|"println"



/*=========================================================================
REGULAR EXPRESSIONS defining the tokens for the Simple language
=========================================================================*/
%%
{whites}        ; // no action and no return
{line_comment}  ; // no action and no return
{block_comment}  ; // no action and no return

{print}      return (PRINT); 
if		     return (IF); 
else		 return (ELSE); 
for		     return (FOR);
in		     return (IN); 
while		 return (WHILE); 
loop	     return (LOOP);
def		     return (FUN); 
var		     return (VAR); 
val	         return (VAL); 
{type}       {
                yylval.id = (char *) strdup(yytext);
                return (TYPE);
            }
{logic}      return (LOGIC);
{num}	     {
                sscanf(yytext, "%d", &yylval.intval);
                return (NUM);
             } 
{real}	     { 
                sscanf(yytext, "%lf", &yylval.doubleval);
                return (NUM);
            } 
{id}		 {
                yylval.id = (char *) strdup(yytext);
                return (IDENTIFIER);
            } 
{comparison} return (COMPARISON); 
{alloc}      return (ALLOC); 
"("          return (LP); 
")"          return (RP); 
"{"          return (LC); 
"}"          return (RC); 
"["          return (LB); 
"]"          return (RB); 
{arit}       return (MATH);
{literal}      {
                yylval.id = (char *) strdup(yytext);
                return (TEXT);
            } 
":"          return (COLON);
","          return (COMMA);
";"          return (FINALIZE);
.            {
                printf("Term not identified\n, %s \nthere is an invalid term detected\n", yytext); 
                exit(1);    
            }
%%
/************************** End Scanner File *****************************/
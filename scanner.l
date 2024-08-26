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
%option yylineno

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
logic        "or"|"and"
line_comment \/\/.*
block_comment \/\*([^*]|\*+[^*/])*\*+\/
return_token "return"
break_token  "break"


/*=========================================================================
REGULAR EXPRESSIONS defining the tokens for the Simple language
=========================================================================*/
%%
{whites}        ; // no action and no return
{line_comment}  ; // no action and no return
{block_comment}  ; // no action and no return

if		     return (IF); 
else		 return (ELSE); 
for		     return (FOR);
in		     return (IN); 
while		 return (WHILE); 
loop	     return (LOOP);
def		     return (FUN); 
var		     return (VAR); 
val	         return (VAL); 
{break_token}        return (BREAK_TOKEN);
{return_token}       return (RETURN_TOKEN);
{type}       {
                yylval.id = (char *) strdup(yytext);
                return (TYPE);
            }
{logic}      {
                yylval.id = (char *) strdup(yytext);
                return (LOGIC);
            } 
{num}	     {
                //sscanf(yytext, "%d", &yylval.intval);
                yylval.id = (char *) strdup(yytext);
                return (NUM);
             } 
{real}	     { 
                //sscanf(yytext, "%lf", &yylval.doubleval);
                yylval.id = (char *) strdup(yytext);
                return (NUM);
            } 
{id}		 {
                yylval.id = (char *) strdup(yytext);
                return (IDENTIFIER);
            } 
{comparison} {
                yylval.id = (char *) strdup(yytext);
                return (COMPARISON);
            }
{alloc}      {
                yylval.id = (char *) strdup(yytext);
                return (ALLOC); 
            }
"("          return (LP); 
")"          return (RP); 
"{"          return (LC); 
"}"          return (RC); 
"["          return (LB); 
"]"          return (RB); 
{arit}        {
                yylval.id = (char *) strdup(yytext);
                return (MATH);
            }
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
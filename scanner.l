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

if		     {
              puts("<IF,_>");
              return (IF);
            } 
else		 {
                puts("<ELSE,_>");
                return (ELSE);
             }
for		     {
                puts("<FOR,_>");
                return (FOR);
            }
in		     {
                puts("<IN,_>");
                return (IN);
            }

while		 {
                puts("<WHILE,_>");
                return (WHILE);
            }
loop	    {
            puts("<LOOP,_>");
             return (LOOP);
            }
def		     {
                puts("<FUN,def>");
                return (FUN);
            } 
var		    {
             puts("<VAR,var>");
             return (VAR);
            }
val	        {
                 puts("<VAL,val>");
                return (VAL);
            } 
{break_token}        {
                        puts("<BREAK_TOKEN,break>");
                        return (BREAK_TOKEN);
                    }
{return_token}       {
                        puts("<RETURN_TOKEN,return>");
                        return (RETURN_TOKEN);
                    }
{type}       {
                yylval.id = (char *) strdup(yytext);
                printf("<TYPE,%s>", yytext);
                return (TYPE);
            }
{logic}      {
                yylval.id = (char *) strdup(yytext);
                printf("<LOGIC,%s>", yytext);
                return (LOGIC);
            } 
{num}	     {
                //sscanf(yytext, "%d", &yylval.intval);
                yylval.id = (char *) strdup(yytext);
                printf("<NUM,%s>", yytext);
                return (NUM);
             } 
{real}	     { 
                //sscanf(yytext, "%lf", &yylval.doubleval);
                yylval.id = (char *) strdup(yytext);
                printf("<NUM,%s>", yytext);
                return (NUM);
            } 
{id}		 {
                yylval.id = (char *) strdup(yytext);
                printf("<IDENTIFIER,%s>", yytext);
                return (IDENTIFIER);
            } 
{comparison} {
                yylval.id = (char *) strdup(yytext);
                printf("<COMPARISON,%s>", yytext);
                return (COMPARISON);
            }
{alloc}      {
                yylval.id = (char *) strdup(yytext);
                printf("<ALLOC,%s>", yytext);
                return (ALLOC); 
            }
"("          {
                puts("<LP,(>");
                return (LP);
            } 
")"          {
                puts("<RP,)>");
                return (RP);
            } 
"{"          {
                puts("<LC,{>");
                return (LC);
            } 
"}"          {
                puts("<RC,}>");
                return (RC);
            } 
"["          {
                puts("<LB,[>");
                return (LB);
            }
"]"          {

                puts("<LB,]>");
                return (RB);
            } 
{arit}        {
                yylval.id = (char *) strdup(yytext);
                printf("<MATH,%s>", yytext);
                return (MATH);
            }
{literal}      {
                yylval.id = (char *) strdup(yytext);
                printf("<TEXT,%s>", yytext);
                return (TEXT);
            } 
":"          {
                puts("<COLON,:>");
                return (COLON);
            }
","          {
                puts("<COLON,,>");
                return (COMMA);
            }
";"          {

                puts("<FINALIZE,;>");
                return (FINALIZE);
            }
.            {
                printf("Term not identified\n, %s \nthere is an invalid term detected\n", yytext); 
                exit(1);    
            }
%%
/************************** End Scanner File *****************************/
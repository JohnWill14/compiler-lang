%{
#include <string.h> /* for strdup */
#include <stdlib.h> /* for atoi */
#include "Parser.tab.h" /* for token definitions and yylval */
%}

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
{whites}        ; 
{line_comment}  ; 
{block_comment}  ; 

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
                printf("<TYPE,%s>\n", yytext);
                return (TYPE);
            }
{logic}      {
                yylval.id = (char *) strdup(yytext);
                printf("<LOGIC,%s>\n", yytext);
                return (LOGIC);
            } 
{num}	     {
                //sscanf(yytext, "%d", &yylval.intval);
                yylval.id = (char *) strdup(yytext);
                printf("<NUM,%s>\n", yytext);
                return (NUM);
             } 
{real}	     { 
                //sscanf(yytext, "%lf", &yylval.doubleval);
                yylval.id = (char *) strdup(yytext);
                printf("<NUM,%s>\n", yytext);
                return (NUM);
            } 
{id}		 {
                yylval.id = (char *) strdup(yytext);
                printf("<IDENTIFIER,%s>\n", yytext);
                return (IDENTIFIER);
            } 
{comparison} {
                yylval.id = (char *) strdup(yytext);
                printf("<COMPARISON,%s>\n", yytext);
                return (COMPARISON);
            }
{alloc}      {
                yylval.id = (char *) strdup(yytext);
                printf("<ALLOC,%s>\n", yytext);
                return (ALLOC); 
            }
"("          {
                puts("<LP,(>\n");
                return (LP);
            } 
")"          {
                puts("<RP,)>\n");
                return (RP);
            } 
"{"          {
                puts("<LC,{>\n");
                return (LC);
            } 
"}"          {
                puts("<RC,}>\n");
                return (RC);
            } 
"["          {
                puts("<LB,[>\n");
                return (LB);
            }
"]"          {

                puts("<LB,]>\n");
                return (RB);
            } 
{arit}        {
                yylval.id = (char *) strdup(yytext);
                printf("<MATH,%s>\n", yytext);
                return (MATH);
            }
{literal}      {
                yylval.id = (char *) strdup(yytext);
                printf("<TEXT,%s>\n", yytext);
                return (TEXT);
            } 
":"          {
                puts("<COLON,:>\n");
                return (COLON);
            }
","          {
                puts("<COLON,,>\n");
                return (COMMA);
            }
";"          {

                puts("<FINALIZE,;>\n");
                return (FINALIZE);
            }
.            {
                printf("Term not identified\n, %s \nthere is an invalid term detected\n", yytext); 
                exit(1);    
            }
%%
%{/*************************************************************************
Compiler for the Simple language
***************************************************************************/
/*=========================================================================
C Libraries, Symbol Table, Code Generator & other C code
=========================================================================*/
#include <stdio.h> /* For I/O */
#include <stdlib.h> /* For malloc here and in symbol table */
#include <string.h> /* For strcmp in symbol table */
#include "SymbolTable.h" /* Symbol Table */
#include "Tree.h" /* Stack Machine */
#include "CG.h" /* Code Generator */
#ifndef YYDEBUG  /* For Debugging */
    #define YYDEBUG 1
#endif
extern int yylineno;
extern char* yytext;

int errors; /* Error Count */

int yylex(void);
int yyerror(char* s);


/*-------------------------------------------------------------------------
Install identifier & check if previously defined.
-------------------------------------------------------------------------*/
void add_identify ( char *sym_name ){
    symrec *s;
    s = getsym (sym_name);
    if (s == 0)
        s = putsym (sym_name);
    else { 
        errors++;
        printf( "%s is already defined\n", sym_name );
    }
}

/*-------------------------------------------------------------------------
If identifier is defined, generate code
-------------------------------------------------------------------------*/

void context_check(char *sym_name ){ 
    symrec *identifier;
    identifier = getsym( sym_name );
    if ( identifier == 0 ){ 
        errors++;
        printf( "%s", sym_name );
        printf( "%s\n", " is an undeclared identifier" );
    }
}

%}

/*=========================================================================
SEMANTIC RECORDS
=========================================================================*/
%union semrec{ /* The Semantic Records */

    int intval; /* Integer values */
    int doubleval; /* Double values */
    char *id; /* Identifiers */
    struct lbs *lbls; /* For backpatching */
}

/*=========================================================================
TOKENS
=========================================================================*/

%start program
%token <intval> NUMBER/* Simple integer */
%token <doubleval> REAL 
%token <id> IDENTIFIER /* Simple identifier */
%token <lbls> IF ELSE FOR WHILE LOOP
%token <id> TYPE 
%token <id> TEXT
%token <id> ALLOC
%token <id> NUM
%token <id> MATH
%token <id> COMPARISON
%token <id> LOGIC
%token FUN VAR VAL IN  
%token   LP RP LC RC LB RB PARAMETERS PARAMETER BLOCK
%token COLON COMMA  FINALIZE PRINT BREAK_TOKEN RETURN_TOKEN 
            ALLOC_LABEL  OPERATION_LABEL
/*=========================================================================
OPERATOR PRECEDENCE
=========================================================================*/
%left '-' '+'
%left '*' '/'
%right '^'
/*=========================================================================
GRAMMAR RULES for the Simple language
=========================================================================*/
%%
program:  function code
;
code: 
       /* empty */
       | program

;
function: FUN
            IDENTIFIER{
                    add_identify($2);
                    create_no($2, FUN);
                    create_no(NULL, PARAMETERS);
                }
            LP
            declarations_parameter
            RP
            COLON
            TYPE{ 
                    revert_no();
                    create_no($8, TYPE);
                    revert_no();
                    create_no(NULL, BLOCK);
                }
            LC 
             block 
            RC{
                finalize_tree();
            }
;
declarations_parameter : /* empty */
            | IDENTIFIER COLON TYPE { 
                            add_identify( $1 ); 
                            create_no($1, PARAMETER);
                            create_no($3, TYPE);
                            revert_no();
                            revert_no();
                        } declaration_parameter 
            
;
declaration_parameter: /* empty */
            | COMMA declarations_parameter
;
block : /* empty */ {revert_no();}
            | command block
;
command : PRINT LP TEXT RP FINALIZE {
                            create_no("print", PRINT);
                            create_no($3, TEXT);
                            revert_no();
                            revert_no();
                    }
        |VAR{
            create_no(NULL, VAR);
        } declaration 
        |VAL {
            create_no(NULL, VAL);
        } declaration 
        |attribution 
        | while 
        | condition  
        | breakkk{
            create_no(NULL, BREAK_TOKEN);
        }
        | return_ss{
            create_no(NULL, RETURN_TOKEN);
        }
;
declarations:
            COMMA declaration  
           | FINALIZE{
            revert_no();
           }
;
declaration: IDENTIFIER COLON TYPE {
                add_identify($1);
                create_no($1, IDENTIFIER);
                create_no($3, TYPE);
                revert_no();
                revert_no();
            } declarations

;
attribution: IDENTIFIER ALLOC {
            create_no(NULL, ALLOC_LABEL);
            context_check($1);

            create_no($1, IDENTIFIER);
            revert_no();
            create_no($2, ALLOC);
            revert_no();
            create_no(NULL, OPERATION_LABEL);
        }
            novo_valor 
             
;
novo_valor: operation 
            |label_abstrato
;
operation: NUM FINALIZE{
            create_no($1, NUM);
            revert_no();
        }
        | NUM {
            create_no($1, NUM);
            revert_no();
        } operation
        | MATH{
                create_no($1, MATH);
                revert_no();
        } operation
;
label_abstrato: TEXT
                | IDENTIFIER
;
while: WHILE {
            create_no(NULL, WHILE);
        }
        LP
            logik
        RP
        LC {
            create_no(NULL, BLOCK);
        }
             block 
        RC{
            {revert_no();}
        }

;
logik: IDENTIFIER COMPARISON  IDENTIFIER logic_c {
            context_check($1);
            context_check($3);

            create_no($1, IDENTIFIER);
            revert_no();
            create_no($2, COMPARISON);
            revert_no();
            create_no($3, IDENTIFIER);
            revert_no();
        }
        | NUM COMPARISON  NUM logic_c {

            create_no($1, NUM);
            revert_no();
            create_no($2, COMPARISON);
            revert_no();
            create_no($3, NUM);
            revert_no();
        }
;
logic_c: /* empty */
    | LOGIC {
            create_no($1, LOGIC);
            revert_no();
    } logik
;
condition: IF {
            create_no(NULL, IF);
        }
        LP
            logik
        RP{
            create_no(NULL, BLOCK);
        }
        LC 
             block 
        RC
        condition_pod

;
condition_pod: /* empty */ {revert_no();}
        | ELSE{
            create_no(NULL, ELSE);
            create_no(NULL, BLOCK);
        }
        LC 
             block 
        RC{
            revert_no();
        }
;
breakkk: BREAK_TOKEN {
            create_no(NULL, BREAK_TOKEN);
            revert_no();
        } FINALIZE
;
return_ss: RETURN_TOKEN FINALIZE{
            create_no(NULL, RETURN_TOKEN);
            revert_no();
        }
        | RETURN_TOKEN IDENTIFIER FINALIZE{
            create_no(NULL, RETURN_TOKEN);
            revert_no();
            create_no($2, IDENTIFIER);
            revert_no();
        }
        | RETURN_TOKEN TEXT FINALIZE{
            create_no($2, TEXT);
            revert_no();
        }
        | RETURN_TOKEN{
            create_no(NULL, RETURN_TOKEN);
            revert_no();
        } operation FINALIZE
;

%%
/*=========================================================================
MAIN
=========================================================================*/
void main( int argc, char *argv[] ){ 
    extern FILE *yyin;
    ++argv; --argc;
    yyin = fopen( argv[0], "r" );
    errors = 0;
    yyparse ();
    if ( errors == 0 ){ 
        print_code ();
        printf ( "Sucessfull Parse Completed!!!\n" );
    }
}
/*=========================================================================
YYERROR
=========================================================================*/
int yyerror ( char *s ) /* Called by yyparse on error */
{
    errors++;
    printf("%s - not expected \"%s\" line %d\n", s, yylval, yylineno);
}
/**************************** End Grammar File ***************************/
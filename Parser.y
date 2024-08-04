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
#define YYDEBUG 1 /* For Debugging */
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

void context_check( enum code_ops operation, char *sym_name ){ 
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
%token FUN VAR VAL IN NUM 
%token COMPARISON ALLOC LP RP LC RC LB RB MATH 
%token COLON COMMA LOGIC FINALIZE PRINT
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
program : FUN
            IDENTIFIER{
                    add_identify($2);
                    create_no($2, DEF);
                    create_no(NULL, PARAMETERS);
                }
            LP
            declarations_parameter
            RP
            COLON
            TYPE{ 
                    revert_no();
                    create_no($8, PRIMITIVE);
                    revert_no();
                    create_no(NULL, BLOCK);
                }
            LC 
             block 
            RC{
                revert_no();
            }
;
declarations_parameter : /* empty */
            | IDENTIFIER COLON TYPE declaration_parameter { 
                                                  add_identify( $1 ); 
                                                  create_no($1, PARAMETER);
                                                  create_no($3, PRIMITIVE);
                                                  revert_no();
                                                  revert_no();
                                                }
            
;
declaration_parameter: /* empty */
            | COMMA declarations_parameter
;
block : /* empty */ {revert_no();}
            | command block
;
command : PRINT LP TEXT RP FINALIZE {
                            create_no("print", PRINT_FUN);
                            create_no($3, PRIMITIVE);
                            revert_no();
                            revert_no();
                    }
        |VAR declaration
        |VAL declaration
        |attribution
;
declarations:
            COMMA declaration  
           | FINALIZE
;
declaration: IDENTIFIER COMMA TYPE declarations

;
attribution: IDENTIFIER ALLOC operation
;
operation: NUM |
           NUM MATH NUM
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
    printf ( "Parse Completed\n" );
    if ( errors == 0 ){ 
        print_code ();
    }
}
/*=========================================================================
YYERROR
=========================================================================*/
int yyerror ( char *s ) /* Called by yyparse on error */
{
    errors++;
    printf("%s\n", s);
}
/**************************** End Grammar File ***************************/
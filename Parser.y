%{
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include "SymbolTable.h" 
#include "Tree.h"
#include "Print_tree.h" 
#ifndef YYDEBUG  
    #define YYDEBUG 1
#endif
extern int yylineno;
extern char* yytext;

int errors; 

int yylex(void);
int yyerror(char* s);


//SymbolTable
void add_identify_var(char *sym_name, int nivel, char* name_function, bool constante, char* type){
    symvar *s;
    s = getsymVar(sym_name, nivel, name_function);
    if (s == NULL)
        s = putsymVar(sym_name, nivel, name_function, constante, type);
    else { 
        errors++;
        printf( "variable %s is already defined in %s\n", sym_name, s->function);
    }
}

void check_var(char *sym_name, int nivel, char* name_function){
    symvar *s;
    s = getsymVar(sym_name, nivel, name_function);
    if (s == NULL){ 
        errors++;
        printf( "variable %s not is defined. line %d\n", sym_name, yylineno);
    }
}


void add_identify_func ( Tree* function ){
    symfunc *s;
    s = getsymfunc (function->label);
    if (s == NULL){
        Node* no = list_getItem(function->neighbors, 0);
        Tree* lista_de_parametros = no->value;
        int tam_p = list_get_size(lista_de_parametros->neighbors);
        char** name_array = (char **) malloc(sizeof(char *) * tam_p);
        int count = 0;

        list_forEach(non, lista_de_parametros->neighbors){
            Tree* tno = (Tree*)non->value;
            Node* no_type = list_getItem(tno->neighbors, 0);
            Tree* tno_type = (Tree*) no_type->value;

            name_array[count] = (char *) malloc (strlen(tno_type->label)+1);
            strcpy (name_array[count],tno_type->label);

            add_identify_var(tno->label, 1, function->label, 0, tno_type->label);

            count++;
        }


        Node* no_type = list_getItem(function->neighbors, 1);
        Tree* tno_type = (Tree*) no_type->value;
        char* type = (char *) malloc (strlen(tno_type->label)+1);
        strcpy (type,tno_type->label);

        s = putsymfunc (function->label, name_array, tam_p, type );
    } else { 
        errors++;
        printf( "function %s is already defined\n", function->label );
    }
}

void add_call ( Tree* call){

    int tam_p = list_get_size(call->neighbors);
    char** name_array = (char **) malloc(sizeof(char *) * tam_p);
    int count = 0;
    list_forEach(non, call->neighbors){

        Tree* tno = (Tree*)non->value;
        name_array[count] = (char *) malloc (strlen(tno->label)+1);
        strcpy (name_array[count],tno->label);
        count++;
    }

     putsymCall (yylineno, call->label, function_current, name_array, tam_p, nivel_block_current);
}

void context_check_func(char *sym_name ){ 
    symfunc *identifier;
    identifier = getsymfunc( sym_name );
    if ( identifier == NULL){ 
        errors++;
        printf( "%s", sym_name );
        printf( "%s\n", " is an undeclared identifier" );
    }
}

%}


%union semrec{ 

    int intval; 
    int doubleval; 
    char *id;
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
            ALLOC_LABEL  OPERATION_LABEL CALL_FUNCTION CALL_PARAM

%left '+' '-'
%left '*' '/'

%%
program:  function code
;
code: 
       /* empty */
       | program

;
function: FUN
            IDENTIFIER{
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
                    add_identify_func(current_tree);
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
command : VAR{
            create_no(NULL, VAR);
        } declaration 
        |VAL {
            create_no(NULL, VAL);
        } declaration_val {
                revert_no();
                revert_no();
        }

        |attribution {
            revert_no();
        }
        | while 
        | condition  
        | breakkk{
            create_no(NULL, BREAK_TOKEN);
        }
        | return_ss
        | call_function
;
declarations:
            COMMA declaration  
           | FINALIZE{
            revert_no();
           }
;
declaration: IDENTIFIER COLON TYPE {
                add_identify_var($1, nivel_block_current, function_current, constante_current, $3);
                    
                create_no($1, IDENTIFIER);
                create_no($3, TYPE);
                revert_no();
                revert_no();
            } declarations
             

;
declaration_val:IDENTIFIER COLON TYPE {
                add_identify_var($1, nivel_block_current, function_current, constante_current, $3);
                    
                create_no($1, IDENTIFIER);
                create_no($3, TYPE);
                revert_no();
                revert_no();
            } ALLOC {
                create_no(NULL, ALLOC_LABEL);
                check_var($1, nivel_block_current, function_current);
            
                create_no($1, IDENTIFIER);
                revert_no();
                create_no($5, ALLOC);
                revert_no();
                create_no(NULL, OPERATION_LABEL);
            }
            novo_valor
;
attribution: IDENTIFIER ALLOC {
            create_no(NULL, ALLOC_LABEL);
            check_var($1, nivel_block_current, function_current);
            errors += check_var_is_Constant($1, nivel_block_current, function_current);

            create_no($1, IDENTIFIER);
            revert_no();
            create_no($2, ALLOC);
            revert_no();
            create_no(NULL, OPERATION_LABEL);
        }
            novo_valor 
        | IDENTIFIER ALLOC LP {
            create_no(NULL, ALLOC_LABEL);
            check_var($1, nivel_block_current, function_current);

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
operation: FINALIZE{
            revert_no();
        } 
        | NUM {
            create_no($1, NUM);
            revert_no();
        } novo_valor
        | MATH{
                create_no($1, MATH);
                revert_no();
        } novo_valor
        | LP novo_valor RP novo_valor
        
;
label_abstrato: TEXT{
                    errors += checkString($1, nivel_block_current, function_current);
                    create_no($1, TEXT);
                    revert_no();
                } novo_valor
                | IDENTIFIER{
                    create_no($1, CALL_FUNCTION);
                } LP parameter_func RP {
                    add_call(current_tree);
                    revert_no();            
                } novo_valor
                | IDENTIFIER{

                    check_var($1, nivel_block_current, function_current);
                    create_no($1, IDENTIFIER);
                    revert_no();
                } novo_valor
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
logik: comparator COMPARISON{
            create_no($2, COMPARISON);
            revert_no();
        }  comparator logic_c 
        
;
 comparator: NUM{
                 create_no($1, NUM);
                revert_no();
            }| 
            IDENTIFIER{
                check_var($1, nivel_block_current, function_current);
                 create_no($1, IDENTIFIER);
                revert_no();
            }| 
            TEXT{
                errors += checkString($1, nivel_block_current, function_current);
                create_no($1, TEXT);
                revert_no();
            }
            | IDENTIFIER{
                create_no($1, CALL_FUNCTION);
            } LP parameter_func RP {
                add_call(current_tree);
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
        | ELSE condition
;
breakkk: BREAK_TOKEN {
            create_no(NULL, BREAK_TOKEN);
            errors += check_break(yylineno);
            revert_no();
        } FINALIZE
;
return_ss: RETURN_TOKEN{
            create_no(NULL, RETURN_TOKEN);
        }
        return_type 
        FINALIZE{
            list_add_returnsList(yylineno);
            revert_no();
        }
;
return_type: /* empty */ 
            | IDENTIFIER{
                create_no($1, IDENTIFIER);
                revert_no();  
            }
            | TEXT{
                errors += checkString($1, nivel_block_current, function_current);
                create_no($1, TEXT);
                revert_no();  
            }
            | IDENTIFIER{
                create_no($1, CALL_FUNCTION);
            } LP parameter_func RP {
                add_call(current_tree);
                revert_no();            
            }
;
call_function: IDENTIFIER{
            create_no($1, CALL_FUNCTION);
        } LP parameter_func RP {
            add_call(current_tree);
            revert_no();            
        }
        FINALIZE
;
parameter_func: /* empty */
            |IDENTIFIER{
                create_no($1, CALL_PARAM);
                revert_no();            
            } parameter_final
            |NUM{
                create_no($1, CALL_PARAM);
                revert_no();            
            } parameter_final
            |TEXT{
                create_no($1, CALL_PARAM);
                revert_no();            
            } parameter_final
            |IDENTIFIER LP{
                 create_no($1, CALL_FUNCTION);
            } parameter_func {
              add_call(current_tree);
             revert_no(); 
            } RP parameter_final
;
parameter_final: /* empty */
                |COMMA parameter_func
;
%%

void addFuncs(){
    char** p =  (char **) malloc(sizeof(char *) * 2);
    char c[] = "String";
    p[0] = (char *) malloc (strlen("String")+1);
    strcpy(p[0], c);
    putsymfunc ("println", p, 1, "Void" );
    putsymfunc ("print", p, 1, "Void" );
}

void main( int argc, char *argv[] ){ 
    extern FILE *yyin;
    ++argv; --argc;
    addFuncs();
    yyin = fopen( argv[0], "r" );
    errors = 0;
    yyparse ();
    errors += valid();
    errors += check_return();
    errors += check_returns_f();

    
    if ( errors == 0 ){ 
        showFuncTable();
        showVarTable();
        showCallTable();
        print_code ();
        printf ( "Sucessfull Parse Completed!!!\n" );
    }else{
        printf ( "Error Parse not Completed\n" );
    }
}

int yyerror ( char *s ) {
    errors++;
    printf("%s - not expected \"%s\" line %d\n", s, yylval, yylineno);
}
/***************************************************************************
Code Generator
***************************************************************************/

#include "Parser.tab.h" /* for token definitions and yylval */

void addSpace(int space){
    for(int i=0;i<space;i++){
        printf(" ");
    }
}

char* getCode(int code){
    switch(code){
        case FUN:
            return "Function";
        break;
        case PARAMETERS:
            return "lista de parametros";
        break;
        case TYPE:
            return "tipo primitivo";
        break;
        case BLOCK:
            return "bloco de código";
        break;
        case PARAMETER:
            return "unico parametro";
        break;
        case PRINT:
            return "funcao print";
        break;
        case TEXT:
            return "string";
        break;
        case VAR:
            return "declaracao de variaveis";
        break;
        case VAL:
            return "declaracao de constantes";
        break;
        case IDENTIFIER:
            return "variavel, funcao ou algum outro trem";
        break;
        case ALLOC_LABEL:
            return "inicio de atribuicao de valored";
        break;
        case ALLOC:
            return "simbolo de alocacao";
        break;
        case OPERATION_LABEL:
            return "inicio de uma operacao";
        break;
        case MATH:
            return "matematyica";
        break;
        case NUM:
            return "numero";
        break;
        case COMPARISON:
            return "comparsion";
        break;

        case WHILE:
            return "inicio block while";
        break;

        case LOGIC:
            return "logic";
        break;

        case IF:
            return "if";
        break;

        case ELSE:
            return "else";
        break;
        case BREAK_TOKEN:
            return "break";
        break;
        case RETURN_TOKEN:
            return "return";
        break;

        default:
            return "faz o L";
        break;

               
    }

}

void showTree(Tree* tree, int nivel){
    if(tree == NULL){
        return;
    }
    addSpace(nivel);
    printf("- label: %s\n", tree->label);
    addSpace(nivel);
    printf("CODE: %s\n", getCode(tree->command));
    addSpace(nivel);
    printf("nivel: %d\n", nivel/3);
    addSpace(nivel);
    if(list_get_size(tree->neighbors) >0){
        printf("arvores %d =>\n", list_get_size(tree->neighbors));
        list_forEach(no, tree->neighbors){
            if(no == NULL){
                continue;
            }
            Tree* t = getValue(no, Tree*);
            showTree(t, nivel+3);
        }
    }


}


void print_code(){
    list_forEach(t, trees_history){
        Tree* tree = getValue(t, Tree*);
        showTree(tree, 0);
         
        free(tree);
        puts("\n\n");
    }
}
/************************** End Code Generator **************************/
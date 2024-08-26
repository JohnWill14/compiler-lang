
#include "Parser.tab.h" /* for token definitions and yylval */
void addSpace(int nivel) {
    for (int i = 0; i < nivel; i++) {
        printf("  ");
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
            return "variavel, funcao...";
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
            return "operador aritmetico";
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
        case CALL_FUNCTION:
            return "chamada de método";
        break;

        default:
            return "não registrado :(";
        break;

               
    }

}

int check_break(int line){
  Tree* it = current_tree;

    while( it!= NULL){
        if(it->command == WHILE) {
          return 0;
        }  

        if(it->command == FUN){
            break;
        }
        it = it->parent;
    }
    printf("Break line %d is not inserted inside a loop\n", line);
    return 1;
}
void showTree(Tree *tree, int nivel) {
    if (tree == NULL) {
        return;
    }

    
    if (nivel == 0) {
        printf("%s\n", tree->label); // Nó raiz
    } else {
        addSpace(nivel);
        if (tree->label == NULL) {
            printf("└── %s: %d\n", getCode(tree->command), nivel); // Nó filho
        } else {
            printf(" └── %s (%s) : %d\n", tree->label, getCode(tree->command), nivel); 
        }
    }

    // Imprime os filhos recursivamente
    if (list_get_size(tree->neighbors) > 0) {
        for (int i = 0; i < list_get_size(tree->neighbors) - 1; i++) {
            Tree *t = getValue(list_getItem(tree->neighbors, i), Tree *);
            showTree(t, nivel + 1);
            addSpace(nivel);
        }
        Tree *t = getValue(list_getItem(tree->neighbors, list_get_size(tree->neighbors) - 1), Tree *);
        showTree(t, nivel + 1);
    }
}

void print_code() {
    list_forEach(t, trees_history) {
        Tree *tree = getValue(t, Tree *);
        showTree(tree, 0); 
        free(tree);
        puts("\n\n");
    }
}
/***************************************************************************
Code Generator
***************************************************************************/

void addSpace(int space){
    for(int i=0;i<space;i++){
        printf(" ");
    }
}

void showTree(Tree* tree, int nivel){
    addSpace(nivel);
    printf("label: %s\n", tree->label);
    addSpace(nivel);
    printf("CODE: %s\n", op_name[tree->command]);
    addSpace(nivel);
    printf("nivel: %d\n", nivel/3);
    addSpace(nivel);
    printf("arvores %d =>\n", list_get_size(tree->neighbors));
    list_forEach(no, tree->neighbors){
         Tree* tree = getValue(no, Tree*);
         showTree(tree, nivel+3);
    }


    free(tree);
}


void print_code(){
    list_forEach(no, trees){
         Tree* tree = getValue(no, Tree*);
         showTree(tree, 0);
    }
}
/************************** End Code Generator **************************/
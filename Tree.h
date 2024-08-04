/***************************************************************************
Stack Machine
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/* OPERATIONS: Internal Representation */
#include "List.h"

enum code_ops { DEF, PRIMITIVE, PARAMETERS, PARAMETER, BLOCK, PRINT_FUN };
char *op_name[] = {"function", "primitivo", "parametros", "unico parametro", "bloco","printf"};
typedef enum code_ops Code;

struct tree{
    char* label;
    Code command;
    List* neighbors;
    struct tree* parent;
};

typedef struct tree Tree;

/* CODE Array */
List* trees;

Tree* current_tree;

Tree*  init_no(char* label, Code command){

  if(trees == NULL){
    trees = list_create();
  }

  Tree* tree_no = alloc(1, Tree, Tree*);

  if(label != NULL){
    tree_no->label = alloc(strlen(label), char, char*);
    strcpy (tree_no->label,label);
  }

  tree_no->command = command;
  tree_no->neighbors  = list_create();
  
  return tree_no;

}

void create_no(char* label, Code command){
  Tree* tree_no = init_no(label, command);
  
  if(current_tree == NULL){
      list_add(trees, tree_no);
      current_tree = tree_no;
  }else{
    list_add(current_tree->neighbors, tree_no);
    
    Tree* old_current_tree = current_tree;
    current_tree = tree_no;
    current_tree->parent = old_current_tree;
    
  }

}

void revert_no(){
    if(current_tree != NULL){
        current_tree = current_tree->parent;
    }
}

void finalize_tree(){
    current_tree = NULL;
}


/*-------------------------------------------------------------------------
Registers
-------------------------------------------------------------------------*/

/*=========================================================================
Fetch Execute Cycle
=========================================================================*/
void generate_code_in_C(){

}

/*************************** End Stack Machine **************************/
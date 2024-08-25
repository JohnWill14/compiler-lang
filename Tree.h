/***************************************************************************
Stack Machine
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/* OPERATIONS: Internal Representation */
#include "List.h"

struct tree{
    char* label;
    int command;
    List* neighbors;
    struct tree* parent;
};

typedef struct tree Tree;

/* CODE Array */
List* trees;
List* trees_history;

Tree* current_tree;

Tree*  init_no(char* label, int command){

  if(trees == NULL){
    trees = list_create();
  }
  if(trees_history == NULL){
    trees_history = list_create();
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

void create_no(char* label, int command){
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
    if(trees != NULL){
      Node* no = list_getItem(trees, 0);
      list_add(trees_history, no->value);
      trees = NULL;
    }
}

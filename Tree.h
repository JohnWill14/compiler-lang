#include "List.h"
#include "Parser.tab.h"

struct tree{
    char* label;
    int command;
    List* neighbors;
    struct tree* parent;
};

typedef struct tree Tree;

List* trees;
List* trees_history;

Tree* current_tree;

List* returnsList;

int nivel_block_current = 0;
char* function_current = NULL;

int constante_current = 0;

Tree*  init_no(char* label, int command){

  if(trees == NULL){
    trees = list_create();
  }

  if(returnsList == NULL){
    returnsList = list_create();
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

  if(command == BLOCK){
    nivel_block_current +=1;
  }

  if(command == VAL){
    constante_current = 1;
  }

  if(command == FUN){
    function_current = (char *) malloc (strlen(label)+1);
    strcpy (function_current,label);
  }

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

    if(BLOCK == current_tree->command){
      nivel_block_current -=1;
    }

    if(current_tree->command == FUN){
      function_current = NULL;
      strcpy (function_current,"");
    }

    if(current_tree->command == VAL){
      constante_current = 0;
    }

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

int check_return();

struct return_info{
  Tree* tree;
  int line;
  int nivel;
  char* function;
};


typedef struct return_info return_info;


void list_add_returnsList(int line){

  return_info *ptr;

  ptr = (return_info *) malloc (sizeof(return_info));

  ptr->tree = current_tree;
  ptr-> line =line;
  ptr->nivel = nivel_block_current;
  ptr->function = (char *) malloc (strlen(function_current)+1);
  strcpy (ptr->function,function_current);

  list_add(returnsList, ptr);
}

int check_return(){
  int ans = 0;
   list_forEach(t, returnsList) {
        return_info* ptr = getValue(t, return_info *);
        Tree *tree = ptr->tree;
       
        symfunc * t = getsymfunc (ptr->function);
        Tree* r = ((Tree*)(list_getItem(tree->neighbors, 0)->value));

        if(r->command == IDENTIFIER){
          symvar * s = getsymVar (r->label, ptr->nivel, ptr->function);
  
          if(s != NULL){
            if(strcmp(s->type, t->return_type)!=0){
              printf("Error type return in %s. line %d\n", ptr->function, ptr->line);
              ans += 1;
            }
          }

        } else if(r->command == TEXT){
            if(strcmp(t->return_type, "String")!=0){
              printf("Error type return in %s. line %d\n", ptr->function, ptr->line);
              ans += 1;
            }
        }else if(r->command == CALL_FUNCTION){
           symfunc* f = getsymfunc(r->label);

            if(f != NULL){
              if(strcmp(f->return_type, t->return_type)!=0){
                 printf("Error type return in %s. line %d\n", ptr->function, ptr->line);
                ans += 1;
              }
            }else{
              ans +=1;
              printf("function not found line %d\n", ptr->line );
            }
        }

       
   }
   return ans;
}

int check_return_f(Tree* tree){
    if(tree == NULL){
        return 0;
    }
    
    if(tree->command == RETURN_TOKEN){
      return 1;
    }
  int found = 0;
    if(list_get_size(tree->neighbors) >0){
        list_forEach(no, tree->neighbors){
            if(no == NULL){
                continue;
            }
            Tree* t = getValue(no, Tree*);
            found += check_return_f(t);
        }
    }

  return found;
}


int check_returns_f(){
    list_forEach(t, trees_history){
        Tree* tree = getValue(t, Tree*);

        symfunc* f = getsymfunc(tree->label);

        if(strcmp(f->return_type, "Void")!=0){
          int v = check_return_f(tree);
          if(v == 0){
            printf("%s not found return\n", f->name);
            return 1;
          }
        }


    }

    return 0;
}
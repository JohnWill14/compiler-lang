#include<stdlib.h>


#define alloc(X,T,R) (R) malloc(X * sizeof (T*));
#define list_forEach(item, list)\
        for(Node* item = list->first; item!=NULL; item = item->next)

#define getValue(item, T) (T) item->value

typedef struct node {
    void* value;
    struct node* next;
} Node;
 
typedef struct list {
    int size;
    Node* first;
    Node* last;
} List;

int list_get_size(List* list){
    return list->size;
}

int list_is_empty(List* list){
    return list->size == 0 ? 1:0;
}

List* list_create() {
    List* list = alloc(1,List,List*);

    list->size = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

void list_add(List* list, void* value) {
    Node* node = alloc(1, Node, Node*);

    node->value = value;
    node->next = NULL;

    if(list->last != NULL){
        list->last->next = node;
    }

    list->last = node;

    if(list_is_empty(list)){
        list->first = node;
    }

    list->size++;
}

void list_clear(List* list) {
    Node* node = list->first;

    while(!list_is_empty(list)){
        Node* node = list->first;
        list->first = node->next;
        free(node);
        list->size -= 1;
    }

}

Node* list_getItem(List* list, int index) {
    Node* node = list->first;
    int cont = 0;
    while(node != NULL && index != cont){
        node = node->next;
        cont++;
    }

    return node;
}

void list_free(List* list) {
    list_clear(list);
    free(list);
}


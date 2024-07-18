#include <lcthw/dbg.h>
#include <lcthw/list.h>
#include <assert.h>

List *List_create(){
    return calloc(1, sizeof(List));
}

void List_destroy(List *list){
    LIST_FOREACH(list, first, next, cur){
        if(cur->prev) {
            free(cur->prev);
        }
    }
    
    free(list->last);
    free(list);
}

void List_clear(List *list){
    int i = 0;
    int size = List_count(list);
    for(i = 0; i < size; i++){
        List_pop(list);
    }
}

void List_clear_destroy(List *list){
    List_clear(list);
    List_destroy(list);
}

//Insere na última posição
void List_push(List *list, void *value){
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);
    assert(value != NULL);
    node->value = value;
    
    if(list->last == NULL){
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

    error:
        return;
}

void *List_pop(List *list){
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value) {
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL){
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev=node;
        list->first = node;
    }

    list->count++;

    error:
        return;
}

void *List_shift(List *list) {
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node) {
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "Node can't be NULL");

    if(node == list->first && node == list->last){
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL");
        list->last->next = NULL;

    } else if(node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

    error:
        return result;
}

//Copia os elementos da lista 2 para lista 1
void List_copy(List *list1, List *list2) {
    List_clear(list1);
    //printf("LISTA DEPOIS DE LIMPAR:\n");
    //List_print(list1);

    if(list2->first != NULL){
        LIST_FOREACH(list2, first, next, cur){
            List_push(list1, cur->value);
        }
    }
    
    //printf("LISTA DEPOIS DA COPIA\n");
    //List_print(list1);
}

//Salva todos elementos da lista 2 na lista 1
void List_join(List *list1, List *list2) {
    LIST_FOREACH(list2, first, next, cur){
        List_push(list1, cur->value);
    }
}

//Parte a lista em determinado ponto e separa em duas listas
void *List_split(List *main, List *list1, List *list2, int index) {
    check(index > 0, "Index precisa ser maior que 0");
    check(index < main->count, "Index não pode ser maior que o tamanho da lista");
    
    ListNode *currentNode;

    //Começa pelo primeiro valor da lista
    currentNode = main->first;

    //Limpa a segunda lista
    List_remove_all(list1);
    List_remove_all(list2);

    int count = 0;
    //Loop para chegar no inicio do split
    for(count = 0; count < index; count++){
        List_push(list1, currentNode->value);
        currentNode = currentNode->next;
    }
    
    //Loop para começar a pegar os valores da primeira lista e inserir na segunda, depois, remove da primeira lista
    while(currentNode != NULL){
        List_push(list2, currentNode->value);
        currentNode = currentNode->next;
    }

    return NULL;
    error:
        return NULL;
}

void List_print(List *list){
        printf("--- Print ---\n");
    LIST_FOREACH(list, first, next, cur){
        printf("%s\n", (char *)cur->value);
    }
}

void List_remove_all(List *list){
    ListNode *nextNode;
    ListNode *currentNode;

    currentNode = list->first;
    
    while(currentNode != NULL){
        nextNode = currentNode->next;
        List_remove(list, currentNode);
        currentNode = nextNode;
    }
}

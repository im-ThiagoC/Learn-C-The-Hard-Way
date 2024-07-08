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
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

void List_clear_destroy(List *list){
    LIST_FOREACH(list, first, next, cur){
        free(cur->value);
        if(cur->prev) {
            free(cur->prev);
        }
    }
}

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

    check(list->first && node == list->last, "List is empty.");
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

//Copia uma lista para outra existente
List *List_copy(List *list1, List *list2) {
    List_clear_destroy(list1);

    LIST_FOREACH(list2, first, next, cur){
        List_push(list1, cur->value);
    }

    return list1;
}

//Salva todos elementos da lista 2 na lista 1
List *List_join(List *list1, List *list2) {
    LIST_FOREACH(list2, first, next, cur){
        List_push(list1, cur->value);
    }

    return list1;
}

//Parte a lista em determinado ponto até outro determinado ponto
List *List_split(List *list, int index) {
    check(index > 0, "Index precisa ser maior que 0");
    check(index > list->count, "Index não pode ser maior que o tamanho da lista");
    List *segundaParte = List_create();

    int count = 0;
    LIST_FOREACH(list, first, next, cur){
        if(count > index){
            List_push(segundaParte, cur->prev->value);
            List_remove(list, cur->prev);
        }
    }

    return segundaParte;
    error:
        return list;
}
#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

//Foward Functions

//Aloca espaço para lista
List *List_create();
//Limpa a lista
void List_destroy(List *list);
//Limpa os valores da lista
void List_clear(List *list);
//Destrói tudo
void List_clear_destroy(List *list);

//Quantidade de Elementos na lista
#define List_count(A) ((A)->count)
//Primeiro elemento da Lista
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
//Último elemento da lista
#define List_last(A)  ((A)->last != NULL ? (A)->last->value : NULL)

//Insere um valor na lista
void List_push(List *list, void *value);

//Retira o último valor da lista
void *List_pop(List *list);

//Adiciona um valor no inicio da lista
void List_unshift(List *list, void *value);

//Remove o primeiro nó da lista
void *List_shift(List *list);

//Remove o nó especificado
void *List_remove(List *list, ListNode *node);

//Itera sobre cada nó da lista
//LIST_FOREACH(list, first, next, cur);
#define LIST_FOREACH(L, S, M, V) \
    ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)

//Copia os elementos da lista 2 para lista 1
void List_copy(List *list1, List *list2);

//Salva todos elementos da lista 2 na lista 1
void List_join(List *list1, List *list2);

//Parte a lista em determinado ponto e separa em duas novas listas
void *List_split(List *main, List *list1, List *list2, int index);

//Imprime todos elementos da lista
void List_print(List *list);

//Remove todos valores de uma lista
void List_remove_all(List *list);

#define max(a, b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a > _b ? _a : _b; })

#define min(a, b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b; })
#endif
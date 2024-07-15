#include <lcthw/dbg.h>
#include <lcthw/list_algos.h>
#include <assert.h>

int List_bubble_sort(List *list, List_compare cmp){

    if(List_count(list) <= 1){
        //*Already Sorted!
        return 0; 
    }

    int sorted = 0;

    do {
        sorted = 0; 
        LIST_FOREACH(list, first, next, cur){
            if(cur->next != NULL){
                if(cmp(cur->value, cur->next->value) > 0){
                // printf("Trocando %s por %s\n", (char *) cur->value, (char *) cur->next->value);
                ListNode_swap(cur, cur->next);
                sorted = 1;
                }
            }
        }
    }
    while(sorted);

    return 0;
}

List *List_merge(List *left, List *right, List_compare cmp){
    //Cria a lista onde o resultado será retornado
    //?Talvez só precise de uma?
    List *result = List_create();

    //Recebe o ponteiro para o valor, pode ser char*, int...
    void *val = NULL;

    //Enquanto houver valores em left e right...
    while (List_count(left) || List_count(right)){

        if (List_count(left) && List_count(right)){
            //Método comparativo entre dois valores
            if (cmp(List_first(left), List_first(right)) <= 0){
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            //Result recebe o menor valor entre o primeiro elemento de left e o primeiro elemento de right
            List_push(result, val);
        } 
        //Se sobrar algum valor em left...
        else if (List_count(left) > 0){
            val = List_shift(left);
            List_push(result, val);
        }
        //Se sobrar algum valor em right...
        else if (List_count(right) > 0){
            val = List_shift(right);
            List_push(result, val);
        }
    }

    return result;
}

List *List_merge_sort(List *list, List_compare cmp){

    //Critério de parada para recursão
    if(List_count(list) <= 1){
        return list;
    }

    //Cria a parte Esquerda e Direita da lista
    List *left = List_create();
    List *right = List_create();

    //Divide a lista main em esquerda e direita, pelo meio
    List_split(list, left, right, (List_count(list)/2));

    //Zed's method
    /*int middle =  List_count(list)/2;
    LIST_FOREACH(list, first, next, cur){
        if(middle > 0) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }

        middle--;
    }*/

    //Faz isso recursivamente até que haja apenas 1 elemento na lista
    List *sort_left = List_merge_sort(left, cmp);
    List *sort_right = List_merge_sort(right, cmp);

    if(sort_left != left){
        List_destroy(left);
    }
    if(sort_right != right){
        List_destroy(right);
    }

    //Chama a função de ordenação
    return List_merge(sort_left, sort_right, cmp);
}

inline void ListNode_swap(ListNode *a, ListNode *b){
    void *temp;
    temp = a->value;
    a->value = b->value;
    b->value = temp;
}

//Insere um elemento no meio de uma Lista Duplamente Encadeada
//Como parâmetro passa a Lista, o Nó anterior ao que será inserido e o valor do novo nó
void *List_insert(List *list, ListNode *node, void *value){
    ListNode *new_node = calloc(1, sizeof(ListNode));
    check_mem(node);
    assert(value != NULL);
    
    //Cria os ponteiros do novo nó
    new_node->prev = node;
    new_node->value = value;
    new_node->next = node->next;

    //Atualiza o ponteiro anterior
    node->next = new_node;

    //Atualiza o próximo ponteiro
    new_node->next->prev = new_node;


    //Aumenta a contagem da lista
    list->count++;

    return NULL;
    
    error:
        return NULL;
}

//Função que insere os elementos de uma lista principal ORDENADAMENTE em uma nova lista.
List *List_inserted_sort(List *list, List_compare cmp){
    List *sorted_List = List_create();
    //Insere ordenadamente os valores da lista inicial na nova lista

    //Para cada elemento da lista principal...
    LIST_FOREACH(list, first, next, cur){
        //Se for o primeiro elemento, apenas insere na primeira posição
        if(sorted_List->first == NULL){
            List_push(sorted_List, cur->value);
        } 
        //Senão, busca pela lista até achar sua posição 
        else {
            //Para cada elemento inserido na nova lista
            LIST_FOREACH(sorted_List, first, next, sorted_Cur){
                if(cmp(sorted_Cur->value, cur->value) >= 0){
                    //Se sim, insere uma posição antes dele
                    List_insert(sorted_List, sorted_Cur->prev, cur->value);
                    //Quebra o looping
                    break;
                }
            }
        }
    }

    //Retorna a nova lista ordenada
    return sorted_List;
}

ListNode *Node_jump(ListNode *node, int jumps){
    int i = 0;

    for(i = 0; i < jumps; i++){
        if(node->next != NULL){
            node = node->next;
        }
    }
    printf("Valor do nó: %s\n", (char *)node->value);
    return node;
}

List *List_bottom_up_merge_sort(List *list, List_compare cmp){
    int size = List_count(list);
    int width = 1;
    int i = 0;

    List *sorted_List = List_create();

    for(width = 1; width < 1; width *= 2){
        for(i = 0; i < size; i = i + 2 * width){
            List_bottom_up_merge(list, i, min(i+width, size), min(i+(2*width), size), sorted_List, cmp);
            printf("%d %d %d %d\n", width, min(i+width, size), min(i+(2*width), size), size);
        }
        
        List_print(sorted_List);
    }

    return sorted_List;
}

void List_bottom_up_merge(List *list, int left, int right, int end, List *sorted_List, List_compare cmp) {
    int i = left;
    int j = right;
    ListNode *leftNode = Node_jump(list->first, left);
    ListNode *rightNode = Node_jump(list->first, right);
    
    while (i < right || j < end) {
        if (i < right && (j >= end || cmp(leftNode->value, rightNode->value) <= 0)) {
            List_push(sorted_List, leftNode->value);
            leftNode = leftNode->next;
            i++;
        } else {
            List_push(sorted_List, rightNode->value);
            rightNode = rightNode->next;
            j++;
        }
    }
}

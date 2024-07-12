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

void ListNode_swap(ListNode *a, ListNode *b){
    void *temp;
    temp = a->value;
    a->value = b->value;
    b->value = temp;
}
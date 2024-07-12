#ifndef lcthw_List_Algos_h
#define lcthw_List_Algos_h

#include <lcthw/list.h>

typedef int (*List_compare) (const void *a, const void *b);

int List_bubble_sort(List *list, List_compare cmp);
void ListNode_swap(ListNode *a, ListNode *b);

List *List_merge(List *left, List *right, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

#endif

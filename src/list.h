#ifndef data_structures_list_h
#define data_structures_list_h

typedef struct ListNode {
  void *value;
  struct ListNode *prev;
  struct ListNode *next;
} ListNode;

typedef struct List {
  int count;
  struct ListNode *first;
  struct ListNode *last;
} List;

typedef void *(*ListNodeIterator)(ListNode *node);

#define list_count(L) ((L)->count)
#define list_first(L) ((L)->first ? (L)->first->value : NULL)
#define list_last(L)  ((L)->last == NULL  ? NULL : (L)->last->value)

List *List_create();
void  list_push(   List *list, void *value);
void *list_pop(    List *list);
void  list_unshift(List *list, void *value);
void *list_shift(  List *list);

List *list_map(    List *list, void *(*f)(ListNode *node));
void  list_each(   List *list, void *(*f)(ListNode *node));
void  list_print(  List *list);
void  list_destroy(List *list);
void  list_clear(  List *list);
void  list_clear_and_destroy(List *list);

#endif

#include <stdlib.h>
#include <debug.h>
#include <list.h>

void *list_node_clear(ListNode *node);
void *list_node_destroy(ListNode *node);
void *list_node_clear_and_destroy(ListNode *node);

List *List_create() {
  List *list = calloc(1, sizeof(List));
  check_mem(list);
  return list;
error:
  return NULL;
}

ListNode *ListNode_create(void *value) {
  ListNode *node = calloc(1, sizeof(ListNode));
  check_mem(node);
  node->value = value;
  return node;
error:
  return NULL;
}

void  list_push(List *list, void *value) {
  check(list, "list in list_push is NULL");

  ListNode *new_node = ListNode_create(value);

  ListNode *current_tail = list->last;
  if (current_tail) {
    current_tail->next = new_node;
    new_node->prev = current_tail;
  } else {
    list->first = new_node;
  }

  list->last = new_node;
  list->count ++;

  return;
error:
  return;
}

void list_unshift(List *list, void *value) {
  check(list,  "list in list_unshift is NULL");

  ListNode *new_node = ListNode_create(value);

  ListNode *current_head = list->first;
  if (current_head) {
    current_head->prev = new_node;
    new_node->next = current_head;
  } else {
    list->last = new_node;
  }

  list->first = new_node;
  list->count ++;

  return;
error:
  return;
}

void *list_pop(List *list) {
  check(list,       "list in list_pop is NULL");
  check(list->last, "list in list_pop in empty");

  void *value = list_last(list);
  ListNode *old_tail = list->last;
  check(old_tail, "list in list_pop has nothing to pop");

  ListNode *new_tail = old_tail->prev;
  if (new_tail) {
    new_tail->next = NULL;   // set penultimate next to null
    list->last = new_tail;   // set last on list to penultimate
  } else {
    // if there is no new tail, it is empty yo!
    list->last = NULL;
    list->first = NULL;
  }

  list->count --;          // decrement list count
  free(old_tail);          // free last node

  return value;
error:
  return NULL;
}

void *list_shift(List *list) {
  check(list,         "list in list_shift is NULL");
  check(list->first,  "list in list_shift in empty");

  void *value = list_first(list);
  ListNode *old_head = list->first;
  check(old_head, "list in list_shift is ");

  ListNode *new_head = old_head->next;
  list->first = new_head;
  if (!new_head) {
    list->last = NULL;
  }

  list->count --;
  free(old_head);

  return value;
error:
  return NULL;
}

List *list_map(List *list, ListNodeIterator f) {
  check(list, "list in list_each is NULL");
  check(list_count(list) > 0, "list size is 0, nothing to iterate");

  ListNode *node;
  List *mapped_values = calloc(1, sizeof(List));
  check_mem(mapped_values);

  for(node = list->first; node != NULL; node = node->next) {
    list_push(mapped_values, f(node));
  }

  return mapped_values;
error:
  return NULL;
}

void list_each(List *list, ListNodeIterator f) {
  check(list, "list in list_each is NULL");
  check(list_count(list) > 0, "list size is 0, nothing to iterate");

  ListNode *node;
  for(node = list->first; node != NULL; node = node->next) {
    f(node);
  }

error:
  return;
}

void list_clear(List *list) {
  list_each(list, list_node_clear);
}

void list_destroy(List *list) {
  check(list, "list in list_destroy is NULL");
  list_each(list, list_node_destroy);
  free(list);
error:
  return;
}

void  list_clear_and_destroy(List *list) {
  check(list, "list in list_clear_and_destroy is NULL");
  list_each(list, list_node_clear_and_destroy);
  free(list);
error:
  return;
}

// -----------------------------
// Helper functions - declared only in this implementation
//
void *list_node_clear(ListNode *node) {
  check(node, "node in list_node_clear is NULL");

  if (node->value) {
    free(node->value);
    node->value = NULL;
  }
error:
  return NULL;
}

void *list_node_destroy(ListNode *node) {
  check(node, "node in list_node_destroy is NULL");
  free(node);
error:
  return NULL;
}

void *list_node_clear_and_destroy(ListNode *node) {
  check(node, "node in list_node_clear_and_destroy is NULL");
  if (node->value) {
    free(node->value);
    node->value = NULL;
  }
  free(node);
error:
  return NULL;
}

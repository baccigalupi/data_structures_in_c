#include <stdlib.h>

#include <debug.h>
#include <array.h>

Array *Array_create() {
  Array *array = calloc(1, sizeof(Array));
  check_mem(array);
  array_max(array) = ARRAY_MAX_DEFAULT;
  array_elements(array) = calloc(array_max(array), sizeof(void *));
  check_mem(array_elements(array));

  return array;
error:
  if (array) {
    free(array);
  }
  return NULL;
}

void array_push(Array *array, void *element) {
  check(array, "array in array_push is NULL");

  if (array_count(array) > array_max(array)) {
    array_expand(array);
  }

  array_element(array, array->count) = element;
  array->count ++;
error:
  return;
}

void *array_pop(Array *array) {
  check(array, "array in array_pop is NULL");
  check(array_count(array) > 0, "array in array_pop is empty");
  void *element = array_last(array);
  array_last(array) = NULL;
  array_count(array) --;
  return element;
error:
  return NULL;
}

void array_clear(Array *array) {
  check(array, "array in array_clear is NULL");
  check(array_count(array) > 0, "array in array_clear is empty");

  array_each(array) {
    free(array_element(array, i));
  }
error:
  return;
}

void array_destroy(Array *array) {
  check(array, "array in array_destroy is NULL");

  free(array);
error:
  return;
}

void array_clear_and_destroy(Array *array) {
  array_clear(array);
  array_destroy(array);
}

int array_new_size(Array *array) {
  check(array, "array in array_clear is NULL");

  int rate;
  int count = array_count(array);
  if (count < 30 ) {
    rate = 10;
  } else if (count < 100) {
    rate = 100;
  } else {
    rate = 1000;
  }

  int new_size = rate;
  while (new_size <= count) {
    new_size += rate;
  }

  return new_size;
error:
  return 10;
}

void array_expand(Array *array) {
  check(array, "array in array_expand is NULL");

  int new_max = array_new_size(array);
  void *elements = realloc(array_elements(array), new_max);
  check_mem(elements);

  // change up attributes on the array
  array_elements(array) = elements;
  array_max(array) =      new_max;
  return;
error:
  return;
}

#include <assert.h>
#include <array.h>

#include "lib/mu_assert.h"

char *test_create_array() {
  Array *array = Array_create();
  mu_assert(array_count(array) == 0, "Array_create did not initialize count");
  mu_assert(array_max(array) == ARRAY_MAX_DEFAULT, "Array_create did not initialize max");

  return NULL;
}

char *test_array_push() {
  Array *array = Array_create();

  char *element_1 = calloc(13, sizeof(int));
  strcat(element_1, "Hello World!");
  char *element_2 = calloc(5, sizeof(int));
  strcat(element_2, "huh?");
  char *element_3 = calloc(8, sizeof(int));
  strcat(element_3, "Goodbye");

  array_push(array, element_1);

  mu_assert(array_count(array) == 1,            "array_push did not increment count");
  mu_assert(array_element(array, 0) == element_1, "array_push did not add element to array");
  mu_assert(array_first(array) == element_1,      "array_first is not working");
  mu_assert(array_last(array) == element_1,       "array_last is not working");

  return NULL;
}

char *test_array_second_push() {
  Array *array = Array_create();

  char *element_1 = calloc(13, sizeof(int));
  strcat(element_1, "Hello World!");
  char *element_2 = calloc(5, sizeof(int));
  strcat(element_2, "huh?");
  char *element_3 = calloc(8, sizeof(int));
  strcat(element_3, "Goodbye");

  array_push(array, element_1);
  array_push(array, element_2);

  mu_assert(array_count(array) == 2,              "array_push did not increment count");
  mu_assert(array_element(array, 1) == element_2, "array_push did not add element to array");
  mu_assert(array_first(array) == element_1,      "array_first is not working");
  mu_assert(array_last(array) == element_2,       "array_last is not working");

  return NULL;
}

char *test_array_additional_push() {
  Array *array = Array_create();

  char *element_1 = calloc(13, sizeof(int));
  strcat(element_1, "Hello World!");
  char *element_2 = calloc(5, sizeof(int));
  strcat(element_2, "huh?");
  char *element_3 = calloc(8, sizeof(int));
  strcat(element_3, "Goodbye");

  array_push(array, element_1);
  array_push(array, element_2);
  array_push(array, element_3);

  mu_assert(array_count(array) == 3,              "array_push did not increment count");
  mu_assert(array_element(array, 1) == element_2, "array_push did not add element to array");
  mu_assert(array_first(array) == element_1,      "array_first is not working");
  mu_assert(array_last(array) == element_3,       "array_last is not working");

  return NULL;
}

char *test_array_pop() {
  Array *array = Array_create();

  char *element_1 = calloc(13, sizeof(int));
  strcat(element_1, "Hello World!");
  char *element_2 = calloc(5, sizeof(int));
  strcat(element_2, "huh?");
  char *element_3 = calloc(8, sizeof(int));
  strcat(element_3, "Goodbye");

  array_push(array, element_1);
  array_push(array, element_2);
  array_push(array, element_3);

  mu_assert(array_pop(array) == element_3, "array_pop did not return last element");
  mu_assert(array_count(array) == 2,       "array_pop did not decrement count");
  mu_assert(array_last(array) == array_element(array, 1), "array_pop did not reset the last");
  mu_assert(array_pop(array) == element_2, "array_pop did not return last element");
  mu_assert(array_count(array) == 1,       "array_pop did not decrement count");
  mu_assert(array_last(array) == array_element(array, 0), "array_pop did not reset the last");
  mu_assert(array_pop(array) == element_1, "array_pop did not return last element");
  mu_assert(array_count(array) == 0,       "array_pop did not decrement count");
  mu_assert(array_last(array) == NULL,     "array_pop did not reset the last");

  mu_assert(array_pop(array) == NULL,      "array_pop could not handle popping when empty");

  return NULL;
}

char *test_array_clear() {
  Array *array = Array_create();

  char *element_1 = calloc(13, sizeof(int));
  strcat(element_1, "Hello World!");
  char *element_2 = calloc(5, sizeof(int));
  strcat(element_2, "huh?");
  char *element_3 = calloc(8, sizeof(int));
  strcat(element_3, "Goodbye");

  array_push(array, element_1);
  array_push(array, element_2);
  array_push(array, element_3);

  array_clear(array);

  return NULL;
}

char *test_array_destroy() {
  Array *array = Array_create();

  char *element_1 = calloc(13, sizeof(int));
  strcat(element_1, "Hello World!");
  char *element_2 = calloc(5, sizeof(int));
  strcat(element_2, "huh?");
  char *element_3 = calloc(8, sizeof(int));
  strcat(element_3, "Goodbye");

  array_push(array, element_1);
  array_push(array, element_2);
  array_push(array, element_3);

  array_destroy(array);

  return NULL;
}

char *test_array_clear_and_destroy() {
  Array *array = Array_create();

  char *element_1 = calloc(13, sizeof(int));
  strcat(element_1, "Hello World!");
  char *element_2 = calloc(5, sizeof(int));
  strcat(element_2, "huh?");
  char *element_3 = calloc(8, sizeof(int));
  strcat(element_3, "Goodbye");

  array_push(array, element_1);
  array_push(array, element_2);
  array_push(array, element_3);

  array_clear_and_destroy(array);

  return NULL;
}

char *test_expansion_number() {
  Array *array = Array_create();

  array_count(array) = 9;
  mu_assert(array_new_size(array) == 10, "array_new_size incorrect for count 9");

  array_count(array) = 10;
  mu_assert(array_new_size(array) == 20, "array_new_size incorrect for count 10");

  array_count(array) = 19;
  mu_assert(array_new_size(array) == 20, "array_new_size incorrect for count 19");

  array_count(array) = 20;
  mu_assert(array_new_size(array) == 30, "array_new_size incorrect for count 10");

  array_count(array) = 29;
  mu_assert(array_new_size(array) == 30, "array_new_size incorrect for count 29");

  array_count(array) = 30;
  mu_assert(array_new_size(array) == 100, "array_new_size incorrect for count 30");

  array_count(array) = 99;
  mu_assert(array_new_size(array) == 100, "array_new_size incorrect for count 99");

  array_count(array) = 100;
  mu_assert(array_new_size(array) == 1000, "array_new_size incorrect for count 100");

  return NULL;
}

char *test_expansion() {
  Array *array = Array_create();

  char *element_1 = calloc(13, sizeof(int));
  strcat(element_1, "Hello World!");

  int i;
  for (i = 0; i <= 10; i++) {
    array_push(array, element_1);
  }
  mu_assert(array_max(array) == 10, "array_max not correct for 10th element");

  i ++;
  // i = 11
  array_push(array, element_1);
  mu_assert(array_max(array) == 20, "array_max not correct for 11th element");

  for (; i <= 30; i++) {
    array_push(array, element_1);
  }
  mu_assert(array_max(array) == 30, "array_max not correct for 29th element");

  i ++;
  // i = 31
  array_push(array, element_1);
  mu_assert(array_max(array) == 100, "array_max not correct for 30th element");

  for (; i <= 100; i++) {
    array_push(array, element_1);
  }
  mu_assert(array_max(array) == 100, "array_max not correct for 99th element");

  i ++;
  // i = 101
  array_push(array, element_1);
  mu_assert(array_max(array) == 1000, "array_max not correct for 100th element");

  for (; i <= 1001; i++) {
    array_push(array, element_1);
  }
  mu_assert(array_max(array) == 2000, "array_max not correct for 1001th element");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_create_array);
  mu_run_test(test_array_push);
  mu_run_test(test_array_second_push);
  mu_run_test(test_array_additional_push);
  mu_run_test(test_array_pop);
  mu_run_test(test_array_clear);
  mu_run_test(test_array_destroy);
  mu_run_test(test_array_clear_and_destroy);
  mu_run_test(test_expansion_number);
  mu_run_test(test_expansion);

  return NULL;
}

RUN_TESTS(all_tests);

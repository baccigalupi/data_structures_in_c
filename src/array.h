#ifndef data_structures_array_h
#define data_structures_array_h

#define ARRAY_MAX_DEFAULT 10

typedef struct Array {
  int count;
  int max;
  void **elements;
} Array;

#define array_count(A)       ((A)->count)
#define array_max(A)         ((A)->max)
#define array_elements(A)    ((A)->elements)
#define array_element(A, I)  ((A)->elements[(I)])
#define array_first(A)       ((A)->elements[0])
#define array_last_index(A)  (A->count == 0 ? 0 : A->count - 1)
#define array_last(A)        ((A)->elements[array_last_index(A)])
#define array_each(A) int i;\
    int max = array_count(A);\
    for(i = 0; i < max; i++)


Array *Array_create();
void   array_push(Array *array, void *element);
void  *array_pop(Array *array);
void   array_clear(Array *array);
void   array_destroy(Array *array);
void   array_clear_and_destroy(Array *array);
int    array_new_size(Array *array);
void   array_expand(Array *array);

#endif

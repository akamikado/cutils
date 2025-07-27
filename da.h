#ifndef DA_H_
#define DA_H_

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*
 * To use the libary, create a dynamic array structure neccessarily consisting
 * of the following members
 * {
 *    T* items,
 *    size_t size,
 *    size_t capacity
 * }
 * */

#define da_reserve(da, needed)                                                 \
  do {                                                                         \
    if ((da)->capacity <= 0)                                                   \
      (da)->capacity = 1;                                                      \
    while ((da)->capacity <= needed)                                           \
      (da)->capacity <<= 1;                                                    \
    (da)->items = realloc((da)->items, (da)->capacity * sizeof(*(da)->items)); \
    assert((da)->items != NULL);                                               \
  } while (0)

// Append single element
#define da_append(da, item)                                                    \
  do {                                                                         \
    da_reserve(da, (da)->size + 1);                                            \
    (da)->items[(da)->size] = item;                                            \
    (da)->size += 1;                                                           \
  } while (0)

// Append array of elements
#define da_append_multiple(da, number_of_items, new_items)                     \
  do {                                                                         \
    da_reserve(da, (da)->size + number_of_items);                              \
    memcpy(&(da)->items[(da)->size], (new_items),                              \
           number_of_items * sizeof(*(da)->items));                            \
    (da)->size += number_of_items;                                             \
  } while (0)

#define da_remove_last(da, n)                                                  \
  do {                                                                         \
    (da)->size -= n;                                                           \
    assert((da)->size >= 0);                                                   \
  } while (0)

#define da_free(da)                                                            \
  do {                                                                         \
    (da)->size = 0;                                                            \
    (da)->capacity = 0;                                                        \
    if ((da)->items != NULL)                                                   \
      free((da)->items);                                                       \
  } while (0)

#endif // DA_H_

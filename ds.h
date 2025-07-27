#ifndef DS_H_
#define DS_H_

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*
 * DYNAMIC ARRAYS
 *
 * To use dynamic array, create a structure consisting of the following members
 * struct DynArray {
 *    T* items;
 *    size_t size;
 *    size_t capacity;
 * };
 */

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

/*
 * LINKED LIST
 *
 * To create a linked list, create a structure consisting of the following
 * members
 * struct LinkedListNode {
 *  struct LinkedListNode* next;
 *  T value;
 * };
 */

#define ll_next(head, it)                                                      \
  do {                                                                         \
    assert(head->next != NULL);                                                \
    it = head->next;                                                           \
  } while (0)

#define ll_insert_start(Type, head, item)                                      \
  do {                                                                         \
    Type *new_node = (Type *)malloc(sizeof(Type));                             \
    new_node->value = item;                                                    \
    new_node->next = (head);                                                   \
    (head) = new_node;                                                         \
  } while (0)

#define ll_insert_end(Type, head, item)                                        \
  do {                                                                         \
    Type *new_node = (Type *)malloc(sizeof(Type));                             \
    new_node->value = item;                                                    \
    new_node->next = NULL;                                                     \
    Type *temp = (head);                                                       \
    while (temp && temp->next) {                                               \
      temp = temp->next;                                                       \
    }                                                                          \
    if (temp) {                                                                \
      temp->next = new_node;                                                   \
    } else {                                                                   \
      temp = new_node;                                                         \
    }                                                                          \
  } while (0)

#define ll_remove_first(Type, head)                                            \
  do {                                                                         \
    assert(head != NULL);                                                      \
    Type *temp = (head);                                                       \
    temp = head->next;                                                         \
    free((head));                                                              \
    (head) = temp;                                                             \
  } while (0)

#define ll_remove_last(Type, head)                                             \
  do {                                                                         \
    assert((head) != NULL);                                                    \
    Type *temp = (head);                                                       \
    while (temp->next)                                                         \
      temp = temp->next;                                                       \
    ll_free(Type, temp);                                                       \
  } while (0)

#define ll_free(Type, head)                                                    \
  do {                                                                         \
    assert((head) != NULL);                                                    \
    while ((head)->next) {                                                     \
      Type *temp = (head);                                                     \
      (head) = (head)->next;                                                   \
      free(temp);                                                              \
    }                                                                          \
  } while (0)

/*
 * STACKS
 *
 * To create a stack, create a structure consisting of the following members
 * struct Stack {
 *  T* items;
 *  size_t size;
 *  size_t capacity;
 * };
 */

#define stk_push(stk, item) da_append(stk, item)
#define stk_top(stk, it) (stk)->items[(stk)->size - 1]
#define stk_pop(stk) da_remove_last(stk)

#endif // DS_H_

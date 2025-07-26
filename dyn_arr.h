#ifndef DYN_ARR_H_
#define DYN_ARR_H_

/*
 * To use the libary, create a dynamic array structure neccessarily consisting
 * of the following members
 * {
 *    T* items,
 *    size_t size,
 *    size_t capacity
 * }
 * */

// Append single element
#define da_append(da, item)                                                    \
  do {                                                                         \
    if ((da)->size >= (da)->capacity) {                                        \
      (da)->items = realloc((da)->items,                                       \
                            2 * (da)->capacity * (sizeof(*(da)->items)) + 1);  \
    }                                                                          \
    (da)->items[size] = item;                                                  \
    size += 1;                                                                 \
  } while (0)

#endif // DYN_ARR_H_

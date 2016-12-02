#ifndef STRDEQUE_H
#define STRDEQUE_H

#ifdef __cplusplus
#include <iostream>
#include <cstddef>

namespace jnp1 {
    extern "C" {

#else

#include <stddef.h>

#endif
/*
 * Create new, empty strdeque and return its identifier.
 */
unsigned long strdeque_new();

/*
 * If dequeue with given id exists, delete it.
 * Otherwise do nothing.
 */
void strdeque_delete(unsigned long id);

/*
 * Return size of deque with given id.
 * If it does not exist, return 0;
 */
size_t strdeque_size(unsigned long id);

/*
 * If deque with given id exists and value != NULL, insert new value
 * before pos position or at the end of deque, if pos is greater than its size.
 */
void strdeque_insert_at(unsigned long id, size_t pos, const char* value);

/*
 * If deque with given id exists and pos is less than its size,
 * delete the element on pos position. Otherwise do nothing.
 */
void strdeque_remove_at(unsigned long id, size_t pos);

/*
 * If deque with given id exists and pos is less than its size,
 * return pointer to element at pos position. Otherwise return NULL
 */
const char* strdeque_get_at(unsigned long id, size_t pos);

/*
 * If deque with given id exists, delete it.
 */
void strdeque_clear(unsigned long id);

/*
 * Compare deques with given ids lexicographically.
 * Return:
 * -1 if dq1 < dq2
 *  0 if dq1 = dq2
 *  1 if dq1 > dq1
 *  Nonexistent deque is treated as empty deque.
 */
int strdeque_comp(unsigned long id1, unsigned long id2);

#ifdef __cplusplus
    };
}
#endif

#endif

#ifndef STRDEQUEUECONST_H
#define STRDEQUEUECONST_H

#ifdef __cplusplus
#include<iostream>

namespace jnp1 {
    extern "C" {
#endif
/*
 * Return identifier of an empty deque, in which you can't add or remove
 * elements.
 */
unsigned long emptystrdeque();

#ifdef __cplusplus
    };
}
#endif

#endif

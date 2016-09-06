/*
 * stack.h 
 *
 * Defines basic operations of a stack.
 */

#ifndef WVM_STACK_H
#define WVM_STACK_H

#include <stdint.h>

void push(uint8_t);
uint8_t pop();
uint8_t empty();
uint8_t full();

#endif

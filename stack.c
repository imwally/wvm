/*
 * stack.c
 *
 * Implements basic stack operations.
 */

#include <stdint.h>
#include "stack.h"

#define MAX_STACK_SIZE 256

int stack[MAX_STACK_SIZE] = {};   // The stack holds no more than 256 elements.
int SP = 0;                       // Stack pointer.

void push(uint8_t data) {
    stack[SP++] = data;
}

uint8_t pop() {
    return stack[--SP];
}

uint8_t empty() {
    return SP == 0;  
}

uint8_t full() {
    return SP+1 == MAX_STACK_SIZE;
}    

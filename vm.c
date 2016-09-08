/*
 * Copyright (c) 2016, Wally Jones <wally@imwally.net>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 256

typedef struct VM {
    uint8_t stack[MAX_STACK_SIZE];  // The stack holds no more than 256 elements.
    uint8_t sp;                     // Stack pointer.
} * machine;

typedef enum {
    HALT,
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV
} isa;

/*
 * According to the instruction set from above the following program should
 * produce something like this:
 *
 * 11 + 10 = 21
 * 5  + 21 = 26
 * print 26
 * 80 - 50 = 30
 * 2  * 30 = 60
 * 120 / 60 = 2
 * print 2
 */
const uint8_t program[] = {
    PUSH, 10,
    PUSH, 11,
    ADD,
    PUSH, 5,
    ADD,
    POP,
    PUSH, 50,
    PUSH, 80,
    SUB,
    PUSH, 2,
    MUL, 
    PUSH, 120,
    DIV,
    POP,
    POP,
    HALT
};

machine init() {
    machine vm = malloc(sizeof(struct VM));
    vm->sp = 0;

    return vm;
}

void halt(machine vm) {
    if(vm) {
        free(vm);
    }
    printf("WVM: halted.\n");
}

uint8_t empty(machine vm) {
    return vm->sp == 0;  
}

uint8_t full(machine vm) {
    return vm->sp+1 == MAX_STACK_SIZE;
}

void push(machine vm, uint8_t data) {
    if (full(vm)) {
        printf("WVM: error: stack overflow.\n");
        halt(vm);
        exit(0);
    }
    vm->stack[(vm->sp)++] = data;
}

uint8_t pop(machine vm) {
    if (empty(vm)) {
        printf("WVM: error: stack underflow.\n");
        halt(vm);
        exit(0);
    }
    return vm->stack[--(vm->sp)];
}

void run(machine vm, const uint8_t program[]) {
    printf("WVM: running...\n");
  
    uint8_t ip = 0; 
    uint8_t instruction = program[ip];
    while (vm) {
        switch(instruction) {
            case HALT:
                halt(vm);
                break;
            case PUSH:
                push(vm, program[++ip]);        // Increment before pushing on to the stack
                break;                          // because ip currently points to "PUSH".
            case POP:
                printf("WVM: %d\n", pop(vm));
                break;
            case ADD:
                push(vm, (pop(vm) + pop(vm)));
                break;
            case SUB:
                push(vm, (pop(vm) - pop(vm)));
                break;
            case MUL:
                push(vm, (pop(vm) * pop(vm)));
                break;
            case DIV:
                push(vm, (pop(vm) / pop(vm)));
                break;
            default:
                return;
        }
        instruction = program[++ip];
    }
}

int main(int argc, char *argv[]) {
    machine vm = init();
    run(vm, program);
}

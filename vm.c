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
    HALT
};

void push(machine vm, uint8_t data) {
    vm->stack[(vm->sp)++] = data;
}

uint8_t pop(machine vm) {
    return vm->stack[--(vm->sp)];
}

uint8_t empty(machine vm) {
    return vm->sp == 0;  
}

uint8_t full(machine vm) {
    return vm->sp+1 == MAX_STACK_SIZE;
}

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

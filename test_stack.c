#include <stdint.h>
#include <stdio.h>
#include "stack.h"

int main(int argc, char *argv[]) {
    uint8_t counter = 0;

    while (!full()) {
        push(counter++);
    }  

    while (!empty()) {
        printf("%d popped off the stack.\n", pop());
    }

    return 0;
}

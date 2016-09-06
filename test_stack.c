#include <stdint.h>
#include <stdio.h>
#include "stack.h"

int main(int argc, char *argv[]) {
    int8_t my_data = 5;
    int8_t counter = 0;
    for (counter = 1; counter < 10; counter++) {
        push(counter);
    }  

    while (counter > 1) {
        printf("%d popped off the stack.\n", pop());
        counter--;
    }

    return 0;
}

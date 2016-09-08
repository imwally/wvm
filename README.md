Wally's Virtual Machine
=======================

This is my attempt at writing a *very* simple stack based virtual machine, or
if you will, a [stack machine](https://en.wikipedia.org/wiki/Stack_machine). It
works on a single stack with a limited set of instructions.

Instruction Set
---------------
```
opcode  |   value   | description
---------------------------------------------------------------------------------
HALT    |   0       | stop the machine
PUSH    |   1       | push operand on to the stack
POP     |   2       | pop operand off the stack and print value
ADD     |   3       | pop top 2 operands, add them, push sum back onto the stack
SUB     |   4       | pop top 2 operands, subtract them, push difference onto the stack
MUL     |   5       | pop top 2 operands, multiply them, push products onto the stack
DIV     |   6       | pop top 2 operands, divide them, push quotient onto the stack
```

Given the above instruction set you can produce a program with the following code:

```
PUSH 10 
PUSH 11
ADD         ; 11 + 10, Push 21 onto the stack
PUSH 5
ADD         ; 5 + 21, Push 26 onto the stack 
POP         ; Print 26
PUSH 50
PUSH 80
SUB         ; 80 - 50, Push 30 onto the stack 
PUSH 2
MUL         ; 2 * 30, Push 60 onto the stack
PUSH 120
DIV         ; 120 / 60, Push 2 onto the stack
POP         ; Print 2
HALT        ; Stop the machine
```

This is the same program that's baked into this machine so if you would like to
try it yourself you can clone this repository and follow the installation
instructions below.

Installation
------------
```
$ git clone https://github.com/imwally/wvm.git
$ make
```

Run
---
`$ ./vm`

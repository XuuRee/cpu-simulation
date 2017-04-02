#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*
 * i) Ma byt alokovano int, nebo int_32t
 */
void stackInit(struct stack* stack)
{
    stack->values = (int *)calloc(512, sizeof(int));    // = (int *)malloc(2048); int nebo int32_t?
    assert(stack->values != NULL);
    stack->top = NULL;
}


void stackClear(struct stack* stack)
{
    free(stack->values);
    stack->values = NULL;
    stack->top = NULL;
}


int isEmpty(struct stack* stack)
{
    if (!stack->top) {
        return 1;
    }

    return 0;
}


void stackPush(struct stack* stack, int32_t cpu_register)
{
    assert(stack->values != NULL);

    int *start = stack->values;

    while (*start != 0) {
        start++;
    }

    *start = cpu_register;
    stack->top = start;
}


void stackPop(struct stack* stack)
{
    if (isEmpty(stack)) {
        return;
    }

    if (stack->top == stack->values) {
        *(stack->top) = 0;
        stack->top = NULL;
    } else {
        *(stack->top) = 0;
        stack->top--;
    }
}


void cpuInit (struct cpu* cpu) {}
void cpuClear (struct cpu* cpu) {}
void cpuStep(struct cpu* cpu) {}
void cpuDebug(const struct cpu* cpu) {}

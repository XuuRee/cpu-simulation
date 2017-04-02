#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void stackInit(struct stack* stack)
{
    stack->values = (int *)calloc(512, sizeof(int));    // = (int *)malloc(2048); int nebo int32_t?
    assert(stack->values != NULL);
    stack->top = NULL;
}


void stackClear(struct stack* stack)
{
    free(stack->values);                // pole, promazat kazdou hodnotu?
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

    /*
    if (stack->top) {
        stack->values = stack->top;
        *(stack->values) = cpu_register;
        stack->values++;
    } else {
    */
        *(stack->values) = cpu_register;
        stack->top = stack->values;
        stack->values++;
    //}

    assert(stack->top != NULL);
}


void stackPop(struct stack* stack)
{
    if (isEmpty(stack)) {
        return;
    }

    *(stack->top) = 0;
    stack->top--;   //musim si pohlidat stack overflow, muzu se posunout na misto pod indexem 0
}


void cpuInit (struct cpu* cpu) {}
void cpuClear (struct cpu* cpu) {}
void cpuStep(struct cpu* cpu) {}
void cpuDebug(const struct cpu* cpu) {}

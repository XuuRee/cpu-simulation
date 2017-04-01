#include "cpu.h"
#include <stdlib.h>
#include <assert.h>

void stackInit(struct stack* stack)
{
    stack->values = (int *)malloc(2048);
    assert(stack->values != NULL);
    stack->top = NULL;
}


void stackClear(struct stack* stack)
{
    free(stack->values);
    stack->values = NULL;
    stack->top = NULL;
}


void stackPush(struct stack* stack, int cpu_register)
{

}


void stackPop(struct stack* stack)
{

}


void cpuInit (struct cpu* cpu) {}
void cpuClear (struct cpu* cpu) {}
void cpuStep(struct cpu* cpu) {}
void cpuDebug(const struct cpu* cpu) {}

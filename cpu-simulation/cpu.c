#include "cpu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void stackInit(struct stack *stack)
{
    stack->values = calloc(512, sizeof(int32_t));
    assert(stack->values != NULL);
    stack->top = NULL;
}

void stackClear(struct stack *stack)
{
    free(stack->values);
    stack->values = NULL;
    stack->top = NULL;
}

int isEmpty(const struct stack *stack)
{
    if (!stack->top) {
        return 1;
    }

    return 0;
}

void stackPrint(const struct stack *stack)
{
    if (isEmpty(stack)) {
        fprintf(stdout, "\n");
        return;
    }

    int32_t *start = stack->values;

    while (start != stack->top) {
        fprintf(stdout, " %d", *start);
        start++;
    }

    fprintf(stdout, " %d\n", *(stack->top));
}

void stackPush(struct stack *stack, int32_t cpu_register)
{
    assert(stack != NULL);
    assert(stack->values != NULL);

    if (isEmpty(stack)) {
        stack->top = stack->values;
    } else {
        stack->top++;
    }

    *(stack->top) = cpu_register;
}

void stackPop(struct stack *stack)
{
    assert(stack != NULL);
    assert(stack->values != NULL);

    if (isEmpty(stack)) {
        return;
    }

    *(stack->top) = 0;

    if (stack->top == stack->values) {
        stack->top = NULL;
    } else {
        stack->top--;
    }
}

void cpuInit(struct cpu *cpu)
{
    memset(cpu->registers, 0, sizeof(cpu->registers));
    listInit(&cpu->programList);
    stackInit(&cpu->memory);
}

void cpuClear(struct cpu *cpu)
{
    memset(cpu->registers, 0, sizeof(cpu->registers));
    listClear(&cpu->programList);
    stackClear(&cpu->memory);
}

int cpuStep(struct cpu *cpu)
{
    const struct instruction *instruction = listStep(&cpu->programList);
    assert(instruction != NULL);
    int32_t tmp = 0;

    switch (instruction->type) {
    case InstNop:
        return 1;

    case InstAdd:
        cpu->registers[0] += cpu->registers[2];
        return 1;

    case InstSub:
        cpu->registers[0] -= cpu->registers[2];
        return 1;

    case InstMul:
        cpu->registers[0] *= cpu->registers[2];
        return 1;

    case InstDiv:
        cpu->registers[0] /= cpu->registers[2];
        return 1;

    case InstMova:
        cpu->registers[0] = instruction->arg;
        return 1;

    case InstLoad:
        cpu->registers[0] = *((cpu->memory).top - cpu->registers[1]);
        return 1;

    case InstSwac:
        tmp = cpu->registers[0];
        cpu->registers[0] = cpu->registers[2];
        cpu->registers[2] = tmp;
        return 1;

    case InstSwab:
        tmp = cpu->registers[0];
        cpu->registers[0] = cpu->registers[1];
        cpu->registers[1] = tmp;
        return 1;

    case InstInc:
        cpu->registers[0] += 1;
        return 1;

    case InstDec:
        cpu->registers[0] -= 1;
        return 1;

    case InstPush:
        stackPush(&cpu->memory, cpu->registers[0]);
        return 1;

    case InstPop:
        stackPop(&cpu->memory);
        return 1;

    default:
        return 0;
    }
}

void cpuDebug(const struct cpu *cpu)
{
    fprintf(stdout, "# Registers %d %d %d | Stack", (cpu->registers)[0], (cpu->registers)[1], (cpu->registers)[2]);
    stackPrint(&cpu->memory);
}

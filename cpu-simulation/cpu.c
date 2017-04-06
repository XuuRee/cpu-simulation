#include "cpu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


void stackInit(struct stack* stack)
{
    stack->values = calloc(512, sizeof(int32_t));
    assert(stack->values != NULL);
    stack->top = NULL;
}


void stackClear(struct stack* stack)
{
    free(stack->values);
    stack->values = NULL;
    stack->top = NULL;
}


void stackPrint(const struct stack* stack)
{
    if (stack->top != NULL) {
        unsigned int i = 0;

        while(&(stack->values)[i] != stack->top) {
            fprintf(stdout, " %d", (stack->values)[i]);    //%zu
            i++;
        }
        //if (i != 0) {
            fprintf(stdout, " %d\n", *(stack->top));        //\n
        //}

    } else {
        fprintf(stdout, "\n");
    }
}


int isEmpty(struct stack* stack)
{
    if (!stack->top) {
        return 1;
    }

    return 0;
}


/*
 * Stack smash - kontrola horni hranice alokovane pameti;
 */
void stackPush(struct stack* stack, int32_t cpu_register)
{
    assert(stack->values != NULL);

    int32_t *start = stack->values;

    while (*start != 0) {   // musi byt neco jineho, je mozne ze na stack budu potrebovat ulozit 0 !
        start++;
    }

    *start = cpu_register;
    stack->top = start;
}


void stackPop(struct stack* stack)
{
    assert(stack->values != NULL);

    if (isEmpty(stack)) {
        return;
    }

    *(stack->top) = 0;

    if (stack->top == stack->values) {
        stack->top = NULL;
        return;
    }

    stack->top--;
}


void cpuInit(struct cpu* cpu)
{
    //memset(cpu->registers, 0, sizeof(cpu->registers));   // memset
    cpu->registers[0] = 0;
    cpu->registers[1] = 0;
    cpu->registers[2] = 0;
    listInit(&cpu->programList);
    stackInit(&cpu->memory);
}


void cpuClear(struct cpu* cpu)
{
    //memset(cpu->registers, 0, sizeof(cpu->registers));  // memset
    cpu->registers[0] = 0;
    cpu->registers[1] = 0;
    cpu->registers[2] = 0;
    listClear(&cpu->programList);
    stackClear(&cpu->memory);
}


void cpuStep(struct cpu* cpu)
{
    const struct instruction *instruction = listStep(&cpu->programList);
    assert(instruction != NULL);
    int32_t tmp = 0;

    switch (instruction->type) {
        case InstNop:
            return;

        case InstAdd:
            cpu->registers[0] += cpu->registers[2];
            return;

        case InstSub:
            cpu->registers[0] -= cpu->registers[2];
            return;

        case InstMul:
            cpu->registers[0] *= cpu->registers[2];
            return;

        case InstDiv:
            cpu->registers[0] /= cpu->registers[2];
            return;

        case InstMova:
            cpu->registers[0] = instruction->arg;
            return;

        case InstLoad:
            cpu->registers[0] = *((cpu->memory).top) - cpu->registers[1];
            return;

        case InstSwac:
            tmp = cpu->registers[0];
            cpu->registers[0] = cpu->registers[2];
            cpu->registers[2] = tmp;
            return;

        case InstSwab:
            tmp = cpu->registers[0];
            cpu->registers[0] = cpu->registers[1];
            cpu->registers[1] = tmp;
            return;

        case InstInc:
            cpu->registers[0] += 1;
            return;

        case InstDec:
            cpu->registers[0] -= 1;
            return;

        case InstPush:
            stackPush(&cpu->memory, cpu->registers[0]);
            return;

        case InstPop:
            stackPop(&cpu->memory);
            return;

        default:
            return;
   }

}


void cpuDebug(const struct cpu* cpu)
{
    // na vypsani int32_t potrebuji prst %zu,
    fprintf(stdout, "# Registers %d %d %d | Stack", (cpu->registers)[0], (cpu->registers)[1], (cpu->registers)[2]);
    stackPrint(&cpu->memory);
}

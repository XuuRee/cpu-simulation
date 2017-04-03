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

        fprintf(stdout, " %d\n", *(stack->top));        //\n
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
    struct stack *memory;
    memory = &cpu->memory;

    struct instructionList *list;
    list = &cpu->programList;       // dont have to use it that way

    memset(cpu->registers, 0, 3);   // memset

    list = malloc(sizeof list);     // or *list?
    assert(list != NULL);
    listInit(list);

    memory = malloc(sizeof *memory);
    assert(memory != NULL);
    stackInit(memory);
}


void cpuClear(struct cpu* cpu)
{
    memset(cpu->registers, 0, 3);

    listClear(&cpu->programList);
    free(&cpu->programList);

    stackClear(&cpu->memory);
    free(&cpu->memory);
}


void cpuStep(struct cpu* cpu)
{

}


void cpuDebug(const struct cpu* cpu)
{
    // na vypsani int32_t potrebuji prst %zu,
    fprintf(stdout, "# Registers %d %d %d | Stack", (cpu->registers)[0], (cpu->registers)[1], (cpu->registers)[2]);
    stackPrint(&cpu->memory);
}

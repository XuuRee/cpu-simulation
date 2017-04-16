#include "instruction_list.h"
#include <stdint.h>

struct stack
{
    int32_t *values;
    int32_t *top;
};

void stackInit(struct stack *stack);
void stackClear(struct stack *stack);
void stackPush(struct stack *stack, int32_t cpu_register);
void stackPop(struct stack *stack);

struct cpu
{
    int32_t registers[3];
    struct instructionList programList;
    struct stack memory;
};

void cpuInit(struct cpu *cpu);
void cpuClear(struct cpu *cpu);
int cpuStep(struct cpu *cpu);
void cpuDebug(const struct cpu *cpu);

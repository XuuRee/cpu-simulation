#include "cpu.h"

void stackInit(struct stack* stack) {}
void stackClear(struct stack* stack) {}
void stackPush(struct stack* stack, int cpu_register) {}
void stackPop(struct stack* stack) {}

void cpuInit (struct cpu* cpu) {}
void cpuClear (struct cpu* cpu) {}
void cpuStep(struct cpu* cpu) {}
void cpuDebug(const struct cpu* cpu) {}
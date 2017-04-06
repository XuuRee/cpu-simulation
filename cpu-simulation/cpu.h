/*
   Hlavickovy soubor pro funkce s prefixem stack* a cpu*,
   mimo deklarace techto zde i definujte struktury stack a cpu.
   Includujte prave a pouze hlavickove soubory primo potrebne touto hlavickou.
 */

#include "instruction_list.h"
#include <stdint.h>

struct stack {
    int32_t* values;    // int values
    int32_t* top;
};

void stackInit(struct stack* stack);
void stackClear(struct stack* stack);
void stackPrint(const struct stack* stack);   // nesmi to byt, pouze pro testovaci ucely! printStack primo do cpuDebug
void stackPush(struct stack* stack, int32_t cpu_register);
void stackPop(struct stack* stack);

struct cpu {
    int32_t registers[3];                   // alocate?
    struct instructionList programList;    // not pointers
    struct stack memory;
};

void cpuInit(struct cpu* cpu);
void cpuClear(struct cpu* cpu);
void cpuStep(struct cpu* cpu);
void cpuDebug(const struct cpu* cpu);

#include "instruction_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

void listInit(struct instructionList* container) {
    assert(container != NULL);
    container->current = NULL;
    container->end = NULL;
}


const char *getInstruction(enum instructionType instruction) {
    switch (instruction) {
        case InstNop: return "InstNop";
        case InstAdd: return "InstAdd";
        case InstSub: return "InstSub";
        case InstMul: return "InstMul";
        case InstDiv: return "InstDiv";
        case InstMova: return "InstMova";
        case InstLoad: return "InstLoad";
        case InstSwac: return "InstSwac";
        case InstSwab: return "InstSwab";
        case InstInc: return "InstInc";
        case InstDec: return "InstDec";
        case InstPush: return "InstPush";
        case InstPop: return "InstPop";
        default: return "Unknown value";
   }
}


void printList(struct instructionList* container) {
    struct instruction *current = container->current;

    while (current != NULL) {
        printf("%s\n", getInstruction(current->type));
        current = current->next;
    }
}


unsigned int listInitToClear(struct instructionList* container)
{
    unsigned int steps = 0;

    if (!container->current && !container->end) {
        return steps;
    }

    while (container->current->prev != NULL) {
        listBackstep(container);
        steps++;
    }

    return steps;
}


unsigned int listClear(struct instructionList* container)
{
    unsigned lengthToRemove = listInitToClear(container);
    bool turnNull = false;

    if (lengthToRemove != 0) {
        turnNull = true;
    }

    struct instruction *current = container->current;
    struct instruction *next = NULL;

    unsigned int lengthList = 0;

    while (current != NULL && lengthToRemove > 0) {
        next = current->next;
        free(current);
        current = next;
        lengthList++;
        lengthToRemove--;
    }

    if (!turnNull) {
        container->current = NULL;
        container->end = NULL;
    } else {
        container->current = current;
        container->current->prev = NULL;
    }

    return lengthList;
}


void listPush(struct instructionList* container, struct instruction* item)
{
    if (!container->current) {
        item->next = NULL;
        item->prev = NULL;
        container->current = item;
        container->end = item;
    } else {
        item->next = NULL;
        item->prev = container->end;
        container->end->next = item;
        container->end = item;
    }
}


const struct instruction *listStep(struct instructionList* container)
{
    if (listEmpty(container)) {
        return NULL;
    }

    if (!container->current->next) {
        return container->current;
    }

    container->current = container->current->next;
    return container->current->prev;
}


const struct instruction *listBackstep(struct instructionList* container)
{
    if (listEmpty(container)) {
        return NULL;
    }

    if(!container->current->prev) {
        return container->current;
    }

    container->current = container->current->prev;
    return container->current->next;
}


unsigned int listEmpty(const struct instructionList* container)
{
    return (!container->current) ? 1 : 0;
}

#include "instruction_list.h"
#include <stdlib.h>
#include <assert.h>

void listInit(struct instructionList* container) {
    assert(container != NULL);
    container->current = NULL;
    container->end = NULL;
}


const char* getInstruction(enum instructionType instruction) {
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


unsigned int listClear(struct instructionList* container) {
    struct instruction *current = container->current;
    struct instruction *next = NULL;
    unsigned int lengthList = 0;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
        lengthList++;
    }

    container->current = NULL;
    container->end = NULL;

    return lengthList;
}


void listPush(struct instructionList* container, struct instruction* item)
{
    if (!container->current) {
        container->current = item;
        container->end = item;
        item->next = NULL;
        item->prev = NULL;
    } else {
        container->end->next = item;
        item->next = NULL;
        item->prev = container->end;
        container->end = item;
    }
}


const struct instruction * listStep(struct instructionList* container)
{
    if (listEmpty(container)) {
        return NULL;
    }

    container->current = container->current->next;
    return container->current->prev;
}


const struct instruction * listBackstep(struct instructionList* container)
{
    if (listEmpty(container)) {
        return NULL;
    }

    container->current = container->current->prev;
    return container->current->next;
}


unsigned int listEmpty(const struct instructionList* container)
{
    return (!container->current) ? 1 : 0;
}

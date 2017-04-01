#include "instruction_list.h"
#include <stdlib.h>

/*
 * Inicializovat vsechny ostatni argumenty na NULL nebo 0 ?
 */
void listInit(struct instructionList* container) {
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
    struct instruction *currentNode = container->current;

    while (currentNode != NULL) {
        printf("%s\n", getInstruction(currentNode->type));
        currentNode = currentNode->next;
    }
}


/*
 * i) lengthList, jako pocitat se zarazkou? +- 1 ?
 * ii) musi opravdu byt container->end, current ukazovat ke konci na NULL ?
 */
unsigned int listClear(struct instructionList* container) {
    struct instruction *currentNode = container->current;
    struct instruction *nextNode;
    unsigned int lengthList = 0;

    while (currentNode->next != NULL) {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
        lengthList++;
    }

    free(currentNode);
    container->current = NULL;
    container->end = NULL;

    return lengthList + 1;
}


/*
 * Musi byt item->next a item->prev nastaven na NULL
 */
void listPush(struct instructionList* container, struct instruction* item) {
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


const struct instruction * listStep(struct instructionList* container) {
    if (listEmpty(container)) {
        return NULL;
    }

    container->current = container->current->next;

    return container->current->prev;
}


const struct instruction * listBackstep(struct instructionList* container) {
    if (listEmpty(container)) {
        return NULL;
    }

    container->current = container->current->prev;

    return container->current->next;
}


int listEmpty(const struct instructionList* container) {
    if (!container->current && !container->end) {
        return 1;
    }

    return 0;
}

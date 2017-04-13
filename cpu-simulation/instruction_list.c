#include "instruction_list.h"
#include <stdlib.h>
#include <assert.h>

void listInit(struct instructionList *container)
{
    assert(container != NULL);

    struct instruction *instruction = malloc(sizeof *instruction);
    assert(instruction != NULL);

    instruction->arg = 0;
    instruction->type = InstNop;
    instruction->next = NULL;
    instruction->prev = NULL;

    container->current = instruction;
    container->end = instruction;
}

unsigned int listClear(struct instructionList *container)
{
    assert(container != NULL);
    assert(container->end != NULL);
    assert(container->current != NULL);

    while(listBackstep(container));

    struct instruction *next = NULL;
    struct instruction *current = container->current;

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

void listPush(struct instructionList *container, struct instruction *item)
{
    assert(item != NULL);
    assert(container != NULL);
    assert(container->end != NULL);
    assert(container->current != NULL);

    if (listEmpty(container)) {
        item->prev = NULL;
        item->next = container->end;
        container->current = item;
        container->end->prev = item;
    } else {
        item->next = container->end;
        item->prev = container->end->prev;
        container->end->prev->next = item;
        container->end->prev = item;
    }
}

const struct instruction *listStep(struct instructionList *container)
{
    assert(container != NULL);
    assert(container->end != NULL);
    assert(container->current != NULL);

    if (listEmpty(container)) {
        return NULL;
    }

    if (!container->current->next) {
        return NULL;
    }

    container->current = container->current->next;
    return container->current->prev;
}

const struct instruction *listBackstep(struct instructionList *container)
{
    assert(container != NULL);
    assert(container->end != NULL);
    assert(container->current != NULL);

    if (listEmpty(container)) {
        return NULL;
    }

    if (!container->current->prev) {
        return NULL;
    }

    container->current = container->current->prev;
    return container->current->next;
}

int listEmpty(const struct instructionList *container)
{
    assert(container != NULL);
    assert(container->end != NULL);
    assert(container->current != NULL);

    struct instruction *terminator = container->current;

    if (terminator->type == InstNop) {
        if (!terminator->next && !terminator->prev) {
            return 1;
        }
    }

    return 0;
}

#include "instruction_list.h"
//#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    /* =================================================================

    printf("Program is starting now...\n");

    struct stack *memory;

    memory = malloc(sizeof *memory);

    if (!memory) {
        printf("Nepodarilo se alokovat pamet!\n");
        return 1;
    }

    stackInit(memory);

    stackPrint(memory);

    stackPush(memory, 32);
    stackPush(memory, 5);
    stackPush(memory, 17);
    stackPush(memory, 8);

    stackPrint(memory);

    stackPop(memory);
    stackPop(memory);
    stackPop(memory);
    stackPop(memory);

    stackClear(memory);
    free(memory);

    ================================================================= */

    struct instructionList *list;
    struct instruction *firstInstr;
    struct instruction *secondInstr;

    list = malloc(sizeof *list);          // (instructionsList *)malloc() or sizeof(* list)

    if (!list) {
        printf("Nepodarilo se alokovat pamet!\n");
        return 1;
    }

    firstInstr = malloc(sizeof(firstInstr));

    if (!firstInstr) {
        printf("Nepodarilo se alokovat pamet!\n");
        return 1;
    }

    secondInstr = malloc(sizeof(secondInstr));

    if (!secondInstr) {
        printf("Nepodarilo se alokovat pamet!\n");
        return 1;
    }

    firstInstr->arg = 1;
    firstInstr->type = InstAdd;
    firstInstr->next = NULL;
    firstInstr->prev = NULL;

    secondInstr->arg = 1;
    secondInstr->type = InstSub;
    secondInstr->next = NULL;
    secondInstr->prev = NULL;

    listInit(list);
    printf("Is Empty: %d\n", listEmpty(list));
    listPush(list, firstInstr);
    listPush(list, secondInstr);
    printList(list);        // implicit declaration of printList ! warning
    printf("Is Empty: %d\n", listEmpty(list));
    printf("Delete items: %d\n", listClear(list));
    free(list);

	return 0;
}

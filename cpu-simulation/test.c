#define TESTING
#define TESTING_MAIN

#include "testing.h"
#include "cpu.h"
#include <assert.h>

TEST(basic_run) {
	struct cpu cpu;
	cpuInit(&cpu);
	cpuDebug(&cpu);
    ASSERT_FILE(stdout, "# Registers 0 0 0 | Stack\n");
	cpuClear(&cpu);
}

TEST(list_back_step) {
    struct instructionList *list;

    struct instruction *firstInstr;
    struct instruction *secondInstr;
    const struct instruction *resultInstr;

    list = malloc(sizeof *list);
    assert(list != NULL);

    firstInstr = malloc(sizeof(firstInstr));
    assert(firstInstr != NULL);

    secondInstr = malloc(sizeof(secondInstr));
    assert(secondInstr != NULL);

    firstInstr->arg = 1;
    firstInstr->type = InstAdd;
    firstInstr->next = NULL;
    firstInstr->prev = NULL;

    secondInstr->arg = 1;
    secondInstr->type = InstSub;
    secondInstr->next = NULL;
    secondInstr->prev = NULL;

    listInit(list);
    assert(listEmpty(list) == 1);
    assert(listBackstep(list) == NULL);
    listPush(list, firstInstr);
    listPush(list, secondInstr);
    listStep(list);
    resultInstr = listBackstep(list);
    assert(resultInstr == secondInstr);
    resultInstr = listBackstep(list);
    assert(resultInstr == NULL);
    resultInstr = listBackstep(list);
    assert(resultInstr == NULL);
    assert(listEmpty(list) == 0);
    listClear(list);
    free(list);
}

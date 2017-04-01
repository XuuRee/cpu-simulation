#include <stdio.h>

enum instructionType {
    InstNop,
    InstAdd,
    InstSub,
    InstMul,
    InstDiv,
    InstMova,
    InstLoad,
    InstSwac,
    InstSwab,
    InstInc,
    InstDec,
    InstPush,
    InstPop
};

struct instruction {
	struct instruction *prev, *next; 
	enum instructionType type;
	int arg;
};

struct instructionList {
	struct instruction *end, *current;
};

void listInit(struct instructionList* container);
unsigned int listClear(struct instructionList* container);
void listPush(struct instructionList* container, struct instruction* item);
const struct instruction * listStep(struct instructionList* container);
const struct instruction * listBackstep(struct instructionList* container);
unsigned int listEmpty(const struct instructionList* container);

#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


unsigned int listLength(struct instructionList *container)
{
    unsigned int length = 0;
    struct instruction *start = container->current;

    while (start != NULL) {
        length++;
        start = start->next;
    }

    return length;
}


int getInstructionStdin(const char* instruction) {
    if (strcmp(instruction, "nop\n") == 0) {
        return 1;
    } else if (strcmp(instruction, "add\n") == 0) {
        return 2;
    } else if (strcmp(instruction, "sub\n") == 0) {
        return 3;
    } else if (strcmp(instruction, "mul\n") == 0) {
        return 4;
    } else if (strcmp(instruction, "div\n") == 0) {
        return 5;
    } else if (strcmp(instruction, "mova") == 0) {
        return 6;
    } else if (strcmp(instruction, "load\n") == 0) {
        return 7;
    } else if (strcmp(instruction, "swac\n") == 0) {
        return 8;
    } else if (strcmp(instruction, "swab\n") == 0) {
        return 9;
    } else if (strcmp(instruction, "inc\n") == 0) {
        return 10;
    } else if (strcmp(instruction, "dec\n") == 0) {
        return 11;
    } else if (strcmp(instruction, "push\n") == 0) {
        return 12;
    } else if (strcmp(instruction, "pop\n") == 0) {
        return 13;
    } else {
        return 0;
    }
}


bool saveInstructions(struct cpu *unit)
{
    char buffer[32];
    char *instruction, *argument;

    do {
        fprintf(stdout, "> ");

        struct instruction *instr = malloc(sizeof *instr);
        assert(instr != NULL);

        fgets(buffer, 32, stdin);
        assert(buffer != NULL);

        instruction = strtok(buffer, " ");

        if (strcmp(instruction, "halt\n") == 0) {
            free(instr);
            return false;
        }

        if (strcmp(instruction, "run\n") == 0) {
            free(instr);
            return true;
        }

        int instrEnum = getInstructionStdin(instruction);

        if (!instrEnum) {
            free(instr);
        } else {
            if (strcmp(instruction, "mova") == 0) {
                argument = strtok(NULL, " ");
                instr->arg = atoi(argument);
            } else {
                instr->arg = 0;
            }
            instr->type = instrEnum - 1;
            listPush(&unit->programList, instr);
        }
    } while(true);
}


int main(int argc, char *argv[])
{
    struct cpu *unit;

    unit = malloc(sizeof *unit);
    assert(unit != NULL);

    cpuInit(unit);

    if (argc < 2 || argc > 3) {
        cpuClear(unit);
        free(unit);
        fprintf(stderr, "ERROR: Wrong number of arguments in main function!\n");
        return 1;
    } else {
        if (strcmp(argv[1], "-h") == 0) {
            fprintf(stdout, "\n-h\t\tprogram vypise informace o programu a jeho prepinacich, nasledne se ukonci\n");
            fprintf(stdout, "-r <number>\tpo zavolani prikazu run program vyhodnoti nejvyse <number> instrukci\n");
            fprintf(stdout, "-R\t\tpo zavolani prikazu run program vyhodnocuje instrukce ve fronte tak dlouho, dokud nenarazi na konec seznamu instrukci\n\n");
        }

        if (strcmp(argv[1], "-r") == 0) {
            while(saveInstructions(unit)) {
                unsigned int iterations = atoi(argv[2]);
                unsigned int length = listLength(&unit->programList);
                while (iterations > 0 && length > 0) {
                    cpuStep(unit);
                    iterations--;
                    length--;
                }
                cpuDebug(unit);
            }
        }

        if (strcmp(argv[1], "-R") == 0) {
            while (saveInstructions(unit)) {
                unsigned int length = listLength(&unit->programList);
                while (length > 0) {
                    cpuStep(unit);
                    length--;
                }
                cpuDebug(unit);
            }
        }
    }

    cpuClear(unit);
    free(unit);
	return 0;
}

#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

/**
 * Identify given string and return relevant instruction.
 * If string is not liable then return Nop instruction.
 *
 * @param instruction   given string (type const char *)
 * @return              instruction (type instructionType)
 */
enum instructionType getInstructionStdin(const char *instruction)
{
    if (strcmp(instruction, "add\n") == 0) {
        return InstAdd;
    } else if (strcmp(instruction, "sub\n") == 0) {
        return InstSub;
    } else if (strcmp(instruction, "mul\n") == 0) {
        return InstMul;
    } else if (strcmp(instruction, "div\n") == 0) {
        return InstDiv;
    } else if (strcmp(instruction, "mova") == 0) {
        return InstMova;
    } else if (strcmp(instruction, "load\n") == 0) {
        return InstLoad;
    } else if (strcmp(instruction, "swac\n") == 0) {
        return InstSwac;
    } else if (strcmp(instruction, "swab\n") == 0) {
        return InstSwab;
    } else if (strcmp(instruction, "inc\n") == 0) {
        return InstInc;
    } else if (strcmp(instruction, "dec\n") == 0) {
        return InstDec;
    } else if (strcmp(instruction, "push\n") == 0) {
        return InstPush;
    } else if (strcmp(instruction, "pop\n") == 0) {
        return InstPop;
    } else {
        return InstNop;
    }
}

/**
 * Read instructions from stdin and if the instructions are
 * valid then save them to the list, otherwise ignore it.
 * Command 'run' terminate function with true value, command
 * 'halt' with false value.
 *
 * @param unit          given cpu structure
 * @return              false if given instruction is 'halt',
 *                      true otherwise
 */
bool saveInstructions(struct cpu *unit)
{
    char buffer[32];
    char *instruction, *argument;

    do {
        fprintf(stdout, "> ");

        fgets(buffer, 32, stdin);
        assert(buffer != NULL);

        instruction = strtok(buffer, " ");

        if (strcmp(instruction, "halt\n") == 0) {
            return false;
        }

        if (strcmp(instruction, "run\n") == 0) {
            return true;
        }

        enum instructionType instructionEnum = getInstructionStdin(instruction);

        if (instructionEnum != InstNop) {
            struct instruction *instr = malloc(sizeof *instr);
            assert(instr != NULL);

            if (instructionEnum == InstMova) {
                argument = strtok(NULL, " ");
                instr->arg = atoi(argument);
            } else {
                instr->arg = 0;
            }

            instr->type = instructionEnum;
            listPush(&unit->programList, instr);

            if (unit->programList.current == unit->programList.end) {
                listBackstep(&unit->programList);
            }
        }
    } while (true);
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
    }

    if (strcmp(argv[1], "-h") == 0) {
        fprintf(stdout, "\n-h\t\tprogram vypise informace o programu a jeho prepinacich, nasledne se ukonci\n");
        fprintf(stdout, "-r <number>\tpo zavolani prikazu run program vyhodnoti nejvyse <number> instrukci\n");
        fprintf(stdout, "-R\t\tpo zavolani prikazu run program vyhodnocuje instrukce ve fronte tak dlouho, dokud nenarazi na konec seznamu instrukci\n\n");
    }

    if (strcmp(argv[1], "-r") == 0) {
        while (saveInstructions(unit)) {
            unsigned int iterations = atoi(argv[2]);
            while (unit->programList.current != unit->programList.end && iterations > 0) {
                cpuStep(unit);
                iterations--;
            }
            cpuDebug(unit);
        }
    }

    if (strcmp(argv[1], "-R") == 0) {
        while (saveInstructions(unit)) {
            while (unit->programList.current != unit->programList.end) {
                cpuStep(unit);
            }
            cpuDebug(unit);
        }
    }

    cpuClear(unit);
    free(unit);

    return 0;
}

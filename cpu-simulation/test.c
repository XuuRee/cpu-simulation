#define TESTING
#define TESTING_MAIN

#include "testing.h"
#include "cpu.h"


TEST(basic_run) {
	struct cpu cpu;
	cpuInit(&cpu);
	cpuDebug(&cpu);

	ASSERT_FILE(stdout, "# Registers 0 0 0 | Stack"); 

	cpuClear(&cpu);
}
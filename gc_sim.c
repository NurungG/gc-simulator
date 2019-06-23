#include "gc_sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct gc_sim_ops gc_sim = {
	.create     = gc_sim_create,
	.destroy    = gc_sim_destroy,
	.simulate   = gc_sim_simulate,
	.write      = gc_sim_write,
	.print_stat = gc_sim_print_stat,
};

struct gc_sim_env env;
struct gc_sim_stat stat;

static void print_info() {
	printf("Device size: %ldGB\n", DEVICE_CAPACITY/G);
	printf("nr_pages: %ld\n", NR_PAGES);
	printf("nr_blocks: %ld\n", NR_BLOCKS);
	printf("nr_superblocks: %ld\n", NR_SUPERBLOCKS);

	puts("");
	printf("op_factor: %.2f\n", OP_FACTOR);
	printf("range: %d\n", env.range);

	printf("rand_max: %d\n", RAND_MAX);
}

int gc_sim_create() {
	int rc = 0;
	puts("===================");
	puts("GC Simulator Create");
	puts("===================\n");

	env.bt = RAND_WRITE;
	env.cycs = 2;
	env.range = RANGE;

	if (env.bt == RAND_WRITE) {
		srand(time(NULL));
	}

	env.itable = (bool *)malloc(sizeof(bool) * NR_PAGES);
	env.mtable = (int *)malloc(sizeof(int) * NR_PAGES);
	for (int i = 0; i < NR_PAGES; i++) {
		env.itable[i] = true;
		env.mtable[i] = -1;
	}

	print_info();
free:
	return rc;
}

int gc_sim_destroy() {
	int rc = 0;
	puts("====================");
	puts("GC Simulator Destroy");
	puts("====================");

	return rc;
}

int gc_sim_simulate() {
	int rc = 0;
	int bench_type = env.bt;
	int cycles = env.cycs;

	int lpa;

	puts("==================");
	puts("GC Simulator Start");
	puts("==================\n");

	for (int i = 0; i < env.range * cycles; i++) {
		switch (bench_type) {
		case SEQ_WRITE:
			break;
		case RAND_WRITE:
			lpa = rand() % env.range;
			gc_sim.write(lpa);
			break;
		default:
			printf("bench_type_error, bench_type: %d\n", bench_type);
			rc = 1;
			return rc;
		}
	}

	return rc;
}

static int garbage_collection() {

}

static int get_next_ppa() {
	
}

int gc_sim_write(int lpa) {
	int rc = 0;
	int ppa;

	ppa = get_next_ppa();
	env.itable[ppa] = true;
	env.mtable[lpa] = ppa;
}

int gc_sim_print_stat() {

}

int main() {
	int rc = 0;
	rc = gc_sim.create();
	if (rc) {
		fprintf(stderr, "[GC_SIM] error on create()\n");
		goto end;
	}

	rc = gc_sim.simulate();
	if (rc) {
		fprintf(stderr, "[GC_SIM] error on simulate()\n");
		goto clean_up;
	}

	rc = gc_sim.print_stat();
	if (rc) {
		fprintf(stderr, "[GC_SIM] error on print_stat()\n");
		goto clean_up;
	}

clean_up:
	gc_sim.destroy();
end:
	return 0;
}

#include "gc_sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int gc_sim_bench_config(int bench_type, int cycles, struct gc_sim_env *env) {
	env->bench_type = bench_type;
	env->cycles = cycles;
	env->range = RANGE;

	return 0;
}

void gc_sim_device_info(struct gc_sim_env *env) {
	puts("[Device Configuration]");
	printf("Page size: %d KB\n", PAGESIZE/K);
	printf("Page per Block: %d\n", PAGE_PER_BLOCK);
	printf("Block per Superblock: %d\n", BLOCK_PER_SUPERBLOCK);
	puts("");
	printf("Device Capacity: %ld GB\n", DEVICE_CAPACITY/G);
	printf("nr_pages: %ld\n", NR_PAGES);
	printf("nr_blocks: %ld\n", NR_BLOCKS);
	printf("nr_superblocks: %ld\n", NR_SUPERBLOCKS);
	puts("");
	printf("Over-Provisioning Factor: %.2f\n", OP_FACTOR);
	puts("");

	puts("[Bench Configuration]");
	if (env->bench_type == SEQ_WRITE) printf("SEQ_WRITE");
	else if (env->bench_type == RAND_WRITE) printf("RAND_WRITE");
	else printf("BENCH_TYPE_ERR");
	printf(" Bench %d cycles\n", env->cycles);
	puts("");
}

void gc_sim_print_stat(struct gc_sim_stat *stat) {
	puts("=================");
	puts("GC Simulator Stat");
	puts("=================");

	puts("");

	printf("Write: %d\n", stat->writes);
	printf("Valid Copy: %d\n", stat->valid_copies);
	printf("GC: %d\n", stat->gc_cnt);

	puts("");

	printf("WAF: %.2f\n", (float)(stat->writes + stat->valid_copies) / stat->writes);

	puts("");
}

static void progress_bar(int current, int total) {
	const int bar_width = 20;

	if (current % (total/bar_width) == 0) {
		printf("\r[");
		for (int i = 0; i < current / (total/bar_width)-1; i++) printf("=");
		if (current/bar_width != total/bar_width) printf(">");
		for (int i = current / (total/bar_width); i < bar_width-1; i++) printf(" ");
		printf("]\n");
	}
}

int gc_sim_simulate(struct gc_sim_ops *ops, struct gc_sim_env *env){
	int rc = 0;
	int bench_type = env->bench_type;
	int cycles = env->cycles;
	int range = env->range;

	int lpa;

	srand(time(NULL));

	ops->create();

	puts("==================");
	puts("GC Simulator Start");
	puts("==================");

	puts("");

	for (int i = 0; i < range * cycles; i++) {
		switch (bench_type) {
		case SEQ_WRITE:
			break;
		case RAND_WRITE:
			lpa = rand() % range;
			ops->write(lpa);
			//usleep(1);
			break;
		default:
			printf("bench_type_error, bench_type: %d\n", bench_type);
			rc = 1;
			goto free;
		}
		progress_bar(i+1, range * cycles);
	}
	puts("");

free:
	ops->destroy();

	return rc;
}

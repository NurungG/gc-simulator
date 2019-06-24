/*
 * Bloom FTL implementation
 */

#include "gc_sim.h"
#include "bloomftl.h"
#include <stdio.h>
#include <stdlib.h>

struct gc_sim_ops bloom = {
	.create     = bloom_create,
	.destroy    = bloom_destroy,
	.write      = bloom_write,
	.print_stat = bloom_print_stat,
};

struct gc_sim_env env;
struct gc_sim_stat stat;

int bloom_create() {
	int rc = 0;

	env.bt = RAND_WRITE;
	env.cycs = 2;
	env.range = RANGE;

	env.itable = (bool *)malloc(sizeof(bool) * NR_PAGES);
	env.mtable = (int *)malloc(sizeof(int) * NR_PAGES);
	for (int i = 0; i < NR_PAGES; i++) {
		env.itable[i] = true;
		env.mtable[i] = -1;
	}
free:
	return rc;
}

int bloom_destroy() {
	int rc = 0;

	return rc;
}

static int garbage_collection() {

}

static int get_next_ppa() {
	
}

int bloom_write(int lpa) {
	int rc = 0;
	int ppa;

	ppa = get_next_ppa();
	env.itable[ppa] = true;
	env.mtable[lpa] = ppa;
}

int bloom_print_stat() {
	puts("hello, it's bloom print stat");
}


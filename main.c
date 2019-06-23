#include <stdio.h>
#include "gc_sim.h"

#ifdef bloomftl
#include "bloomftl.h"
#endif

extern struct gc_sim_ops ops;
extern struct gc_sim_env env;
extern struct gc_sim_stat stat;

static void print_device_info() {
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
}

int main() {
	print_device_info();

	ops.print_stat();
	return 0;
}

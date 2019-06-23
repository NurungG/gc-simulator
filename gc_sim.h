/*
 * GC Simulator Header
 */

#ifndef __GC_SIM_H__
#define __GC_SIM_H__

#include <stdbool.h>

#define K (1024)
#define M (1024 * K)
#define G (1024 * M)
#define T (1024L * G)

/* Device Configuration */
#define PAGESIZE (8*K) 

#define PAGE_PER_BLOCK 256
#define BLOCK_PER_SUPERBLOCK 4

#define DEVICE_CAPACITY (256L*G)
#define NR_PAGES (DEVICE_CAPACITY/PAGESIZE)
#define NR_BLOCKS (NR_PAGES/PAGE_PER_BLOCK)
#define NR_SUPERBLOCKS (NR_BLOCKS/BLOCK_PER_SUPERBLOCK)

#define OP_FACTOR 0.25
#define RANGE (NR_PAGES*(1-OP_FACTOR))

/* Bench Types */
#define SEQ_WRITE  0
#define RAND_WRITE 1

/* Structures */
struct gc_sim_ops {
	int (*create) ();
	int (*destroy) ();
	int (*simulate) ();
	int (*write) (int);
	int (*print_stat) ();
};

struct gc_sim_env {
	int bt;
	int cycs;
	int range;

	bool *itable;
	int *mtable;
};

struct gc_sim_stat {

};

#endif

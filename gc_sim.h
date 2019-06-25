/*
 * GC Simulator Header
 */

#ifndef __GC_SIM_H__
#define __GC_SIM_H__

#include <stdint.h>

#define K (1024)
#define M (1024 * K)
#define G (1024 * M)
#define T (1024L * G)

/* Device Configuration */
#define PAGESIZE (4*K) 

#define DEVICE_CAPACITY (256L*G)
#define NR_PAGES (DEVICE_CAPACITY/PAGESIZE)
#define NR_BLOCKS (NR_PAGES/PAGE_PER_BLOCK)
#define NR_SUPERBLOCKS (NR_BLOCKS/BLOCK_PER_SUPERBLOCK)

#define PAGE_PER_BLOCK 256
//#define BLOCK_PER_SUPERBLOCK NR_BLOCKS
#define BLOCK_PER_SUPERBLOCK 4
#define PAGE_PER_SUPERBLOCK (PAGE_PER_BLOCK * BLOCK_PER_SUPERBLOCK)

#define OP_FACTOR 0.07
#define RANGE (NR_PAGES*(1-OP_FACTOR))

/* Bench Types */
#define SEQ_WRITE  0
#define RAND_WRITE 1

/* Structures */
struct gc_sim_ops {
	int (*create) ();
	int (*destroy) ();
	int (*write) (int);
};

struct gc_sim_env {
	int bench_type;
	int cycles;
	int range;
};

struct gc_sim_stat {
	uint64_t writes;
	uint64_t valid_copies;
	uint64_t gc_cnt;
};

int gc_sim_bench_config(int, int, struct gc_sim_env *);
void gc_sim_print_stat(struct gc_sim_stat *);
void gc_sim_device_info(struct gc_sim_env *);
int gc_sim_simulate(struct gc_sim_ops *, struct gc_sim_env *);

#endif

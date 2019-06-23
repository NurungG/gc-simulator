/*
 * Bloom FTL ops header
 */

#ifndef __GC_SIM_BLOOM_FTL_H__
#define __GC_SIM_BLOOM_FTL_H__

/* Functions */
int bloom_create();
int bloom_destroy();
int bloom_simulate();
int bloom_write(int);
int bloom_print_stat();

#endif

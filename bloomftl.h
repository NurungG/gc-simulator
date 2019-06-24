/*
 * Bloom FTL ops header
 */

#ifndef __GC_SIM_BLOOM_FTL_H__
#define __GC_SIM_BLOOM_FTL_H__

#include <stdbool.h>

/* Structures */
struct bloom_member {
	bool *itable;
	int *mtable;
	int *oob;

	int *ppa_in_sb;
};

/* Functions */
int bloom_create();
int bloom_destroy();
int bloom_write(int);

#endif

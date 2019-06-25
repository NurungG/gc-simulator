/*
 * Bloom FTL ops header
 */

#ifndef __GC_SIM_BLOOM_FTL_H__
#define __GC_SIM_BLOOM_FTL_H__

#include <stdbool.h>

/* Structures */
struct blm_member {
	bool *itable;	// Invalid Table
	int *mtable;	// Mapping Table
	int *oob;	// Out-Of-Band area

	int *ppa_in_sb;
};

/* Functions */
int blm_create();
int blm_destroy();
int blm_write(int);

#endif

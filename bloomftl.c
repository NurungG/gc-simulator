/*
 * Bloom FTL implementation
 */

#include "gc_sim.h"
#include "bloomftl.h"
#include <stdio.h>
#include <stdlib.h>

struct gc_sim_ops ops = {
	.create     = blm_create,
	.destroy    = blm_destroy,
	.write      = blm_write,
};

struct gc_sim_env env;
struct gc_sim_stat stat;

struct blm_member blm;

int blm_create() {
	int rc = 0;

	blm.itable = (bool *)malloc(sizeof(bool) * NR_PAGES);
	blm.mtable = (int *)malloc(sizeof(int) * NR_PAGES);
	blm.oob = (int *)malloc(sizeof(int) * NR_PAGES);

	for (int i = 0; i < NR_PAGES; i++) {
		blm.itable[i] = 1;
		blm.mtable[i] = -1;
		blm.oob[i] = -1; 
	}

	blm.ppa_in_sb = (int *)malloc(sizeof(int) * NR_SUPERBLOCKS);

	for (int i = 0; i < NR_SUPERBLOCKS; i++) {
		blm.ppa_in_sb[i] = 0;
	}

	return rc;
}

int blm_destroy() {
	int rc = 0;

	free(blm.itable);
	free(blm.mtable);
	free(blm.oob);
	free(blm.ppa_in_sb);

	return rc;
}

static int garbage_collection(int lpa, int ppa) {
	int sblk_idx = lpa % NR_SUPERBLOCKS;
	int blk_idx = (ppa / PAGE_PER_BLOCK) % BLOCK_PER_SUPERBLOCK;
	int rppa = sblk_idx * PAGE_PER_SUPERBLOCK + blk_idx * PAGE_PER_BLOCK;

	bool *it = blm.itable;
	int *mt = blm.mtable;
	int *oob = blm.oob;

	struct valid_page {
		int origin_ppa;
		int target_lpa;
	} vp[PAGE_PER_BLOCK];

	int valid_idx = 0;

	// Valid copy (read)
	for (int i = rppa; i < rppa + PAGE_PER_BLOCK; i++) {
		if (it[i] == 0) {
			vp[valid_idx].origin_ppa = i;
			vp[valid_idx].target_lpa = oob[i];
			it[i] = 1;
			oob[i] = -1;

			valid_idx++;
		}
	}

	// Valid copy (write)
	for (int i = 0; i < valid_idx; i++) {
		mt[vp[i].target_lpa] = rppa;
		it[rppa] = 0;
		oob[rppa] = vp[i].target_lpa;

		ppa++; rppa++;

		stat.valid_copies++;
	}

	// Erase
	stat.gc_cnt++;
	//if (sblk_idx == 0) printf("blk %d (%d / %d)\n", blk_idx, valid_idx, PAGE_PER_BLOCK);
	//if (blk_idx < 4) printf("blk %d (%d / %d)\n", blk_idx, valid_idx, PAGE_PER_BLOCK);

	return ppa;
}

static int get_next_ppa(int lpa) {
	int sblk_idx = lpa % NR_SUPERBLOCKS;
	int ppa = blm.ppa_in_sb[sblk_idx]++;
	int blk_idx = (ppa / PAGE_PER_BLOCK) % BLOCK_PER_SUPERBLOCK;

	if (ppa >= PAGE_PER_SUPERBLOCK) {
		if (ppa % PAGE_PER_BLOCK == 0) {
			ppa = garbage_collection(lpa, ppa);
			blm.ppa_in_sb[sblk_idx] = ppa+1;
		}
	}

	ppa = sblk_idx * PAGE_PER_SUPERBLOCK + (ppa % PAGE_PER_SUPERBLOCK);
	//if (sblk_idx == 0) printf("%d - %d\n", blk_idx, ppa);

	return ppa;
}

int blm_write(int lpa) {
	int rc = 0;

	bool *it = blm.itable;
	int *mt = blm.mtable;
	int *oob = blm.oob;

	int ppa = get_next_ppa(lpa);
	if (mt[lpa] != -1) {
		it[mt[lpa]] = 1;
		oob[mt[lpa]] = -1;
	}
	it[ppa] = 0;
	mt[lpa] = ppa;
	oob[ppa] = lpa;

	stat.writes++;

	return rc;
}

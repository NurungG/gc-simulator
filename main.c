#include <stdio.h>
#include "gc_sim.h"

#ifdef bloomftl
#include "bloomftl.h"
#endif

extern struct gc_sim_ops ops;
extern struct gc_sim_env env;
extern struct gc_sim_stat stat;

int main() {
	gc_sim_bench_config(RAND_WRITE, 1000, &env);

	gc_sim_device_info(&env);
	gc_sim_simulate(&ops, &env);
	gc_sim_print_stat(&stat);

	return 0;
}

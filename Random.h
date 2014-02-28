#ifndef RANDOM_H
#define RANDOM_H

#include "common.h"

class Random {
public:

	static inline int rand_int() {
		return rand();
	}

	static inline RTdouble rand_float() {
		return ((RTdouble) rand() / (RTdouble) RAND_MAX);
	}

	static inline void rand_init(long long seed = 0ll) {
		if(seed == 0) {
			srand(static_cast<unsigned int>(time(NULL)));
		}
		else {
			srand(static_cast<unsigned int>(seed));
		}
	}
};

#endif
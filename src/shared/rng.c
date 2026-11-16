#include "shared/rng.h"

// See SplitMix64
uint64_t mw_rng_next(uint64_t *state){

	uint64_t z = (*state += 0x9e3779b97f4a7c15ULL);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
	z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;

	return z ^ (z >> 31);

}
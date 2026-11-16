#pragma once

#include <stdbool.h>
#include <stdint.h>


#define MW_MAX_ENTITIES 2048		// rough back-of-the-napckin math says this should be enough, nya~

typedef struct mw_entity_s mw_entity_t;

typedef void (*mw_think_func_t)(mw_entity_t *self);

struct mw_entity_s{

	bool active;

	float pos_x, pos_y;
	uint8_t health;

	mw_think_func_t think;

};
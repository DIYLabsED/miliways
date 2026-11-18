/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/server/server_config.h
	Struct to store server configuration

*/ 

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <enet/enet.h>

#include "shared/entity.h"

typedef struct{

	ENetHost 		*enet_server;
	ENetAddress 	server_address;

	ENetPeer *players[2];
	int player_characters[2];
	int player_count;

	bool create_new_world;
	uint64_t world_seed;
	char *world_path;

	mw_entity_t entities[MW_MAX_ENTITIES];

} mw_server_global;
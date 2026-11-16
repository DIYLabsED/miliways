/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/client/client_config.h
	Struct to store client configuration

*/ 

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <enet/enet.h>

#include "shared/entity.h"

typedef struct{

	ENetHost 		*enet_client;
	ENetAddress 	server_address;
	ENetPeer 		*enet_peer;

	int playing_as;
	bool joined;

	mw_entity_t entities[MW_MAX_ENTITIES];

} mw_client_global;
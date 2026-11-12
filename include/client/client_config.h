/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/client/client_config.h
	Struct to store client configuration

*/ 

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <enet/enet.h>

#define MW_CLIENT_LILAC 1
#define MW_CLIENT_CLOVER -1

typedef struct{

	ENetHost 		*enet_client;
	ENetAddress 	server_address;
	ENetPeer 		*enet_peer;

	int playing_as;

} mw_client_global;
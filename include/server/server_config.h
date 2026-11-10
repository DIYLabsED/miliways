/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/server/server_config.h
	Struct to store server configuration

*/ 

#pragma once

#include <stdint.h>
#include <enet/enet.h>

typedef struct{

	// ENet library
	char *addr;
	uint16_t port;

} mw_server_global;
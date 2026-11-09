/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/server/server_state.h
	Enum for server state

*/ 

#pragma once

typedef enum{
	MW_SERVER_READ_ARGS,
	MW_SERVER_ENET_SETUP,
	MW_SERVER_CLEANUP
} mw_server_state;
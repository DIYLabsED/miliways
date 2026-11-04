/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/server/server_state.h
	Enum for server state

*/ 

#pragma once

enum mw_server_state{
	MW_SERVER_SETUP,
	MW_SERVER_WAITING_FOR_PLAYERS,
	MW_SERVER_WAITING_FOR_LILAC,
	MW_SERVER_WAITING_FOR_CLOVER,
	MW_SERVER_IN_GAME,
	MW_SERVER_SHUTDOWN
};
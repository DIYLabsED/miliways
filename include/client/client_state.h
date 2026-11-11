/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/client/client_state.h
	Enum for client state

*/ 

#pragma once

#include <stdbool.h>
#include "client/client_config.h"


typedef void(*mw_client_state_func)(int argc, char **argv);

void mw_state_setup(int argc, char **argv);
void mw_state_cleanup(int argc, char **argv);


extern mw_client_state_func g_current_state;
extern bool g_server_running;
extern mw_client_global g_client_global;
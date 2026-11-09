#include <enet/enet.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "server/server_state.h"
#include "shared/loc.h"
#include "shared/log.h"
#include "shared/arg.h"
#include "server/server_config.h"
#include "shared/reslist.h"


mw_server_cfg   g_server_config;
mw_server_state g_server_state 		= MW_SERVER_READ_ARGS;
bool 			g_server_running 	= true;
ENetHost 		*g_enet_server;
ENetAddress 	g_server_address;


void read_args(int argc, char **argv);
void setup_enet();
void cleanup();


int main(int argc, char **argv){

	MW_LOG(MW_LOG_WARNING, MW_LOC_SECURITY_WARNING);
	MW_LOG(MW_LOG_INFO, MW_LOC_LICENSE_AND_CREDITS);

	while(g_server_running){

		switch(g_server_state){

			case MW_SERVER_READ_ARGS:
				read_args(argc, argv);
				g_server_state = MW_SERVER_ENET_SETUP;				
				break;

			case MW_SERVER_ENET_SETUP:
				setup_enet();
				//g_server_state = MW_WAIT_FOR_CLIENTS;
				exit(EXIT_SUCCESS);
				break;

			case MW_SERVER_CLEANUP:
				cleanup();
				break;

			default: 
				break;

		}

	}

	return 0;

}

void read_args(int argc, char **argv){

	g_server_config.addr 				= mw_arg_get_str(argc, argv, "--addr", "0");			// 0 for local address
	g_server_config.port 				= mw_arg_get_ll(argc, argv, "--port", 0);				// 0 for OS-assigned port

}

void setup_enet(){

	g_server_address.host = ENET_HOST_ANY;				// TODO: addr is a uint, but address needs to passed in as str arg, some way to specify no addr in fallback
	g_server_address.port = g_server_config.port;

	// TODO: replace magic numbers with macros/constants (don't need to be passed in through CLI args)
	g_enet_server = enet_host_create(&g_server_address,		// Address
									 2,						// Number of clients
									 2,						// Number of channels
									 0,						// Incoming bandwidth
									 0						// Outgoing bandwidth
														);

	if(g_enet_server == NULL){
		MW_LOG(MW_LOG_ERROR, "ENet server create failed");
		exit(EXIT_FAILURE);
	}

	MW_LOG(MW_LOG_INFO, "Created ENet server");

	char ipstring[256];
	enet_address_get_host(&g_enet_server->address, ipstring, sizeof(ipstring));
	printf("Server IP: %s, Server Port: %d\n", ipstring, g_enet_server->address.port);

}

void cleanup(){

	enet_host_destroy(g_enet_server);

}
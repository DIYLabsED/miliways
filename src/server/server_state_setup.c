#include <enet/enet.h>
#include <stdlib.h>

#include "server/server_state.h"
#include "shared/log.h"
#include "shared/arg.h"


void read_enet_args(int argc, char **argv){

	if(mw_arg_exists(argc, argv, "--addr") != -1){

		char *addr = mw_arg_get_str(argc, argv, "--addr", "FALLBACK");
		enet_address_set_host(&g_server_global.server_address, addr);
		MW_LOG(MW_LOG_INFO, "Using custom address: %s", addr);

	}
	else{

		g_server_global.server_address.host = ENET_HOST_ANY;
		MW_LOG(MW_LOG_INFO, "No address configured");

	}

	if(mw_arg_exists(argc, argv, "--port") != -1){

		int port = mw_arg_get_ll(argc, argv, "--port", 0);
		g_server_global.server_address.port = port;
		MW_LOG(MW_LOG_INFO, "Using custom port: %d", port);

	}
	else{

		g_server_global.server_address.port = 0;
		MW_LOG(MW_LOG_INFO, "No port configured. Letting OS assign us a port");

	}

	MW_LOG(MW_LOG_INFO, "Parsed ENet args");

}

void start_enet_server(){

	g_server_global.enet_server = enet_host_create(&g_server_global.server_address,		// Addr
												   2,									// Number of clients
												   2,									// Number of channels
												   0,									// Incoming bandwidth
												   0									// Outgoing bandwidth
	);

	if(g_server_global.enet_server == NULL){
		MW_LOG(MW_LOG_ERROR, "ENet server create failed");
		exit(EXIT_FAILURE);
	}

	MW_LOG(MW_LOG_INFO, "Created ENet server.");

}

void mw_state_setup(int argc, char **argv){

	MW_LOG(MW_LOG_INFO, "Starting server setup");

	read_enet_args(argc, argv);
	start_enet_server();

	MW_LOG(MW_LOG_INFO, "Server setup finished");
	g_current_state = mw_state_cleanup;

}
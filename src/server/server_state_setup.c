#include <enet/enet.h>

#include "server/server_state.h"
#include "shared/log.h"
#include "shared/arg.h"


void mw_state_setup(int argc, char **argv){

	MW_LOG(MW_LOG_INFO, "Starting server setup");

	// Server address/port
	if(mw_arg_exists(argc, argv, "--addr")){
		enet_address_set_host(&g_server_global.server_address, mw_arg_get_str(argc, argv, "--addr", "FALLBACK"));
	}
	else{
		g_server_global.server_address.host = ENET_HOST_ANY;
	}

	if(mw_arg_exists(argc, argv, "--port")){
		g_server_global.server_address.port = mw_arg_get_ll(argc, argv, "--port", 0);
	}
	else{
		g_server_global.server_address.port = 0;
	}

	char ipstring[32];
	enet_address_get_host(&g_server_global.server_address, ipstring, sizeof(ipstring));
	MW_LOG(MW_LOG_INFO, "ENet server host: %s, ENet server port: %d", ipstring, g_server_global.server_address.port);

	MW_LOG(MW_LOG_INFO, "Server setup finished");
	g_current_state = mw_state_cleanup;

}
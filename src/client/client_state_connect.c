#include <enet/enet.h>
#include <stdlib.h>
#include <string.h>

#include "client/client_config.h"
#include "client/client_state.h"
#include "shared/log.h"
#include "shared/arg.h"
#include "shared/consts.h"


void mw_state_connect(int argc, char **argv){

	g_client_global.enet_peer = enet_host_connect(g_client_global.enet_client, &g_client_global.server_address, MW_ENET_MAX_CONNECTIONS, 0);

	if(g_client_global.enet_peer == NULL){

		MW_LOG(MW_LOG_ERROR, "No available peers for starting ENet connection!");
		exit(EXIT_FAILURE);

	}

	int timeout = 5000;
	ENetEvent event;	

	while(timeout > 0){

		int serviced = enet_host_service(g_client_global.enet_client, &event, 100);

		if(serviced > 0 && event.type == ENET_EVENT_TYPE_CONNECT){

			MW_LOG(MW_LOG_INFO, "Connected successfully");
			g_current_state = mw_state_cleanup;
			return;
		}

		timeout -= 100;

	}

}
#include <enet/enet.h>
#include <stdlib.h>

#include "server/server_state.h"
#include "shared/log.h"
#include "shared/arg.h"
#include "shared/consts.h"


void mw_state_await_connections(int argc, char **argv){

	MW_LOG(MW_LOG_INFO, "Awaiting client connections");

	ENetEvent event;

	while(1){

		while(enet_host_service(g_server_global.enet_server, &event, 10) > 0){

			switch(event.type){

			case ENET_EVENT_TYPE_CONNECT:
				MW_LOG(MW_LOG_INFO, "Client connected from %x:%u", event.peer->address.host, event.peer->address.port);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				MW_LOG(MW_LOG_INFO, "Client disconnected");
				break;

			}

			event.peer->data = NULL;

		}

	}

}
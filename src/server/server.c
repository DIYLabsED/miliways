#include <stdio.h>

#include <enet/enet.h>

#include "shared/loc.h"


int main(void){

	printf(MW_LOC_SECURITY_WARNING);
	printf(MW_LOC_LICENSE_AND_CREDITS);

	if(enet_initialize() != 0){
		printf("ENet library init failed");
		return 1;
	}

	ENetAddress addr;
	ENetHost* server;

	addr.host = ENET_HOST_ANY;
	addr.port = 1234;

	server = enet_host_create(&addr, 32, 2, 0, 0);

	if(server == NULL){
		printf("ENet server create failed");
		return 1;
	}

	ENetEvent event;
	
	while(true){
		while(enet_host_service(server, &event, 10) > 0){

			switch(event.type){

				case ENET_EVENT_TYPE_CONNECT:
					printf("Client connected from %x:%u\n", event.peer->address.host, event.peer->address.port);
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					printf("Client disconnected");
					break;

			}

			event.peer->data = NULL;

		}

	}

	enet_deinitialize();
	return 0;

}
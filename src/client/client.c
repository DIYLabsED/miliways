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

	ENetHost* client;
	client = enet_host_create(NULL, 1, 2, 0, 0);

	if(client == NULL){
		printf("ENet client create failed");
	}

	ENetAddress addr;
	ENetEvent event;
	ENetPeer* peer;
	enet_address_set_host(&addr, "127.0.0.1");
	addr.port = 1234;

	peer = enet_host_connect(client, &addr, 2, 0);

	if(peer == NULL){
		printf("No available peers for initing enet conn");
		return 1;
	}

    int connected = 0;
    int timeout = 5000;

    while(timeout > 0){

        int serviced = enet_host_service(client, &event, 100);
        if(serviced > 0 && event.type == ENET_EVENT_TYPE_CONNECT){

            printf("Connection succeeded\n");
            connected = 1;
            break;
        }

        timeout -= 100;
    }

    if(!connected){

        printf("Connection failed\n");
        enet_peer_disconnect(peer, 0);
        enet_host_destroy(client);
        enet_deinitialize();
        return 1;

    }

    int delay = 3000;
    while(delay > 0){

        enet_host_service(client, &event, 100);
        delay -= 100;
        
    }

    enet_peer_disconnect(peer, 0);
    enet_host_service(client, &event, 3000);

	enet_host_destroy(client);
	enet_deinitialize();

	return 0;

}
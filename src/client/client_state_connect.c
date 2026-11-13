#include <enet/enet.h>
#include <stdlib.h>
#include <string.h>

#include "client/client_config.h"
#include "client/client_state.h"
#include "shared/log.h"
#include "shared/arg.h"
#include "shared/consts.h"
#include "shared/packet.h"


void mw_state_connect(int argc, char **argv){

	g_client_global.enet_peer = enet_host_connect(g_client_global.enet_client, &g_client_global.server_address, MW_ENET_MAX_CONNECTIONS, 0);

	if(g_client_global.enet_peer == NULL){

		MW_LOG(MW_LOG_ERROR, "No available peers for starting ENet connection!");
		exit(EXIT_FAILURE);

	}

	int timeout_ms = 5000;
	ENetEvent event;

	while(timeout_ms > 0){

		int serviced = enet_host_service(g_client_global.enet_client, &event, 100);

		if(serviced > 0 && event.type == ENET_EVENT_TYPE_CONNECT){

			MW_LOG(MW_LOG_INFO, "Connected to server, requesting character slot");

			mw_payload_join_request request = {g_client_global.playing_as};
			mw_packet packet = {{MW_PACKET_JOIN_REQUEST, sizeof(request)}, &request};

			if(!mw_send_packet(g_client_global.enet_peer, &packet, ENET_PACKET_FLAG_RELIABLE, 0)){
				g_current_state = mw_state_cleanup;
				MW_LOG(MW_LOG_ERROR, "Failed to send join request to server");
				return;
			}

			MW_LOG(MW_LOG_INFO, "Sent join request to server");

			enet_host_flush(g_client_global.enet_client);

			int join_timeout_ms = 5000;
			while(join_timeout_ms > 0){

				int join_serviced = enet_host_service(g_client_global.enet_client, &event, 100);
				if(join_serviced < 0) break;
				if(join_serviced == 0){	join_timeout_ms -= 100; continue;	}

				if(event.type == ENET_EVENT_TYPE_DISCONNECT){
					MW_LOG(MW_LOG_ERROR, "Server disconnected before accepting us");
					g_current_state = mw_state_cleanup;
					return;
				}

				if(event.type == ENET_EVENT_TYPE_RECEIVE){

					mw_packet response = {0};
					bool valid = mw_recv_packet(event.packet, &response) && response.header.type == MW_PACKET_JOIN_RESULT && response.header.length == sizeof(mw_payload_join_result);

					if(valid){

						mw_payload_join_result result;
						memcpy(&result, response.payload, sizeof(result));

						if(result.accepted && result.character == g_client_global.playing_as){

							MW_LOG(MW_LOG_INFO, "Joined successfully as %s", result.character == MW_CLIENT_CLOVER ? "Clover" : "Lilac");
							g_client_global.joined = true;
							mw_free_packet(&response);
							enet_packet_destroy(event.packet);
							g_current_state = mw_state_cleanup;
							return;

						}
						MW_LOG(MW_LOG_ERROR, "Join request rejected by server for reason %u", result.reason);

					}
					mw_free_packet(&response);
					enet_packet_destroy(event.packet);
					g_current_state = mw_state_cleanup;
					return;

				}

			}
			MW_LOG(MW_LOG_ERROR, "Timed out waiting for server join decision");
			g_current_state = mw_state_cleanup;
			return;

		}
		if(serviced > 0 && event.type == ENET_EVENT_TYPE_DISCONNECT) break;
		timeout_ms -= 100;

	}
	MW_LOG(MW_LOG_ERROR, "Connection timed out");
	g_current_state = mw_state_cleanup;
	return;

}
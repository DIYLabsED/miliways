#include <string.h>

#include <enet/enet.h>

#include "server/server_networking.h"
#include "server/server_state.h"
#include "shared/consts.h"
#include "shared/log.h"
#include "shared/arg.h"
#include "shared/packet.h"


int get_player_slot(ENetPeer *peer){

	for(int i = 0; i < 2; i++){
		if(g_server_global.players[i] == peer) return i;
	}

	return -1;

}

void send_join_result(ENetPeer *peer, mw_join_result res, int character){

	mw_payload_join_result payload = {(uint8_t)(res == MW_JOIN_ACCEPTED), (uint8_t)res, character};
	mw_packet packet = {{MW_PACKET_JOIN_RESULT, sizeof(payload)}, &payload};
	mw_send_packet(peer, &packet, ENET_PACKET_FLAG_RELIABLE, 0);
	enet_host_flush(g_server_global.enet_server);

}

void reject_peer(ENetPeer *peer, mw_join_result res){

	send_join_result(peer, res, 0);
	enet_peer_disconnect_later(peer, 0);

}

void handle_join_request(ENetPeer *peer, const mw_packet *packet){

	if(packet->header.length != sizeof(mw_payload_join_request)){
		reject_peer(peer, MW_JOIN_INVALID_CHARACTER);
		return;
	}

	mw_payload_join_request request;
	memcpy(&request, packet->payload, sizeof(request));

	if(request.character != MW_CLIENT_CLOVER && request.character != MW_CLIENT_LILAC){
		reject_peer(peer, MW_JOIN_INVALID_CHARACTER);
		MW_LOG(MW_LOG_WARNING, "Client tried to join with invalid character");
		return;
	}
	if(g_server_global.player_count >= 2){
		reject_peer(peer, MW_JOIN_SERVER_FULL);
		MW_LOG(MW_LOG_WARNING, "Client tried to join, but server is full");
		return;
	}
	for(int i = 0; i < 2; i++){
		if(g_server_global.players[i] && g_server_global.player_characters[i] == request.character){
			reject_peer(peer, MW_JOIN_CHARACTER_TAKEN);
		MW_LOG(MW_LOG_WARNING, "Client tried to join, but their character was taken");
			return;
		}
	}

	int slot = g_server_global.players[0] ? 1 : 0;
	g_server_global.players[slot] = peer;
	g_server_global.player_characters[slot] = request.character;
	g_server_global.player_count++;
	peer->data = (void *)(intptr_t)(slot + 1);
	send_join_result(peer, MW_JOIN_ACCEPTED, request.character);

	MW_LOG(MW_LOG_INFO, "Player joined as %s", request.character == MW_CLIENT_CLOVER ? "Clover" : "Lilac");

}

void handle_packet(ENetPeer *peer, ENetPacket *enet_packet){

	mw_packet packet = {0};

	if(!mw_recv_packet(enet_packet, &packet)){
		mw_free_packet(&packet);
		MW_LOG(MW_LOG_ERROR, "Failed to parse ENet packet");
	}

	switch(packet.header.type){

	case MW_PACKET_JOIN_REQUEST:
		handle_join_request(peer, &packet);
		break;

	default:
		MW_LOG(MW_LOG_WARNING, "Ignoring unknown packet of tpe %u", packet.header.type);
		break;

	}

	mw_free_packet(&packet);

}

void handle_disconnect(ENetEvent *event){

	int slot = get_player_slot(event->peer);

	if(slot >= 0){

		MW_LOG(MW_LOG_INFO, "%s disconnected", g_server_global.player_characters[slot] == MW_CLIENT_CLOVER ? "Clover" : "Lilac");
		g_server_global.players[slot] = NULL;
		g_server_global.player_characters[slot] = 0;
		g_server_global.player_count--;

	}

}

void process_event(ENetEvent *event){

	switch(event->type){

		case ENET_EVENT_TYPE_NONE:
			break;

		case ENET_EVENT_TYPE_CONNECT:
			MW_LOG(MW_LOG_INFO, "Client connected from %x:%u", event->peer->address.host, event->peer->address.port);
			break;

		case ENET_EVENT_TYPE_RECEIVE:
			MW_LOG(MW_LOG_INFO, "Received packet from client");
			handle_packet(event->peer, event->packet);
			enet_packet_destroy(event->packet);
			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			handle_disconnect(event);
			break;

	}

}

void mw_server_service_events(enet_uint32 timeout){

	ENetEvent event;

	while(enet_host_service(g_server_global.enet_server, &event, timeout) > 0){
		process_event(&event);
	}

}
#include <stdlib.h>
#include <string.h>

#include <enet/enet.h>

#include "shared/packet.h"
#include "shared/log.h"


bool mw_send_packet(ENetPeer *peer, mw_packet *pkt, enet_uint32 flags, enet_uint8 chan){

	// Validity checks
	if(!peer){
		MW_LOG(MW_LOG_ERROR, "Null peer passed to mw_send_packet");
		return false;
	}
	if(!pkt){
		MW_LOG(MW_LOG_ERROR, "Null packet passed to mw_send_packet");
		return false;
	}

	// Pack packet
	size_t total_size = sizeof(mw_packet_header) + pkt->header.length;
	uint8_t *packet_data = (uint8_t *)malloc(total_size);

	if(!packet_data){
		MW_LOG(MW_LOG_ERROR, "Failed to allocate memory for packet");
		return false;		
	}

	memcpy(packet_data, &pkt->header, sizeof(mw_packet_header));

	if(pkt->header.length > 0 && pkt->payload){
		memcpy(packet_data + sizeof(mw_packet_header), pkt->payload, pkt->header.length);
	}else{
		MW_LOG(MW_LOG_WARNING, "Packet without any payload passed to mw_send_packet");		
	}

	// Create ENet packet
	ENetPacket *enet_pkt = enet_packet_create(packet_data, total_size, flags);
	free(packet_data);

	if(!enet_pkt){
		MW_LOG(MW_LOG_ERROR, "Failed to create ENet packet");
		return false;
	}

	// Send off to ENet
	if(enet_peer_send(peer, chan, enet_pkt) < 0){
		MW_LOG(MW_LOG_ERROR, "Failed to send packet");
		enet_packet_destroy(enet_pkt);
		return false;
	}

	return true;

}

bool mw_recv_packet(ENetPacket *enet_pkt, mw_packet *mw_pkt){

	// Validity checks
	if(!enet_pkt){
		MW_LOG(MW_LOG_ERROR, "Null ENet packet passed to mw_recv_packet");
		return false;
	}
	if(!mw_pkt){
		MW_LOG(MW_LOG_ERROR, "Null packet passed to mw_recv_packet");
		return false;
	}	

	mw_free_packet(mw_pkt);

	// Sanity check
	if(enet_pkt->dataLength < sizeof(mw_packet_header)){
		MW_LOG(MW_LOG_ERROR, "ENet packet length is less than packet header, corrupted packet");
		return false;
	}

	// Copy header
	memcpy(&mw_pkt->header, enet_pkt->data, sizeof(mw_packet_header));	// prob check header validity so the next step doesn't get garbage data

	// Validate ENet packet length
	size_t expected_pkt_size = sizeof(mw_packet_header) + mw_pkt->header.length;
	if(enet_pkt->dataLength < expected_pkt_size){
		MW_LOG(MW_LOG_ERROR, "ENet packet length does not match packet header's promise");
		return false;
	}

	// Copy payload
	if(mw_pkt->header.length > 0){

		mw_pkt->payload = malloc(mw_pkt->header.length);
		if(!mw_pkt->payload){
			MW_LOG(MW_LOG_ERROR, "Failed to allocate memory for packet");
			return false;
		}

		memcpy(mw_pkt->payload, enet_pkt->data + sizeof(mw_packet_header), mw_pkt->header.length);

	}
	else{
		mw_pkt->payload = NULL;
	}

	return true;

}

void mw_free_packet(mw_packet *pkt){

	if(!pkt){
		MW_LOG(MW_LOG_DEBUG, "Attempted to free a null packet");
		return;
	}

	if(pkt->payload){
		free(pkt->payload);
		pkt->payload = NULL;
	}

	pkt->header.length = 0;
	pkt->header.type = MW_PACKET_NONE;

}
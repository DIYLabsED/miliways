/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/shared/packet.h
	Shared packet-related stuff

*/ 

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <enet/enet.h>
#include <enet/types.h>

// Packet types
typedef enum{

	MW_PACKET_NONE,
	MW_PACKET_JOIN_REQUEST,
	MW_PACKET_JOIN_RESULT,

} mw_packet_type;

// Packet header
#pragma pack(push, 1)
typedef struct{

	uint8_t type;
	uint16_t length;

} mw_packet_header;
#pragma pack(pop)

// Packet
typedef struct{

	mw_packet_header header;
	void *payload;

} mw_packet;


// Payloads
typedef struct{

	int32_t character;
	
} mw_payload_join_request;

typedef struct{

	uint8_t accepted;
	uint8_t reason;
	uint32_t character;

} mw_payload_join_result;

typedef enum{
	MW_JOIN_ACCEPTED,
	MW_JOIN_SERVER_FULL,
	MW_JOIN_CHARACTER_TAKEN,
	MW_JOIN_INVALID_CHARACTER
} mw_join_result;

bool mw_send_packet(ENetPeer *peer, mw_packet *pkt, enet_uint32 flags, enet_uint8 chan);
bool mw_recv_packet(ENetPacket *enet_pkt, mw_packet *mw_pkt);
void mw_free_packet(mw_packet *pkt);
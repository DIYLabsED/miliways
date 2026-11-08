/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/shared/packet.h
	SHared packet-related stuff

*/ 

#pragma once

#include <enet/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <enet/enet.h>


typedef enum{

	MW_PACKET_NONE,
	MW_PACKET_PLAYER_INPUT

} mw_packet_type;

#pragma pack(push, 1)
typedef struct{

	uint8_t type;
	uint16_t length;

} mw_packet_header;
#pragma pack(pop)

typedef struct{

	mw_packet_header header;
	void *payload;

} mw_packet;

// structs for payloads

bool mw_send_packet(ENetPeer *peer, mw_packet *pkt, enet_uint32 flags);
bool mv_recv_pachet(ENetPacket *enetPkt, mw_packet *mwPkt);
void mw_free_packet(mw_packet *pkt);
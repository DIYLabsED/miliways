#include <enet/enet.h>
#include <stdlib.h>
#include <string.h>

#include "client/client_config.h"
#include "client/client_state.h"
#include "shared/log.h"
#include "shared/arg.h"
#include "shared/consts.h"


void read_enet_args(int argc, char **argv){

	if(mw_arg_exists(argc, argv, "--sv-addr") != -1){

		char *addr = mw_arg_get_str(argc, argv, "--sv-addr", "FALLBACK");
		enet_address_set_host(&g_client_global.server_address, addr);
		MW_LOG(MW_LOG_INFO, "Game server address: %s", addr);

	}
	else{

		MW_LOG(MW_LOG_ERROR, "No game server address passed! Pass a valid IPV4 address, or hostname, using the --sv-addr flag");
		exit(EXIT_FAILURE);

	}

	if(mw_arg_exists(argc, argv, "--port") != -1){

		int port = mw_arg_get_ll(argc, argv, "--port", 0);
		g_client_global.server_address.port = port;
		MW_LOG(MW_LOG_INFO, "Game server port: %d", port);

	}
	else{

		MW_LOG(MW_LOG_ERROR, "No game server port passed! Pass a port using --port");
		exit(EXIT_FAILURE);

	}

	if(mw_arg_exists(argc, argv, "--play-as") != -1){

		char *play_as = mw_arg_get_str(argc, argv, "--play-as", "FALLBACK");
		
		if(strcmp(play_as, "lilac") == 0){
			MW_LOG(MW_LOG_INFO, "Playing as Lilac");
			g_client_global.playing_as = MW_CLIENT_LILAC;
		}
		else if(strcmp(play_as, "clover") == 0){
			MW_LOG(MW_LOG_INFO, "Playing as Clover");
			g_client_global.playing_as = MW_CLIENT_CLOVER;
		}
		else{
			MW_LOG(MW_LOG_ERROR, "Invalid player %s passed! Use --play-as clover or --play-as lilac", play_as);
			exit(EXIT_FAILURE);
		}

	}
	else{

		MW_LOG(MW_LOG_ERROR, "No player selected! Use --play-as clover or --play-as lilac");
		exit(EXIT_FAILURE);

	}

	MW_LOG(MW_LOG_INFO, "Parsed ENet args");

}

void start_enet(){

	g_client_global.enet_client = enet_host_create(NULL, 1, MW_ENET_MAX_CONNECTIONS, 0, 0);

	if(g_client_global.enet_client == NULL){
		MW_LOG(MW_LOG_ERROR, "Failed to create ENet client!");
		exit(EXIT_FAILURE);
	}

	MW_LOG(MW_LOG_INFO, "Created ENet client");

}

void mw_state_setup(int argc, char **argv){

	MW_LOG(MW_LOG_INFO, "Starting client setup");

	read_enet_args(argc, argv);
	start_enet();

	MW_LOG(MW_LOG_INFO, "Client setup finished");
	g_current_state = mw_state_connect;

}
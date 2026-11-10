#include <stdlib.h>

#include  <enet/enet.h>

#include "server/server_state.h"
#include "shared/log.h"


void mw_state_cleanup(int argc, char **argv){

	MW_LOG(MW_LOG_INFO, "Deinitializing ENet...");
	enet_deinitialize();

	MW_LOG(MW_LOG_INFO, "Server cleaning done. Goodnight!");
	exit(EXIT_SUCCESS);

}
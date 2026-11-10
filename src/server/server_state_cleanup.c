#include "server/server_state.h"
#include "shared/log.h"
#include <stdlib.h>


void mw_state_cleanup(int argc, char **argv){

	MW_LOG(MW_LOG_INFO, "Cleaning up server. Goodnight!");
	exit(EXIT_SUCCESS);

}
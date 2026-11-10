#include "server/server_state.h"
#include "shared/log.h"


void mw_state_setup(int argc, char **argv){

	MW_LOG(MW_LOG_INFO, "Setup function called");
	g_current_state = mw_state_cleanup;

}
#include <enet/enet.h>
#include <stdio.h>


#include "client/client_config.h"
#include "client/client_state.h"
#include "shared/loc.h"
#include "shared/log.h"
#include "shared/arg.h"



mw_client_global g_client_global;
mw_client_state_func g_current_state = mw_state_setup;
bool g_client_running = true;


int main(int argc, char **argv){

	MW_LOG(MW_LOG_WARNING, MW_LOC_SECURITY_WARNING);
	MW_LOG(MW_LOG_INFO, MW_LOC_LICENSE_AND_CREDITS);

	MW_LOG(MW_LOG_INFO, "Entering client loop");

	while(g_client_running){

		if(g_current_state == NULL){

			MW_LOG(MW_LOG_ERROR, "g_current_state is a nullptr! Calling cleanup function");
			mw_state_cleanup(argc, argv);			

			MW_LOG(MW_LOG_ERROR, "mw_state_cleanup did not exit! Calling exit()");
			exit(EXIT_FAILURE);

		}
		else{
			g_current_state(argc, argv);
		}

	}

	MW_LOG(MW_LOG_ERROR, "Abnormal client exit");
	exit(EXIT_FAILURE);

}
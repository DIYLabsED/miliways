#include <enet/enet.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "server/server_config.h"
#include "server/server_state.h"
#include "shared/loc.h"
#include "shared/log.h"
#include "shared/arg.h"
#include "shared/reslist.h"


mw_server_global g_server_global;
mw_server_state_func g_current_state = mw_state_setup;
bool g_server_running = true;


int main(int argc, char **argv){

	MW_LOG(MW_LOG_INFO, MW_LOC_LICENSE_AND_CREDITS);
	MW_LOG(MW_LOG_WARNING, MW_LOC_SECURITY_WARNING);
	
	if(mw_arg_exists(argc, argv, "--risk") == -1){
		if(!mw_arg_prompt_n(MW_LOC_SECURITY_PROMPT)){
			printf(MW_LOC_SECURITY_PROMPT_RESPONSE);
			exit(EXIT_SUCCESS);
		}
	}

	MW_LOG(MW_LOG_INFO, "Entering server loop");

	while(g_server_running){

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

	MW_LOG(MW_LOG_ERROR, "Abnormal server exit");
	exit(EXIT_FAILURE);

}
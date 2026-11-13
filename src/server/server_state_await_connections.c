#include "server/server_state.h"
#include "server/server_networking.h"
#include "shared/log.h"	

void mw_state_await_connections(int argc, char **argv){

	MW_LOG(MW_LOG_INFO, "Awaiting client connections");

	while(1){
		mw_server_service_events(10);
	}

}
#include <stdio.h>

#include "shared/loc.h"
#include "shared/log.h"
#include "shared/reslist.h"

#include <server/server_ui.h>


int main(void){

	MW_LOG(MW_LOG_WARNING, MW_LOC_SECURITY_WARNING);
	MW_LOG(MW_LOG_INFO, MW_LOC_LICENSE_AND_CREDITS);

	mw_server_ui_init();

	while(1){
		mw_server_ui_update();
	}

	mw_server_ui_deinit();

	return 0;

}
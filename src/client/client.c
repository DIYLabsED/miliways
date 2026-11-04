#include <stdio.h>

#include <enet/enet.h>

#include "shared/loc.h"
#include "shared/log.h"

int main(void){

	printf(MW_LOC_SECURITY_WARNING);
	printf(MW_LOC_LICENSE_AND_CREDITS);
	
	MW_LOG(MW_LOG_INFO, "hello, world!");
	MW_LOG(MW_LOG_ERROR, "hello, world!");

	return 0;

}
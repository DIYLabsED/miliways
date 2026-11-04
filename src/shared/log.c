#include <stdio.h>
#include <stdlib.h>

#include "shared/log.h"


char *mw_get_str_from_log_level(enum mw_log_level lvl){

	switch(lvl){

		case MW_LOG_INFO:
			return "INF";

		case MW_LOG_WARNING:
			return "WRN";

		case MW_LOG_ERROR:
			return "ERR";

		case MW_LOG_DEBUG:
			return "DBG";

		default:
			return "???";

	}

	return "???";

}

void mw_log(enum mw_log_level lvl, const char *msg, char *file, int line){

	const char *fmt = "[%s] (%s at line %d): %s\n";
	const char *lvl_c = mw_get_str_from_log_level(lvl);
	
	int size = snprintf(NULL, 0, fmt, lvl_c, file, line, msg);
	char *log = malloc(size + 1);
	sprintf(log, fmt, lvl_c, file, line, msg);

	if(lvl == MW_LOG_ERROR){
		fprintf(stderr, log);
	}
	else{
		fprintf(stdout, log);
	}

}
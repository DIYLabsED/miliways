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

char *mw_get_ansi_color_from_log_level(enum mw_log_level lvl){

	switch(lvl){

		case MW_LOG_INFO:
			return MW_ANSI_CC_GREEN;

		case MW_LOG_WARNING:
			return MW_ANSI_CC_YELLOW;

		case MW_LOG_ERROR:
			return MW_ANSI_CC_RED;

		case MW_LOG_DEBUG:
			return MW_ANSI_CC_BLUE;

		default:
			return "";

	}

	return "";

}

void mw_log(enum mw_log_level lvl, const char *msg, char *file, int line){

	const char *fmt = "[%s%s%s] (%s at line %d): %s\n";
	const char *lvl_c = mw_get_str_from_log_level(lvl);
	
	int size = snprintf(NULL, 0, fmt, mw_get_ansi_color_from_log_level(lvl), lvl_c, MW_ANSI_CC_RESET, file, line, msg);
	char *log = malloc(size + 1);
	sprintf(log, fmt, mw_get_ansi_color_from_log_level(lvl), lvl_c, MW_ANSI_CC_RESET, file, line, msg);

	if(lvl == MW_LOG_ERROR){
		fprintf(stderr, "%s", log);
	}
	else{
		fprintf(stdout, "%s", log);
	}

}
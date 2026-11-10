#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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

void mw_log(enum mw_log_level lvl, char *file, int line, const char *fmt, ...){

	va_list args;
	va_start(args, fmt);

	va_list args_cpy;
	va_copy(args_cpy, args);
	int msg_size = vsnprintf(NULL, 0, fmt, args_cpy);
	va_end(args_cpy);

	char *msg = malloc(msg_size + 1);

	vsnprintf(msg, msg_size + 1, fmt, args);
	va_end(args);

	const char *log_fmt = "[%s%s%s] %s(%s at line %d):%s %s\n";
	const char *lvl_str = mw_get_str_from_log_level(lvl);
	const char *clr = mw_get_ansi_color_from_log_level(lvl);

	int total_size = snprintf(NULL, 0, log_fmt, clr, lvl_str, MW_ANSI_RESET, MW_ANSI_FM_ITALIC, file, line, MW_ANSI_RESET, msg);

	char *log = malloc(total_size + 1);
	sprintf(log, log_fmt, clr, lvl_str, MW_ANSI_RESET, MW_ANSI_FM_ITALIC, file, line, MW_ANSI_RESET, msg);

	if(lvl == MW_LOG_ERROR){
		fprintf(stderr, "%s", log);
	}
	else{
		fprintf(stdout, "%s", log);		
	}

	free(msg);
	free(log);

}
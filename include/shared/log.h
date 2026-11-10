/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/shared/log.h
	Basic logging function

*/ 

#pragma once

#define MW_LOG(lvl, fmt, ...) mw_log(lvl, __FILE__, __LINE__, fmt, ##__VA_ARGS__);	// ##__VA_ARGS__ handles trailing comma if you call w/ no fmt args

#define MW_ANSI_CC_RED			"\x1b[31m"
#define MW_ANSI_CC_GREEN		"\x1b[32m"
#define MW_ANSI_CC_YELLOW		"\x1b[33m"
#define MW_ANSI_CC_BLUE			"\x1b[34m"
#define MW_ANSI_CC_MAGENTA		"\x1b[35m"
#define MW_ANSI_CC_CYAN			"\x1b[36m"
#define MW_ANSI_FM_ITALIC 		"\x1b[3m"
#define MW_ANSI_RESET		"\x1b[0m"


enum mw_log_level{
	MW_LOG_INFO,
	MW_LOG_WARNING,
	MW_LOG_ERROR,
	MW_LOG_DEBUG
};

char *mw_get_str_from_log_level(enum mw_log_level lvl);
char *mw_get_ansi_color_from_log_level(enum mw_log_level lv);
void mw_log(enum mw_log_level lvl, char *file, int line, const char *fmt, ...);
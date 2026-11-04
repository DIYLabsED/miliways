/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/shared/log.h
	Basic logging function

*/ 

#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MW_LOG(lvl, msg) mw_log(lvl, msg, __FILE__, __LINE__);

enum mw_log_level{
	MW_LOG_INFO,
	MW_LOG_WARNING,
	MW_LOG_ERROR,
	MW_LOG_DEBUG
};

char *mw_get_str_from_log_level(enum mw_log_level lvl);
void mw_log(enum mw_log_level lvl, char *msg, char *file, int line);
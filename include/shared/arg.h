/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/shared/packet.h
	Argument parsing utility

*/ 

#pragma once

#include <stdbool.h>

int 		mw_arg_exists(int argc, char **argv, char *arg);
long long 	mw_arg_get_ll(int argc, char **argv, char *arg, long long fb);
double 		mw_arg_get_d(int argc, char **argv, char *arg, double fb);
bool 		mw_arg_get_bool(int argc, char **argv, char *arg, bool fb);
char *		mw_arg_get_str(int argc, char **argv, char *arg, char *fb);
bool 		mw_arg_prompt_n(char *msg);
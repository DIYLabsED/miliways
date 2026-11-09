#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "shared/arg.h"


int mw_arg_exists(int argc, char **argv, char *arg){

	if(arg == NULL) return -1;

	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], arg) == 0) return i;
	}

	return -1;

}

long long mw_arg_get_ll(int argc, char **argv, char *arg, long long fb){

	int idx = mw_arg_exists(argc, argv, arg);
	if(idx == -1 || idx + 1 >= argc) return fb;

	return atoll(argv[idx + 1]);

}

double mw_arg_get_d(int argc, char **argv, char *arg, double fb){

	int idx = mw_arg_exists(argc, argv, arg);
	if(idx == -1 || idx + 1 >= argc) return fb;

	return atof(argv[idx + 1]);

}

bool mw_arg_get_bool(int argc, char **argv, char *arg, bool fb){

	int idx = mw_arg_exists(argc, argv, arg);
	if(idx == -1 || idx + 1 >= argc) return fb;

	char *str = argv[idx + 1];

	if(strcmp(str, "1") == 0) return true;
	if(strcmp(str, "0") == 0) return false;

	if(strcasecmp(str, "true") == 0) return true;
	if(strcasecmp(str, "false") == 0) return false;	

	return fb;

}

char *mw_arg_get_str(int argc, char **argv, char *arg, char *fb){

	int idx = mw_arg_exists(argc, argv, arg);
	if(idx == -1 || idx + 1 >= argc) return fb;

	return argv[idx + 1];

}
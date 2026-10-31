#define NOB_IMPLEMENTATION
#include "nob.h"

#define BUILD_DIR 				"build/"
#define CL_BUILD_SUBDIR 		"client/"
#define SV_BUILD_SUBDIR 		"server/"

#define SV_EXE_NAME 		"miliways-sv"
#define CL_EXE_NAME			"miliways-cl"

#define CL_SRC_DIR 			"src/client"
#define SV_SRC_DIR 			"src/server"
#define SHARED_SRC_DIR 		"src/shared"

#define INCLUDE_DIR			"include"

#define GCC_ENABLE_ALL_WARNINGS_AND_WHINE_ABOUT_THEM "-Wall", "-Wextra", "-Wpedantic", "-Werror"

static Nob_File_Paths *scanDA = NULL;
static bool walk_callback(Nob_Walk_Entry entry){

	if(entry.type == NOB_FILE_REGULAR){
		Nob_String_View sv = nob_sv_from_cstr(entry.path);
		if(nob_sv_ends_with(sv, nob_sv_from_cstr(".c"))){
			nob_da_append(scanDA, nob_temp_strdup(entry.path));
		}
	}

	return true;

}

int main(int argc, char **argv){

	// Rebuild nob if needed
	NOB_GO_REBUILD_URSELF(argc, argv);

	// Ensure build dirs exist
	if(!nob_mkdir_if_not_exists(BUILD_DIR)) return 1;
	if(!nob_mkdir_if_not_exists(BUILD_DIR CL_BUILD_SUBDIR)) return 1;
	if(!nob_mkdir_if_not_exists(BUILD_DIR SV_BUILD_SUBDIR)) return 1;

	// Get all source files
	Nob_File_Paths sv_src_files		= {0};
	Nob_File_Paths cl_src_files 	= {0};
	Nob_File_Paths shared_src_files = {0};

	scanDA = &sv_src_files;
	nob_walk_dir(SV_SRC_DIR, walk_callback);

	scanDA = &cl_src_files;
	nob_walk_dir(CL_SRC_DIR, walk_callback);

	scanDA = &shared_src_files;
	nob_walk_dir(SHARED_SRC_DIR, walk_callback);

	nob_log(NOB_INFO, "Found the following server source files:");
	for(size_t i = 0; i < sv_src_files.count; i++){
		nob_log(NOB_INFO, "%s", sv_src_files.items[i]);
	}

	nob_log(NOB_INFO, "Found the following client source files:");
	for(size_t i = 0; i < cl_src_files.count; i++){
		nob_log(NOB_INFO, "%s", cl_src_files.items[i]);
	}

	nob_log(NOB_INFO, "Found the following shared source files:");
	for(size_t i = 0; i < shared_src_files.count; i++){
		nob_log(NOB_INFO, "%s,", shared_src_files.items[i]);
	}

	// Build server compile command
	Nob_Cmd sv_build_cmd = {0};
	nob_cmd_append(&sv_build_cmd, "gcc", GCC_ENABLE_ALL_WARNINGS_AND_WHINE_ABOUT_THEM, "-O3", "-I" INCLUDE_DIR, "-o" BUILD_DIR SV_BUILD_SUBDIR SV_EXE_NAME);

	for(size_t i = 0; i < sv_src_files.count; i++){
		nob_cmd_append(&sv_build_cmd, sv_src_files.items[i]);
	}	

	for(size_t i = 0; i < shared_src_files.count; i++){
		nob_cmd_append(&sv_build_cmd, shared_src_files.items[i]);
	}	

	// Build client compile command
	Nob_Cmd cl_build_cmd = {0};
	nob_cmd_append(&cl_build_cmd, "gcc", GCC_ENABLE_ALL_WARNINGS_AND_WHINE_ABOUT_THEM, "-O3", "-I" INCLUDE_DIR, "-o" BUILD_DIR CL_BUILD_SUBDIR CL_EXE_NAME);
	
	for(size_t i = 0; i < cl_src_files.count; i++){
		nob_cmd_append(&cl_build_cmd, cl_src_files.items[i]);
	}	

	for(size_t i = 0; i < shared_src_files.count; i++){
		nob_cmd_append(&cl_build_cmd, shared_src_files.items[i]);
	}	

	// Compile!
	if(!nob_cmd_run(&sv_build_cmd)) return 1;
	if(!nob_cmd_run(&cl_build_cmd)) return 1;

	// Note: sv_build_cmd and cl_build_cmd are now reset, doesn't matter but set dont_reset to true to avoid this if needed

	return 0;

}
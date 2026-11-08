#include <raylib.h>
#include "shared/raygui.h"

#include <shared/log.h>
#include <shared/loc.h>
#include <shared/reslist.h>


void mw_server_ui_init(){

	InitWindow(500, 500, MW_LOC_SERVER_WINDOW_TITLE);

}

void mw_server_ui_update(){

}

void mw_server_ui_deinit(){

	CloseWindow();

}
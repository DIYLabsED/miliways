/*	Miliways
	This file is licensed under the MIT license. See LICENSE in the root of this repo for the license text.

	include/shared/loc.h
	A poor man's localization system, that only supports one language, but at least it avoid hardcoding strings.

*/ 

#pragma once

const char *MW_LOC_SECURITY_WARNING = 
"\n"
"Warning!\n"
"\n"
"This code was written without much care for safety.\n"
"And it connects to the Internet.\n"
"And blindly trusts the game server/client it talks to.\n"
"\n"
"This is a standard no-bake gluten-free recipe for a whole host of potential security vulnerabilities!\n"
"MAKE ABSOLUTELY SURE YOU TRUST THE SERVER OR CLIENT YOU ARE TALKING WITH!\n"
"\n"
"In addition, other things you could do are:\n"
"- run this in a sandbox to limit read/write access to files\n"
"- set up your firewall so the only thing this can talk to is the game server or client (which you trust)\n"
"\n"
;

const char *MW_LOC_LICENSE_AND_CREDITS = 
"\n"
"Miliways is licensed under the MIT license.\n"
"The source code is available at https://github.com/DIYLabsED/miliways/\n"
"\n"
"Miliways uses the following third-party libraries:\n"
"1. Raylib by Ramon Santamaria (raysan5), licensed under the Zlib license.\n"
"2. ENet by Lee Salzman (lsalzman), licensed under the MIT license.\n"
"3. nob.h by Alexey Kutepov (rexim/Tsoding), licensed under the MIT license."
"\n"
;
#pragma once

#include "Utility/CommandParse.h"
#include "IO/IO.h"

#include <string>

namespace x69::cmd
{

	// prints pong
	int ping(const CommandArgs& _args);

	// clears screen
	int clear(const CommandArgs& _args);

	// exits terminal
	int exit(const CommandArgs& _args);

	// prints current directory and contents
	int ls(const CommandArgs& _args);

	// sets current directory relative to the current path
	int cd(const CommandArgs& _args);

	//	ShellApp printout and manipulation
	//	
	//	app								- prints summary and note of app help command
	//	app help						- prints list of app commands
	//	app list						- prints all registered shell apps
	//	app <appname>					- runs a shell app
	//
	int app(const CommandArgs& _args);


	//
	//	Sets terminal window size
	//		ssize <width> <height>
	int ssize(const CommandArgs& _args);





};

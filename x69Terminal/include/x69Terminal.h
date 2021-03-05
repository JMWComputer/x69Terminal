#pragma once
#ifndef X69TERMINAL_H
#define X69TERMINAL_H

struct jcTerminal;

#include <filesystem>

namespace x69
{
	struct TerminalConfig
	{
		std::filesystem::path font;
	};



	bool start_terminal(TerminalConfig _config);
	bool is_terminal_open();
	void shutdown_terminal();

	bool update_terminal();




};

#endif
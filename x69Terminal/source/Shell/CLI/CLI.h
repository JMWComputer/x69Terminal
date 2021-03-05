#pragma once

struct jcTerminal;

#include <jclib/functor.h>

#include <string>

namespace x69::tmnl
{
	struct Region;
};

namespace x69::cli
{
	using CommandCallback = jc::functor<void(const std::string&)>;

	void update_cli();

	void clear_all();

	void clear_terminal_output();

	void write(const std::string& _ln);

	void set_command_callback(CommandCallback _cb);

	void append_input(char c);
	
	void set_cli_region(const tmnl::Region& _region);

	bool start_cli(jcTerminal* _tmnl);
	void shutdown_cli();

}
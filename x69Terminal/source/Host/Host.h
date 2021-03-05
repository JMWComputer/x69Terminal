#pragma once

struct jcTerminal;


namespace x69
{
	namespace impl
	{
		extern jcTerminal* terminal_v;
	};

	void set_terminal(jcTerminal* _terminal);
	jcTerminal*& terminal();

	bool keep_terminal_open();
	void set_terminal_keep_open_flag(bool _to);


	class Shell;

	bool start_shell();
	Shell& shell();



};

#include <x69Terminal.h>
#include <c/JCTerminal.h>

#include "Host/Host.h"
#include "Shell/Shell.h"
#include "Process/Process.h"

#include "Apps/Emulator/Emulator.h"

#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace x69
{
	namespace impl
	{
		extern inline TerminalConfig terminal_config_v{};
	};

	namespace
	{
		constexpr inline int terminal_cells_x = 128;
		constexpr inline int terminal_cells_y = 48;
		
		constexpr inline int terminal_cell_width = 11;
		constexpr inline int terminal_cell_height = 18;

	};

	extern inline std::ifstream fin{ SOURCE_ROOT "/fin.txt" };
	extern inline std::ofstream fout{ SOURCE_ROOT "/fout.txt" };





	void redirect_stdio()
	{
		std::cin.tie(nullptr);
		std::cin.rdbuf(fin.rdbuf());
		std::cout.rdbuf(fout.rdbuf());
	};

	void tclose_callback(jcTerminal* _terminal)
	{
		set_terminal_keep_open_flag(false);
	};

	bool start_terminal(TerminalConfig _config)
	{
		assert(!is_terminal_open());

		auto& _tmnl = terminal();
		_tmnl = jcTerminalOpen(terminal_cells_x, terminal_cells_y, "x69");
		bool _goodOpen = (_tmnl != nullptr);
		char _userInput = 0;

		auto _goodShell = start_shell();
		if (!_goodShell)
		{
			return _goodShell;
		};

		redirect_stdio();

		if (_goodOpen)
		{
			auto& _tcon = impl::terminal_config_v;
			_tcon = _config;

			jcTerminalSetCellSize(_tmnl, terminal_cell_width, terminal_cell_height);
			jcTerminalLoadFont(_tmnl, _tcon.font.string().c_str(), 0, 256);

			jcTerminalPrintString(_tmnl, 0, 0, "Welcome, Retard");

			jcTerminalSetCloseCallback(_tmnl, tclose_callback);
			set_terminal_keep_open_flag(true);

			jcTerminalRefresh(_tmnl);

		};


		//std::cout.flush();
		//std::filesystem::path _otherExe{ std::filesystem::current_path() };
		//_otherExe.append("x69Terminalother.exe");
		//assert(std::filesystem::exists(_otherExe));
		//std::cout << _otherExe << '\n';
		//launch_process(_otherExe);
		//std::cout.flush();

		return _goodOpen;
	};
	bool is_terminal_open()
	{
		return keep_terminal_open();
	};
	void shutdown_terminal()
	{
		if (is_terminal_open())
		{
			auto& _tmnl = terminal();
			jcTerminalClose(&_tmnl);
			_tmnl = nullptr;
		};
	};

	bool update_terminal()
	{
		if (is_terminal_open())
		{
			auto& _tmnl = terminal();
			jcTerminalDrawUntilEvent(_tmnl);
		};
		shell().update();
		return is_terminal_open();
	};

};

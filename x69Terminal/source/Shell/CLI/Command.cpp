#include "Command.h"

#include "Host/Host.h"
#include "Command.h"

#include "Shell/Shell.h"
#include "Shell/ShellApp.h"

#include "IO/IO.h"

#include "CLI.h"

#include "Apps/Emulator/Emulator.h"

#include <c/JCTerminal.h>

#include <filesystem>

namespace x69::cmd
{
	namespace fs = std::filesystem;

	int ping(const CommandArgs& _args)
	{
		cli::write("pong");
		return 0;
	};

	// clears screen
	int clear(const CommandArgs& _args)
	{
		cli::clear_terminal_output();
		return 0;
	};

	// exits terminal
	int exit(const CommandArgs& _args)
	{
		auto& _tmnl = terminal();
		cli::write("cya bitch");
		set_terminal_keep_open_flag(false);
		return 0;
	};

	// prints current directory and contents
	int ls(const CommandArgs& _args)
	{
		auto& _tmnl = terminal();
		
		namespace fs = std::filesystem;
		auto _here = fs::current_path();

		std::string _str{ "\t@" + _here.string() + "\n" };
		_str.reserve(_str.size() + 256);
		for (auto& p : fs::directory_iterator{ _here })
		{
			_str.append(p.path().filename().string());
			_str.push_back('\n');
		};
		cli::write(_str);

		return 0;
	};




	int ssize(const CommandArgs& _args)
	{
		if (_args.size() < 3)
		{
			cli::write("\tUsage : ssize <width> <height>");
			return 0;
		};

		auto _w = std::stoi(std::string{ _args[1] });
		auto _h = std::stoi(std::string{ _args[2] });

		auto& _tmnl = terminal();
		jcTerminalSetWindowSize(_tmnl, _w, _h);

	};


	namespace
	{
		constexpr inline std::string_view appList = "list";
		constexpr inline std::string_view appHelp = "help";

	};

	int app(const CommandArgs& _args)
	{
		if (_args.size() <= 1)
		{
			// print summary and notice of app help

		}
		else if (_args[1] == appList)
		{
			// print list of all registered shell apps

			auto _saps = get_registered_shell_apps();
			std::stringstream _str{};
		
			_str << "\temulator\n";

			cli::write(_str.str());

		}
		else if (_args[1] == appHelp)
		{
			// print list of all registered shell apps

			std::string _str{};

			_str.append("Shell app managament functionality. These are NOT executables.\n");
			_str.append("\tapp help\n\t\tprints app command documentation\n");
			_str.append("\tapp list\n\t\tprints list of registered shell apps\n");
			_str.append("\tapp <name>\n\t\truns app with <name> if registered\n");

			cli::write(_str);
		}
		else if( _args[1] == "emulator" )
		{
			auto& _sh = shell();
			cli::write("\tlaunching emulator...");
			_sh.run_app(std::unique_ptr<app::Emulator>{ new app::Emulator{} });
		}
		else
		{
			cli::write("unknown command, use 'app help' for help");
		};

		return 0;
	};

	int cd(const CommandArgs& _args)
	{
		auto _here = fs::current_path();
		if (_args.size() < 2) 
		{ 
			cli::write("\t" + _here.string());
			return 0;
		};

		_here.append(_args[1]);
		fs::current_path(_here);
		cli::write("\t" + _here.string());

		return 0;
	};




};


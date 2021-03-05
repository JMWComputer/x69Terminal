#pragma once

#include "ShellApp.h"

#include <jclib/functor.h>

#include <string>
#include <istream>
#include <ostream>
#include <unordered_map>
#include <string_view>

namespace x69
{
	using ShellCommand = jc::functor<int(const std::vector<std::string_view>& _args)>;

	class Shell
	{
	private:
		bool cli_running_flag_ = false;

		bool is_cli_running();
		void start_cli();
		void shutdown_cli();

	public:

		void run_command(const std::vector<std::string_view>& _command);
		void run_command(const std::string& _command);

		void insert(const std::string& _command, const ShellCommand& _callback);
		void erase_command(const std::string& _command);


		bool run_app(std::unique_ptr<ShellApp> _app);
		void shutdown_app();

		void update();

		Shell();

	private:
		std::unordered_map<std::string, ShellCommand> commands_{};
		std::unique_ptr<ShellApp> app_;
		
		std::istream sin;
		std::ostream sout;

	};

	

};

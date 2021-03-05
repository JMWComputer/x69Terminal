#include "Shell.h"

#include "Host/Host.h"
#include "Utility/CommandParse.h"
#include "IO/IO.h"

#include "CLI/CLI.h"
#include "CLI/Command.h"

#include <iostream>
#include <cassert>

namespace x69
{

	bool Shell::is_cli_running()
	{
		return this->cli_running_flag_;
	};
	void Shell::start_cli()
	{
		if (!this->is_cli_running())
		{
			cli::set_command_callback({ &Shell::run_command, this });

			this->insert("ping", cmd::ping);
			this->insert("clr", cmd::clear);
			this->insert("exit", cmd::exit);
			this->insert("ls", cmd::ls);
			this->insert("dir", cmd::ls);
			this->insert("app", cmd::app);
			this->insert("cd", cmd::cd);
			this->insert("ssize", cmd::ssize);

			cli::start_cli(terminal());
			this->cli_running_flag_ = true;
		};
	};
	void Shell::shutdown_cli()
	{
		if (this->is_cli_running())
		{
			cli::set_command_callback(nullptr);
			cli::shutdown_cli();
			this->cli_running_flag_ = false;
		};
	};

	void Shell::run_command(const std::vector<std::string_view>& _command)
	{
		assert(!_command.empty());
		auto _it = this->commands_.find(std::string{ _command.front() });
		if (_it != this->commands_.end())
		{
			auto& _callback = _it->second;
			assert(_callback);
			auto _result = std::invoke(_callback, _command);
			assert(_result == 0);
		};
	};
	void Shell::run_command(const std::string& _command)
	{
		auto _tokens = parse_command(_command);
		this->run_command(_tokens);
	};

	void Shell::insert(const std::string& _command, const ShellCommand& _callback)
	{
		this->commands_.insert_or_assign(_command, _callback);
	};
	void Shell::erase_command(const std::string& _command)
	{
		this->commands_.erase(_command);
	};


	bool Shell::run_app(std::unique_ptr<ShellApp> _app)
	{
		this->shutdown_cli();
		assert(_app);
		if (this->app_)
		{
			this->app_->shutdown();
		};
		this->app_ = std::move(_app);
		return this->app_->start();
	};
	void Shell::shutdown_app()
	{
		if (this->app_)
		{
			this->app_->shutdown();
		};
		this->app_.reset();
		this->start_cli();
	};

	void Shell::update()
	{
		if (this->is_cli_running())
		{
			cli::update_cli();
		};
		if (this->app_)
		{
			this->app_->update();
		};
	};

	Shell::Shell() :
		sin{ io::sout.rdbuf() },
		sout{ io::sin.rdbuf() }
	{
		this->start_cli();
	};

}
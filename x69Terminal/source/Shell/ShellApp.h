#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <string_view>
#include <optional>

namespace x69
{
	class ShellAppFactory;
	class ShellApp;

	class ShellApp
	{
	public:
		const auto& name() const noexcept { return this->name_; };

		virtual bool start() = 0;
		virtual void shutdown() = 0;
		virtual void update() = 0;
		virtual void run_command(const std::vector<std::string_view>& _args) {};

		virtual ~ShellApp() = default;

	protected:
		ShellApp(const std::string& _name);

	private:
		const std::string name_;
	};

	class ShellAppFactory
	{
	public:
		static ShellApp* make(const std::string& _appName, const std::vector<std::string>& _args);
		virtual ~ShellAppFactory() = default;
	protected:
		virtual ShellApp* make_app(const std::vector<std::string>& _args) = 0;
		ShellAppFactory(const std::string& _appName);
	private:
		std::string name_ = "";
	};

	std::vector<std::string> get_registered_shell_apps();

};

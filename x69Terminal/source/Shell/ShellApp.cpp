#include "ShellApp.h"

#include <jclib/singleton.h>

#include <cassert>

namespace x69
{

	using AppFactoryLedger = std::unordered_map<std::string, ShellAppFactory*>;
	inline auto& get_apf_ledger()
	{
		return jc::get_singleton<AppFactoryLedger>();
	};

	ShellApp* ShellAppFactory::make(const std::string& _appName, const std::vector<std::string>& _args)
	{
		auto& _apl = get_apf_ledger();
		if (_apl.contains(_appName))
		{
			return _apl.at(_appName)->make_app(_args);
		}
		else
		{
			return nullptr;
		};
	};
	ShellAppFactory::ShellAppFactory(const std::string& _appName) :
		name_{ _appName }
	{
		auto& _apl = get_apf_ledger();
		assert(!_apl.contains(_appName));
		_apl.insert({ _appName, this });


	};



	ShellApp::ShellApp(const std::string& _name) :
		name_{ _name }
	{};


	std::vector<std::string> get_registered_shell_apps()
	{
		auto& _apl = get_apf_ledger();
		std::vector<std::string> _out{};
		_out.reserve(_apl.size());
		for (auto& a : _apl)
		{
			_out.push_back(a.first);
		};
		return _out;
	};

};


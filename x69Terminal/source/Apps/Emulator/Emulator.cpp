#include "Emulator.h"

#include "Host/Host.h"
#include "IO/IO.h"

#include "Shell/CLI/CLI.h"
#include "Utility/CommandParse.h"

#include "Shell/Shell.h"

#include <x69Emulator.h>

#include <cassert>
#include <filesystem>

namespace x69::app
{
	bool Emulator::start()
	{
		this->emu_ = emu::new_emulator();
		
		auto _good = emu::load_program(this->emu_, SOURCE_ROOT "/fibbo.o");
		assert(_good);

		cli::start_cli(terminal());
		cli::clear_terminal_output();
		cli::set_command_callback({ &Emulator::run_command, this });
		
		
		const auto _treg = tmnl::terminal_region(terminal());
		const auto _ereg = this->registers_.region();

		tmnl::Region _cliReg{ _treg };
		_cliReg.yMin = _ereg.yMax + 1;
		_cliReg.xMax = _cliReg.xMax / 2;
		cli::set_cli_region(_cliReg);

		return true;
	};
	void Emulator::shutdown()
	{
		emu::destroy_emulator(this->emu_);


		cli::set_command_callback(nullptr);
		cli::shutdown_cli();

	};
	
	void Emulator::draw_registers()
	{

		auto& _tmnl = terminal();
		tmnl::clear(_tmnl, this->registers_.region());

		this->registers_.reset();
		tmnl::fill(_tmnl, this->registers_.region(), {}, this->register_bg_color_);

		auto _regs = emu::get_all_cpu_registers(this->emu_);
		auto& _crsr = this->registers_;
		int _rcounter = 0;
		std::string _str{};

		//io::TerminalWriter _twrite{ _crsr };

		const auto _regColor = tmnl::TextColor
		{
			this->rname_color_,
			this->register_bg_color_
		};
		const auto _valColor = tmnl::TextColor
		{
			this->rvalue_color_,
			this->register_bg_color_
		};
		
		for (auto& r : _regs)
		{
			tmnl::set_color(_tmnl, _regColor);
			_str.push_back('r');
			_str.append(std::to_string(_rcounter++));
			_str.append(" : ");
			tmnl::print(_tmnl, _crsr, _str);
			_str.clear();

			tmnl::set_color(_tmnl, _valColor);
			_str.append(std::to_string(r));
			tmnl::print(_tmnl, _crsr, _str);
			_str.clear();

			_crsr.at().x = _crsr.begin().x;
			++_crsr.at().y;
		};



		const auto _sregColor = tmnl::TextColor
		{
			this->special_rname_color_,
			this->register_bg_color_
		};
		
		const auto _sregs = emu::get_all_special_registers(this->emu_);

		_str.clear();

		tmnl::set_color(_tmnl, _sregColor);
		tmnl::print(_tmnl, _crsr, "PC : ");
		tmnl::set_color(_tmnl, _valColor);
		tmnl::print(_tmnl, _crsr, std::to_string(_sregs[0]));
		_crsr.next_line();

		tmnl::set_color(_tmnl, _sregColor);
		tmnl::print(_tmnl, _crsr, "LR : ");
		tmnl::set_color(_tmnl, _valColor);
		tmnl::print(_tmnl, _crsr, std::to_string(_sregs[1]));
		_crsr.next_line();

		tmnl::set_color(_tmnl, _sregColor);
		tmnl::print(_tmnl, _crsr, "SP : ");
		tmnl::set_color(_tmnl, _valColor);
		tmnl::print(_tmnl, _crsr, std::to_string(_sregs[2]));
		_crsr.next_line();

		tmnl::set_color(_tmnl, _sregColor);
		tmnl::print(_tmnl, _crsr, "ADDR : ");
		tmnl::set_color(_tmnl, _valColor);
		tmnl::print(_tmnl, _crsr, std::to_string(_sregs[3]));
		_crsr.next_line();
	};



	void Emulator::cmd_clear(const CmdArgs& _args)
	{
		cli::clear_terminal_output();
	};
	void Emulator::cmd_exit(const CmdArgs& _args)
	{
		shell().shutdown_app();
	};

	void Emulator::cmd_stop(const CmdArgs& _args)
	{
		this->auto_step_ = false;
	};
	void Emulator::cmd_start(const CmdArgs& _args)
	{
		this->auto_step_ = true;
	};
	void Emulator::cmd_step(const CmdArgs& _args)
	{
		emu::step(this->emu_);
	};

	void Emulator::cmd_reset(const CmdArgs& _args)
	{
		emu::destroy_emulator(this->emu_);
		this->emu_ = emu::new_emulator();
	};
	void Emulator::cmd_load(const CmdArgs& _args)
	{
		if (_args.size() < 2)
		{
			assert(false);
			return;
		}
		else
		{
			auto _path = std::filesystem::current_path();
			_path.append(_args[1]);
			auto _result = emu::load_program(this->emu_, _path);
			assert(_result);
		};
	};


	void Emulator::run_command(const std::string& _str)
	{
		auto _tkns = parse_command(_str);
		auto _it = this->command_list_.find(std::string{ _tkns.front() });
		if (_it != this->command_list_.end())
		{
			_it->second.invoke(_tkns);
		};
	};

	void Emulator::update()
	{
		tmnl::clear(terminal(), tmnl::terminal_region(terminal()));

		cli::clear_all();
		cli::update_cli();

		this->draw_registers();

		if (this->auto_step_)
		{
			emu::step(this->emu_);
		};

		jcTerminalRefresh(terminal());
	};

	Emulator::Emulator() :
		ShellApp{ "emulator" }
	{
		const auto _treg = tmnl::terminal_region(terminal());
	
		auto _regRegion = _treg;
		_regRegion.xMax = _regRegion.xMin + 10;
		_regRegion.yMax = _regRegion.yMin + 25;
		this->registers_ = tmnl::Cursor{ _regRegion };

	};

	Emulator::~Emulator()
	{};

};

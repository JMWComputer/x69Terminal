#pragma once

#include "Shell/ShellApp.h"

#include "Terminal/Draw.h"

#include <jclib/functor.h>

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

namespace x69::emu
{
	struct Emulator;
};

namespace x69::app
{

	class Emulator : public ShellApp
	{
	public:

		bool start() override;
		void shutdown() override;
		void update() override;

		void run_command(const std::string& _str);

		Emulator();
		~Emulator();


	protected:
		using CmdArgs = const std::vector<std::string_view>&;
	
		// CLI related commands
		void cmd_clear(const CmdArgs& _args);	// Clears CLI
		void cmd_exit(const CmdArgs& _args);	// Exits emulator app

		// Clock related
		void cmd_stop(const CmdArgs& _args);	// stops PC auto stepper
		void cmd_start(const CmdArgs& _args);	// starts PC auto stepper
		void cmd_step(const CmdArgs& _args);	// steps PC forward

		// State related
		void cmd_reset(const CmdArgs& _args); // resets emulator to initial state
		void cmd_load(const CmdArgs& _args);  // loads a program into the emulator


	private:
		const std::unordered_map<std::string, jc::functor<void(const CmdArgs&)>> command_list_
		{
			{ "clr", { &Emulator::cmd_clear, this } },
			{ "exit", { &Emulator::cmd_exit, this } },

			{ "stop", { &Emulator::cmd_stop, this } },
			{ "start", { &Emulator::cmd_start, this } },
			{ "step", { &Emulator::cmd_step, this } },

			{ "reset", { &Emulator::cmd_reset, this } }

		};
		
		void draw_registers();


		bool auto_step_ = false;

		emu::Emulator* emu_ = nullptr;
		
		tmnl::Cursor registers_;
		
		jcTerminal_Color rname_color_{ 200, 80, 80, 255 };
		jcTerminal_Color special_rname_color_{ 57, 255, 20, 255 };
		jcTerminal_Color rvalue_color_{ 200, 200, 200, 255 };
		jcTerminal_Color register_bg_color_{ 25, 25, 25, 255 };




		struct Factory : public ShellAppFactory 
		{
		public:
			Factory() :
				ShellAppFactory{ "emulator" }
			{};
		protected: 
			ShellApp* make_app(const std::vector<std::string>& _args) override 
			{ 
				return new Emulator{  };
			};
		};
		const static inline Factory factory_v{};

	};

};

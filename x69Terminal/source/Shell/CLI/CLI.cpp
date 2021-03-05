#include "CLI.h"

#include "Host/Host.h"

#include "Terminal/Draw.h"
#include "Terminal/Region.h"

#include "Shell/Shell.h"

#include <c/JCTerminal.h>

#include <jclib/singleton.h>
#include <jclib/parse.h>

#include <string>
#include <vector>
#include <list>

namespace x69::cli
{
	struct CLISettings
	{
		jcTerminal_Color input_color{ 0, 255, 0, 255 };
		jcTerminal_Color input_background_color{ 25, 25, 25, 255 };
		jcTerminal_Color output_color{ 200, 200, 200, 255 };
		jcTerminal_Color output_background_color{ 0, 0, 0, 255 };

		std::string input_prefix = ">";

	};
	struct CLIData
	{
		CLISettings settings{};
		std::vector<std::string> lines;
		std::list<std::string> history{};
		tmnl::Cursor cursor{};

		std::string input = "";
		CommandCallback callback{};

	};

	auto& get_cli() { return jc::get_singleton<CLIData, struct x69CLITag>(); };
	
	void reset_cursor()
	{
		auto& _cli = get_cli();
		_cli.cursor.reset();
	};


	auto cli_height()
	{
		const auto& _cli = get_cli();
		return _cli.cursor.end().y - _cli.cursor.begin().y;
	};

	void remove_excess_lines()
	{
		auto& _cli = get_cli();
		const auto _height = cli_height() - 1;
		auto& _lines = _cli.lines;

		if (_lines.size() >= _height)
		{
			const auto _rcount = (_lines.size() - _height) + 1;
			
			std::rotate(_lines.begin(), _lines.begin() + _rcount, _lines.end());
			_lines.erase(_lines.end() - _rcount, _lines.end());
		};

	};

	void update_cli()
	{
		auto _tmnl = terminal();
		
		remove_excess_lines();
		reset_cursor();
		clear_all();

		auto& _cli = get_cli();
		
		jcTerminalSetDefaultTextColor(_tmnl, _cli.settings.output_color, _cli.settings.output_background_color);
		
		auto& _lines = _cli.lines;
		tmnl::print(_tmnl, _cli.cursor, _lines.begin(), _lines.end());

		jcTerminalSetDefaultTextColor(_tmnl, _cli.settings.input_color, _cli.settings.input_background_color);

		//_cli.cursor.seek(0, 1);
		tmnl::print(_tmnl, _cli.cursor, _cli.settings.input_prefix);
		tmnl::print(_tmnl, _cli.cursor, _cli.input);

		jcTerminalRefresh(_tmnl);

	};



	void write(const std::string& _ln)
	{
		const auto _tkns = jc::split_not_empty(_ln, '\n');
		const auto _count = _tkns.size();

		auto& _cli = get_cli();
		std::string _tkStr{};

		for (auto& t : _tkns)
		{
			_tkStr = t;
			_cli.history.push_back(_tkStr);
			_cli.lines.push_back(_tkStr);
		};

		update_cli();
	};







	void clear_all()
	{
		auto& _cli = get_cli();
		auto& _tmnl = terminal();

		const auto _reg = _cli.cursor.region();

		reset_cursor();
		tmnl::clear(_tmnl, _reg);
		tmnl::fill(_tmnl, _reg, jcTerminal_Color{ 0, 0, 0, 255 }, _cli.settings.output_background_color);
	
	};
	void clear_terminal_output()
	{
		clear_all();
		get_cli().lines.clear();
		update_cli();
	};



	void echo_input()
	{
		auto& _cli = get_cli();
		auto _input = _cli.settings.input_prefix;
		_input.append(_cli.input);
		write(_input);
	};
	void clear_input()
	{
		auto& _cli = get_cli();
		_cli.input.clear();
	};


	void append_input(char c)
	{
		auto& _cli = get_cli();
		_cli.input.push_back(c);
		update_cli();
	};
	void pop_back_input()
	{
		auto& _cli = get_cli();
		if (!_cli.input.empty())
		{
			_cli.input.pop_back();
		};
	};

	void text_callback(jcTerminal* _tmnl, unsigned short _codepoint)
	{
		append_input((char)(_codepoint & 0xFF));
	};
	void key_callback(jcTerminal* _tmnl, jcTerminal_Key _key, jcTerminal_Action _action)
	{
		switch (_key)
		{
		case JCT_KEY_BACKSPACE:
			if (_action != JCT_RELEASE)
			{
				pop_back_input();
			};
			break;
		case JCT_KEY_ENTER:
			if (_action == JCT_RELEASE)
			{
				auto& _cli = get_cli();
				if (!_cli.input.empty())
				{
					auto _input{ get_cli().input };

					echo_input();
					clear_input();

					if (_cli.callback)
					{
						_cli.callback.invoke(_input);
					};
				};
			};
			break;
		};
	};



	void set_command_callback(CommandCallback _cb)
	{
		auto& _cli = get_cli();
		_cli.callback = std::move(_cb);
	};



	void set_cli_region(const tmnl::Region& _region)
	{
		auto& _cli = get_cli();
		clear_all();
		_cli.cursor = tmnl::Cursor{ _region };
	};

	void set_callbacks()
	{
		auto& _tmnl = terminal();
		jcTerminalSetKeyCallback(_tmnl, &key_callback);
		jcTerminalSetTextCallback(_tmnl, &text_callback);
	};
	void remove_callbacks()
	{
		auto& _tmnl = terminal();
		jcTerminalSetKeyCallback(_tmnl, nullptr);
		jcTerminalSetTextCallback(_tmnl, nullptr);
	};

	bool start_cli(jcTerminal* _tmnl)
	{
		auto& _cli = get_cli();
		auto& _crsr = _cli.cursor;

		int _w = 0;
		int _h = 0;
		jcTerminalGetWindowSize(_tmnl, &_w, &_h);

		auto& _begin = _crsr.begin();
		_begin.x = 0;
		_begin.y = 2;
		
		auto& _end = _crsr.end();
		_end.x = _w;
		_end.y = _h - 1;

		_crsr.reset();

		set_callbacks();
		update_cli();

		return true;
	};
	void shutdown_cli()
	{
		remove_callbacks();
		get_cli().callback.reset();
	};



}



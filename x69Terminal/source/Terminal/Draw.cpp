#include "Draw.h"


#include <c/JCTerminal.h>



namespace x69::tmnl
{

	void set_texture(jcTerminal* _terminal, Position _pos, unsigned short _textureIndex)
	{
		jcTerminalPut(_terminal, _pos.x, _pos.y, _textureIndex);
	};



	void fill(jcTerminal* _terminal, const Region& _region, unsigned short _textureIndex)
	{
		Cursor _cs{ _region };
		for (_cs.reset(); _cs.at().y != _cs.end().y; _cs.advance())
		{
			set_texture(_terminal, _cs.at(), _textureIndex);
		};
	};
	void fill(jcTerminal* _terminal, const Region& _region, jcTerminal_Color _foreground, jcTerminal_Color _background)
	{
		Cursor _cs{ _region };
		for (_cs.reset(); _cs.at().y != _cs.end().y; _cs.advance())
		{
			auto _x = _cs.at().x;
			auto _y = _cs.at().y;

			jcTerminalSetColor(_terminal, _x, _y, _foreground);
			jcTerminalSetBackgroundColor(_terminal, _x, _y, _background);

		};
	};


	void clear(jcTerminal* _terminal, const Region& _region)
	{
		fill(_terminal, _region, 0);
	};

	void print(jcTerminal* _terminal, Cursor& _cursor, const std::string& _str)
	{
		auto& _at = _cursor.at();
		auto& _x = _at.x;
		auto& _y = _at.y;
		jcTerminalPrint(_terminal, &_x, &_y, _str.c_str(), _str.size());
	};


	Region terminal_region(jcTerminal* _terminal)
	{
		Region _out{};
		_out.xMin = 0;
		_out.yMin = 0;

		_out.xMax = 0;
		_out.yMax = 0;
		jcTerminalGetWindowSize(_terminal, &_out.xMax, &_out.yMax);
		return _out;
	};


	void set_color(jcTerminal* _terminal, const TextColor& _color)
	{
		jcTerminalSetDefaultTextColor(_terminal, _color.text, _color.background);
	};

};

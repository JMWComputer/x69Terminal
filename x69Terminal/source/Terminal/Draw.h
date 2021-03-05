#pragma once

#include "Region.h"

#include <c/JCTerminal.h>

#include <string>
#include <sstream>

struct jcTerminal;

namespace x69::tmnl
{
	void set_texture(jcTerminal* _terminal, Position _pos, unsigned short _textureIndex);

	void fill(jcTerminal* _terminal, const Region& _region, unsigned short _textureIndex);
	void fill(jcTerminal* _terminal, const Region& _region, jcTerminal_Color _foreground, jcTerminal_Color _background);

	void clear(jcTerminal* _terminal, const Region& _region);

	void print(jcTerminal* _terminal, Cursor& _cursor, const std::string& _str);
	
	template <typename IterT>
	inline IterT print(jcTerminal* _terminal, Cursor& _cursor, IterT _begin, const IterT _end)
	{
		const auto& _cbegin = _cursor.begin();
		const auto& _cend = _cursor.end();
		auto& _at = _cursor.at();

		for (_begin; _begin != _end; ++_begin)
		{
			print(_terminal, _cursor, *_begin);
			_at.x = _cbegin.x;
			++_at.y;
			if (_at.y >= _cend.y)
			{
				break;
			};
		};

		return _begin;
	};

	Region terminal_region(jcTerminal* _terminal);


	struct TextColor
	{
		jcTerminal_Color text;
		jcTerminal_Color background;
	};

	void set_color(jcTerminal* _terminal, const TextColor& _color);

};

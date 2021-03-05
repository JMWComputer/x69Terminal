#pragma once

#include <jclib/parse.h>

#include <vector>
#include <string_view>

namespace x69
{

	using CommandArgs = std::vector<std::string_view>;

	inline CommandArgs parse_command(const std::string_view& _sv)
	{
		return jc::split_not_empty(_sv, ' ');
	};


}
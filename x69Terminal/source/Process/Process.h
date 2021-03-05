#pragma once

#include <filesystem>
#include <string_view>

namespace x69
{
	void launch_process(const std::filesystem::path& _path);
	void launch_process(const std::filesystem::path& _path, std::string& _commandLine);
};

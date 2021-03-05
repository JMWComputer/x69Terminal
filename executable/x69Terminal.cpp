
#include <x69Terminal.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <cassert>



const std::filesystem::path font_path_v{ SOURCE_ROOT "/../fonts/Hack/Hack-Regular.ttf" };


int main()
{




	auto _good = x69::start_terminal(x69::TerminalConfig{ font_path_v });
	assert(_good);

	while (x69::update_terminal()) {};

	x69::shutdown_terminal();

	return 0;
};

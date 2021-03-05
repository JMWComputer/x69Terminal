#include "Process.h"

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>


void launch_process_os(const std::filesystem::path& _path, char* _args)
{
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	si.dwFlags |= STARTF_USESTDHANDLES;

	auto _pstr = _path.string();

	// start the program up
	CreateProcess(_pstr.data(),   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		true,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	std::cout.flush();

};

#endif


namespace x69
{
	void launch_process(const std::filesystem::path& _path, std::string& _commandLine)
	{
		launch_process_os(_path, _commandLine.data());
	};

}
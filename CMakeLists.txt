cmake_minimum_required(VERSION 3.8)

option(X69_TERMINAL_GIT_CLONE_DEPS "Clones the dependencies if the targets are not already defined" ON)

project(x69Terminal)

set(X69EMULATOR_TARGET_NAME x69Emulator)

set(lib_dir "lib")

find_package(Git QUIET)

macro(ADD_GIT_DEPENDENCY depLibraryDir depTarget depName githubURL)
if(NOT TARGET ${depTarget})
	execute_process(COMMAND 
		${GIT_EXECUTABLE} clone ${githubURL} ${depLibraryDir}/${depName}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE GIT_SUBMOD_RESULT)	
	add_subdirectory("${depLibraryDir}/${depName}")	
endif()
endmacro()

macro(ADD_GIT_DEPENDENCY_NO_CMAKE depLibraryDir depTarget depName githubURL)
if(NOT TARGET ${depTarget})
	execute_process(COMMAND 
		${GIT_EXECUTABLE} clone ${githubURL} ${depLibraryDir}/${depName}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE GIT_SUBMOD_RESULT)
endif()
endmacro()


#
#	x69Emulator : https://github.com/JMWComputer/x69Emulator
#

ADD_GIT_DEPENDENCY(${lib_dir} x69Emulator x69Emulator "https://github.com/JMWComputer/x69Emulator")


#
#	JCTerminal : https://github.com/JonathanCline/JCTerminal
#

ADD_GIT_DEPENDENCY(${lib_dir} JCTerminal JCTerminal "https://github.com/JonathanCline/JCTerminal")


add_subdirectory("x69Terminal")
add_subdirectory("executable")



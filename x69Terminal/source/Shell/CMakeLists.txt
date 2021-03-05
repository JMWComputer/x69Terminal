

add_subdirectory("CLI")

target_sources(${PROJECT_NAME} PRIVATE 

	"${CMAKE_CURRENT_SOURCE_DIR}/Shell.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Shell.cpp"
	
	"${CMAKE_CURRENT_SOURCE_DIR}/ShellApp.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/ShellApp.cpp"
	
	
	)
	


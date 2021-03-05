
add_library(jclib INTERFACE)
target_include_directories(jclib INTERFACE "JCLib")

target_sources(${PROJECT_NAME} PRIVATE 

	"${CMAKE_CURRENT_SOURCE_DIR}/CommandParse.h"
	
	
	)
	



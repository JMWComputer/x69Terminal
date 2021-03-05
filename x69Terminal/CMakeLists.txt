

set(lib_include_public "include")


set(lib_include_private 
	"source"
	"source/Apps" )

add_library(${PROJECT_NAME} STATIC "include/${PROJECT_NAME}.h" "source/${PROJECT_NAME}.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${lib_include_public} PRIVATE ${lib_include_private})

target_link_libraries(${PROJECT_NAME} PUBLIC JCTerminal x69Emulator PRIVATE jclib )

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED True)

target_compile_definitions(${PROJECT_NAME} PRIVATE SOURCE_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory("source")


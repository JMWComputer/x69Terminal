

add_executable(${PROJECT_NAME}EXE "${PROJECT_NAME}.cpp")
target_link_libraries(${PROJECT_NAME}EXE PUBLIC ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}EXE PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED True)


target_compile_definitions(${PROJECT_NAME}EXE PRIVATE SOURCE_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/")



add_executable(${PROJECT_NAME}other "other.cpp")


install(TARGETS ${PROJECT_NAME}EXE DESTINATION "bin")

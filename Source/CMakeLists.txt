file(GLOB_RECURSE source *.cpp *.c *.h *.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
add_executable(BickRenderer ${source})

target_include_directories(BickRenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)

target_link_libraries(BickRenderer glfw)
target_link_libraries(BickRenderer glm)
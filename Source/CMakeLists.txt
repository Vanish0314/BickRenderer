file(GLOB_RECURSE source *.cpp *.c *.h *.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
add_executable(BickRenderer ${source})

target_include_directories(BickRenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)

target_link_libraries(BickRenderer glfw)
target_link_libraries(BickRenderer glm)
target_link_libraries(BickRenderer ${CMAKE_SOURCE_DIR}/3rd/assimp/lib/libassimp.dll.a)

file(COPY ${CMAKE_SOURCE_DIR}/3rd/assimp/bin/libassimp-5.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

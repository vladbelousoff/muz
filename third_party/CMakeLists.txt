cmake_minimum_required(VERSION 3.29)

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(gl3w)
add_subdirectory(spdlog)

if (USE_STRINGZILLA)
    add_subdirectory(StringZilla)
endif ()

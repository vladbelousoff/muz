cmake_minimum_required(VERSION 3.29)
project(muz)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_STRINGZILLA "Use StringZilla instead of std::string" OFF)

# FetchContent is used to download and manage dependencies
include(FetchContent)

FetchContent_Declare(
        gl3w
        GIT_REPOSITORY https://github.com/vladbelousoff/gl3w.git
        GIT_TAG 1.0.0
)
FetchContent_MakeAvailable(gl3w)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.14.1
)
FetchContent_MakeAvailable(spdlog)

if (MSVC)
    # Suppress "warning C4068: unknown pragma 'GCC'"
    add_compile_options(/wd4068)
endif ()

file(GLOB_RECURSE HEADER_FILES "${PROJECT_NAME}/include/*.h")
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_NAME}/src/*.cpp")

add_executable(${PROJECT_NAME} muz.cpp ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC
        gl3w glfw glm::glm spdlog::spdlog)

if (USE_STRINGZILLA)
    FetchContent_Declare(
            stringzilla
            GIT_REPOSITORY https://github.com/someone/stringzilla.git
            v3.9.8
    )
    FetchContent_MakeAvailable(stringzilla)

    target_compile_definitions(${PROJECT_NAME} PRIVATE MUZ_USE_STRINGZILLA)
    target_link_libraries(${PROJECT_NAME} PUBLIC stringzilla)
endif ()

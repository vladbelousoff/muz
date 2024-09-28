cmake_minimum_required(VERSION 3.29)
project(muz)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_STRINGZILLA "Use StringZilla instead of std::string" OFF)

add_subdirectory(third_party)

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
    target_compile_definitions(${PROJECT_NAME} PRIVATE MUZ_USE_STRINGZILLA)
    target_link_libraries(${PROJECT_NAME} PUBLIC stringzilla)
endif ()

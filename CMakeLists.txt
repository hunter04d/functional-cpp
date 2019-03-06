cmake_minimum_required(VERSION 3.13)
project(functional_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(curring curring.cpp)
add_executable(composition composition.cpp)
add_executable(partial_application partial_application.cpp)
add_executable(match match.cpp)


foreach(target ${BUILDSYSTEM_TARGETS})
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra)
    endif()
endforeach()
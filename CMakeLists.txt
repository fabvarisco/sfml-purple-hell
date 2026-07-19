cmake_minimum_required(VERSION 3.16)
project(PurpleHell LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 2.6 estatico, buildado do fonte (pkgs. do sistema ja migraram pra SFML 3, API incompativel)
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2)
FetchContent_MakeAvailable(SFML)

file(GLOB PURPLEHELL_SRC ${CMAKE_SOURCE_DIR}/PurpleHell/*.cpp)
add_executable(PurpleHell ${PURPLEHELL_SRC})

find_package(Threads REQUIRED)
target_link_libraries(PurpleHell PRIVATE
    sfml-graphics sfml-window sfml-audio sfml-network sfml-system Threads::Threads)

if(APPLE)
    # extlibs da SFML tem install name @rpath/../Frameworks/...; com este rpath
    # elas resolvem para um diretorio Frameworks/ ao lado do executavel
    set_target_properties(PurpleHell PROPERTIES BUILD_RPATH "@executable_path/Frameworks")
endif()

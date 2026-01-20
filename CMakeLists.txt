cmake_minimum_required(VERSION 3.15)
project(
        BobiniLambard
        VERSION 0.0.1
        DESCRIPTION "chujh wi "
        HOMEPAGE_URL "none"
        LANGUAGES C CXX
)

add_executable(example main.cpp "CreatePlayer.h" "CreatePlayer.cpp" "Projectile.h" "Projectile.cpp" "Enemy.h" "Enemy.cpp" "Spawner.h" "Spawner.cpp")

target_compile_features(example PUBLIC cxx_std_23)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${CMAKE_BINARY_DIR})
FetchContent_MakeAvailable(raylib)
target_link_libraries(example PRIVATE raylib)
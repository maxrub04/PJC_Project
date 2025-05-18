cmake_minimum_required(VERSION 3.27)
project(project_rubtsov)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(project_rubtsov main.cpp
        MapLoader.cpp
        MapLoader.h
        Character.cpp
        Character.h
        Background.cpp
        Background.h
        ENEMYSkeleton.cpp
        ENEMYSkeleton.h
        EnemySpirit.cpp
        EnemySpirit.h
        BOSS.cpp
        BOSS.h
)
target_link_libraries(project_rubtsov sfml-graphics)
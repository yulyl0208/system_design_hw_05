cmake_minimum_required(VERSION 3.16)
project(fitness-tracker-userver CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")

find_package(userver REQUIRED COMPONENTS core redis postgresql)

set(SOURCES
    src/main.cpp
    src/handlers/exercises_handler.cpp
    src/handlers/workouts_handler.cpp
    src/repositories/exercise_repo.cpp
    src/repositories/workout_repo.cpp
)

include_directories(
    src
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    userver::core
    userver::redis
    userver::postgresql
)

target_compile_options(${PROJECT_NAME} PRIVATE -pipe)

# 🔹 Установка (для Docker)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

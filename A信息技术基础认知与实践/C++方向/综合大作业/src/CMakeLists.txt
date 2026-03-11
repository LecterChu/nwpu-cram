cmake_minimum_required(VERSION 3.10.0)
project(game25sp VERSION 0.1.0 LANGUAGES C CXX)

option(BUILD_TESTS ON "Build tests")

add_subdirectory(${CMAKE_SOURCE_DIR}/vendors/SFML)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendors/entt)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendors/json)

include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/*.hpp)

if (BUILD_TESTS)
    file(GLOB_RECURSE TESTS ${CMAKE_SOURCE_DIR}/test/*.hpp)
endif()

add_executable(game25sp main.cpp ${SOURCES} ${HEADERS} ${TESTS})

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Audio EnTT::EnTT nlohmann_json::nlohmann_json)


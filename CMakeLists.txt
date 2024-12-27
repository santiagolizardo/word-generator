cmake_minimum_required(VERSION 3.10)

project(wordgenerator VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Version.hpp.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Version.hpp"
)

find_package(argparse REQUIRED)
find_package(RapidJSON REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} argparse::argparse rapidjson)


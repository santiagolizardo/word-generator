cmake_minimum_required(VERSION 3.10)

project(namegen VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    Main.cpp
    Generator.cpp
    NameGenerator.cpp
    Model.cpp
    Random.cpp
    LevenshteinDistance.cpp
    TrainingData.cpp
)

set(HEADERS
    Generator.hpp
    LevenshteinDistance.hpp
    Model.hpp
    NameGenerator.hpp
    Random.hpp
    TrainingData.hpp
)

find_package(args)
find_package(RapidJSON)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}  taywee::args rapidjson)


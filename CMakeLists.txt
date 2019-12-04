cmake_minimum_required(VERSION 3.15.5)

# Boost configuration
find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

# Compiler config
set(CMAKE_CXX_COMPILER /usr/local/opt/llvm/bin/clang++)
set(CMAKE_CXX_FLAGS "-O3")

# Source files
set(SOURCES
    src/estimator.cpp
    src/estimator.hpp
    src/glm.cpp
    src/glm.hpp
    src/queue.cpp
    src/queue.hpp
    src/reader.cpp
    src/reader.hpp
    src/solver.cpp
    src/solver.hpp
    src/utils.cpp
    src/utils.hpp
    src/main.cpp)

add_executable(main ${SOURCES})
set(EXECUTABLE_OUTPUT_PATH "../bin/")
target_link_libraries(main Boost::program_options)
cmake_minimum_required(VERSION 3.8)
project(lab4)

set(CMAKE_CXX_STANDARD 14)
set(BOOST_ROOT C:/Boost/1.65.1)
set(BOOST_LIBRARYDIR C:/Boost/lib)
set(BOOST_INCLUDEDIR C:/Boost/include)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS thread chrono system)
include_directories(${Boost_INCLUDE_DIRS} src)
link_libraries(${Boost_LIBRARIES})
set(SOURCE_FILES
        main.cpp
        Core/Factorizator.hpp
        Core/Algorithm.hpp
        Algorithm/Naive_Algorithm.hpp
        Algorithm/Pollard_Rho_Brent.hpp Core/Input.hpp Core/Output.hpp Core/ConcurrentQueue.hpp Core/Threadpool.hpp Core/ConcurrentFactorizator.hpp)

add_executable(lab4 ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.10)

project(simple-distributed-systen VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
find_package(PkgConfig)
pkg_check_modules(PC_ZerpMQ QUIET zmq)

find_path(ZeroMQ_INCLUDE_DIR
          NAMES zmq.hpp
          PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
          )

find_library(ZeroMQ_LIBRARY
             NAMES zmq
             PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
             )

add_executable(requestor-node requestor-node.cpp)
target_include_directories(requestor-node PUBLIC
	"${PROJECT_BINARY_DIR}")
target_link_libraries(requestor-node
    ${ZeroMQ_LIBRARY}
    proto ${PROTOBUF_LIBRARY})


add_executable(server-node server-node.cpp)
target_include_directories(server-node PUBLIC
    "${PROJECT_BINARY_DIR}")
target_link_libraries(server-node ${ZeroMQ_LIBRARY})


add_executable(database-node database-node.cpp)
target_include_directories(database-node PUBLIC
    "${PROJECT_BINARY_DIR}")
target_link_libraries(database-node
    ${ZeroMQ_LIBRARY}
    proto ${PROTOBUF_LIBRARY})


add_executable(demo demo.cpp)
target_include_directories(demo PUBLIC
    "${PROJECT_BINARY_DIR}")

add_subdirectory(proto)

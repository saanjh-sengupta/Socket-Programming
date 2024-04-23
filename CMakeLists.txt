cmake_minimum_required(VERSION 3.16.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Socket VERSION 1.0)
file(GLOB_RECURSE SRC_FILES source/*.cpp CMAKE_CONFIGURE_DEPENDS)

add_executable(server MainServer.cpp ${SRC_FILES})
add_executable(client MainClient.cpp ${SRC_FILES})

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(server PUBLIC -lpthread)
target_link_libraries(client PUBLIC -lpthread)
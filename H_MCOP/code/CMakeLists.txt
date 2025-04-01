cmake_minimum_required(VERSION 3.0.0)
project(H_MCOP VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(H_MCOP
main.cpp
FibHeap_head.h
FibHeap.h
getgraph.h
H_MCOP.h
heads.h
readgraph.h
showans.h)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

cmake_minimum_required(VERSION 3.4)
project(cmem VERSION 0.0.1 DESCRIPTION "cmem library v0.0.1")

include(GNUInstallDirs)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(cmem cmem.h cmem.c)
target_include_directories(cmem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CMEM_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
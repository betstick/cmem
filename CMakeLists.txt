cmake_minimum_required(VERSION 3.4)
project(cmem VERSION 0.0.1 DESCRIPTION "cmem library v0.0.1")

include(GNUInstallDirs)

add_library(cmem STATIC cmem.h cmem.c)

target_include_directories(cmem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
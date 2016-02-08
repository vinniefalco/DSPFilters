cmake_minimum_required(VERSION 2.8)

project (DSPFilters)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source SOURCE_LIB)

set(CMAKE_BUILD_TYPE Release)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})

target_include_directories(${PROJECT_NAME} 
PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

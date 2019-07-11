cmake_minimum_required(VERSION 3.0)

project (DSPFilters CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source SOURCE_LIB)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})
add_library(${PROJECT_NAME}_so SHARED ${SOURCE_LIB})

target_include_directories(${PROJECT_NAME}
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME}_so
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET ${PROJECT_NAME}_so PROPERTY POSITION_INDEPENDENT_CODE ON)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY include/DspFilters DESTINATION include)

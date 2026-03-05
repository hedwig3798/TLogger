cmake_minimum_required(VERSION 3.16)
project(TLogger)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/External")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist" CACHE PATH "..." FORCE)
endif()

option(BUILD_TEST_APP "make logger test program" ON)

add_subdirectory(src/TLogger)

if(BUILD_TEST_APP)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LoggerTest)
    add_subdirectory(src/LoggerTest)
    add_dependencies(LoggerTest TLogger)
endif()


install(FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE"
    "${CMAKE_CURRENT_SOURCE_DIR}/THIRD-PARTY-NOTICES.md"
    DESTINATION .
)

cmake_minimum_required(VERSION 3.16)
project(TLogger)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/External")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LoggerTest)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist" CACHE PATH "..." FORCE)
endif()

add_subdirectory(TLogger)
add_subdirectory(LoggerTest)

add_dependencies(LoggerTest TLogger)

install(
	TARGETS TLogger LoggerTest
    RUNTIME DESTINATION bin    # .exe, .dll
    LIBRARY DESTINATION lib    # 리눅스 .so 
    ARCHIVE DESTINATION lib    # .lib
)

install(FILES "TLogger/ILogger.h" DESTINATION include)
install(FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE"
    "${CMAKE_CURRENT_SOURCE_DIR}/THIRD-PARTY-NOTICES.md"
    DESTINATION .
)

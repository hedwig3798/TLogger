cmake_minimum_required(VERSION 3.16)
project(TLogger)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist" CACHE PATH "..." FORCE)
endif()

add_subdirectory(TLogger)
add_subdirectory(LoggerTest)

install(
	TARGETS TLogger LoggerTest
    RUNTIME DESTINATION bin    # .exe, .dll
    LIBRARY DESTINATION lib    # 리눅스 .so 
    ARCHIVE DESTINATION lib    # .lib
)

install(FILES "TLogger/ILogger.h" DESTINATION include/TLogger)

add_executable(LoggerTest main.cpp)

target_link_libraries(LoggerTest PRIVATE TLogger)

set_target_properties(LoggerTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Build/$<CONFIG>")

source_group("Entry" FILES main.cpp)
include(FetchContent)

# fmt 라이브러리 가져오기
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG            12.1.0
)
FetchContent_MakeAvailable(fmt)

# 소스 파일 및 출력 경로 설정
set(TSOURCE_FILES
    ILogger.h ILogger.cpp
    TLogger.h TLogger.cpp
    dllmain.cpp framework.h
    pch.h pch.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Build/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Build/$<CONFIG>")

# 라이브러리 생성
add_library(TLogger SHARED ${TSOURCE_FILES})
target_compile_definitions(TLogger PRIVATE LOGGER_EXPORTS)

# 디버그 dll 이름만 다르게 설정
set_target_properties(TLogger PROPERTIES DEBUG_POSTFIX "D")

# fmt 라이브러리 연결
target_link_libraries(TLogger PRIVATE fmt::fmt)

# Visual Studio 소스 그룹화
source_group("DLL" FILES dllmain.cpp framework.h pch.h pch.cpp)
source_group("Logger" FILES ILogger.h ILogger.cpp TLogger.h TLogger.cpp)

install(FILES "ILogger.h" DESTINATION include/TLogger)

# 인클루드 경로 설정
target_include_directories(TLogger PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
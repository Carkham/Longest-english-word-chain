cmake_minimum_required(VERSION 3.0.2)

add_subdirectory(core)
# 支持模块生成dll
add_library(ArgParser SHARED ArgParser.cpp)
add_library(IOUtil SHARED IOUtil.cpp)
install(
        TARGETS ArgParser
        TARGETS IOUtil
        RUNTIME DESTINATION ${EXECUTABLE_OUTPUT_PATH}
        LIBRARY DESTINATION ${EXECUTABLE_OUTPUT_PATH}
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/guibin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/guibin
)
file(GLOB libs ${LIBRARY_OUTPUT_PATH}/ArgParser.dll ${LIBRARY_OUTPUT_PATH}/IOUtil.dll ${LIBRARY_OUTPUT_PATH}/Core.dll)
file(COPY ${libs} DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file(COPY ${libs} DESTINATION ${PROJECT_SOURCE_DIR}/guibin)

add_executable(Wordlist Wordlist.cpp ArgParser.cpp IOUtil.cpp)
#add_executable(Wordlist Wordlist.cpp)

target_link_libraries(Wordlist
        PRIVATE ${LIBRARY_OUTPUT_PATH}/Core.dll
#        PRIVATE ${LIBRARY_OUTPUT_PATH}/ArgParser.dll
#        PRIVATE ${LIBRARY_OUTPUT_PATH}/IOUtil.dll
        )
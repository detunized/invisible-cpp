project(invisible-cpp)
cmake_minimum_required(VERSION 2.8)

# Path to LLVM
set(LLVM_ROOT "${CMAKE_CURRENT_LIST_DIR}/../llvm/build" CACHE PATH "Root of LLVM install/build")
if(NOT EXISTS ${LLVM_ROOT}/include/llvm)
    message(FATAL_ERROR "LLVM_ROOT (${LLVM_ROOT}) is not a valid LLVM install")
endif()

# Load LLVM CMake config
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${LLVM_ROOT}/share/llvm/cmake")
include(LLVMConfig)

# LLVM compiler/linker settings
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

# Clang include directories
include_directories("${LLVM_BUILD_MAIN_SRC_DIR}/tools/clang/include"
                    "${LLVM_BUILD_BINARY_DIR}/tools/clang/include")


# We want C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

# Clang don't like RTTI
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

#
# Add executable with the settings prepared above
#
add_executable(${PROJECT_NAME} main.cpp
                               action.cpp
                               consumer.cpp
                               stacktrace.cpp)

# LLVM libraries (use llvm-config)
execute_process(COMMAND ${LLVM_BUILD_TOOLS_BINARY_DIR}/llvm-config --libs
                OUTPUT_VARIABLE REQUIRED_LLVM_LIBRARIES
                OUTPUT_STRIP_TRAILING_WHITESPACE)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LLVM_LIBRARIES})

# Clang libraries
target_link_libraries(${PROJECT_NAME} clangAnalysis
                                      clangAST
                                      clangASTMatchers
                                      clangBasic
                                      clangDriver
                                      clangDynamicASTMatchers
                                      clangEdit
                                      clangFormat
                                      clangFrontend
                                      clangFrontendTool
                                      clangIndex
                                      clangLex
                                      clangParse
                                      clangRewriteCore
                                      clangRewriteFrontend
                                      clangSema
                                      clangSerialization
                                      clangTooling)

# Extra libraries
target_link_libraries(${PROJECT_NAME} ncurses
                                      z)

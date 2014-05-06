project(invisible-cpp)
cmake_minimum_required(VERSION 2.8)

# Path to LLVM build/install root relative to CMakeLists.txt
set(LLVM_ROOT "../llvm/build")

# Path to llvm-config
set(LLVM_CONFIG "${CMAKE_CURRENT_LIST_DIR}/${LLVM_ROOT}/bin/llvm-config")
if(NOT EXISTS "${LLVM_CONFIG}")
    message(FATAL_ERROR "llvm-config (${LLVM_CONFIG}) could not be found")
endif()

execute_process(COMMAND "${LLVM_CONFIG}" "--src-root"
                OUTPUT_VARIABLE LLVM_SRC_ROOT
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND "${LLVM_CONFIG}" "--obj-root"
                OUTPUT_VARIABLE LLVM_OBJ_ROOT
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND "${LLVM_CONFIG}" "--cxxflags"
                OUTPUT_VARIABLE LLVM_CXX_FLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND "${LLVM_CONFIG}" "--libdir"
                OUTPUT_VARIABLE LLVM_LIB_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND "${LLVM_CONFIG}" "--libs"
                OUTPUT_VARIABLE LLVM_LIBS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# LLVM compiler/linker settings
add_definitions("${LLVM_CXX_FLAGS}")
link_directories("${LLVM_LIB_DIR}")

# Clang include directories
include_directories("${LLVM_SRC_ROOT}/tools/clang/include"
                    "${LLVM_OBJ_ROOT}/tools/clang/include")

# We want C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

# Clang doesn't like RTTI
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

#
# Add executable with the settings prepared above
#
add_executable("${PROJECT_NAME}" "main.cpp"
                                 "action.cpp"
                                 "consumer.cpp"
                                 "stacktrace.cpp")

# LLVM libraries
target_link_libraries("${PROJECT_NAME}" "${LLVM_LIBS}")

# Clang libraries
target_link_libraries("${PROJECT_NAME}" "clangAnalysis"
                                        "clangAST"
                                        "clangASTMatchers"
                                        "clangBasic"
                                        "clangDriver"
                                        "clangDynamicASTMatchers"
                                        "clangEdit"
                                        "clangFormat"
                                        "clangFrontend"
                                        "clangFrontendTool"
                                        "clangIndex"
                                        "clangLex"
                                        "clangParse"
                                        "clangRewriteCore"
                                        "clangRewriteFrontend"
                                        "clangSema"
                                        "clangSerialization"
                                        "clangTooling")

# Extra libraries needed by LLVM/Clang
target_link_libraries("${PROJECT_NAME}" "ncurses"
                                        "z")

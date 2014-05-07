project(invisible-cpp)
cmake_minimum_required(VERSION 2.8)

# Path to LLVM build/install root relative to CMakeLists.txt
set(LLVM_ROOT "../llvm/build")

# Path to llvm-config
set(LLVM_CONFIG "${CMAKE_CURRENT_LIST_DIR}/${LLVM_ROOT}/bin/llvm-config")
if(NOT EXISTS "${LLVM_CONFIG}")
    message(FATAL_ERROR "llvm-config (${LLVM_CONFIG}) could not be found")
endif()

# Run llvm-config to get various build parameters
macro(llvm_config command result_var)
    execute_process(COMMAND "${LLVM_CONFIG}" "${command}"
                    OUTPUT_VARIABLE "${result_var}"
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
endmacro()

llvm_config("--src-root" LLVM_SRC_ROOT)
llvm_config("--obj-root" LLVM_OBJ_ROOT)
llvm_config("--cxxflags" LLVM_CXX_FLAGS)
llvm_config("--libdir" LLVM_LIB_DIR)
llvm_config("--libs" LLVM_LIBS)

# LLVM compiler/linker settings
add_definitions("${LLVM_CXX_FLAGS}")
link_directories("${LLVM_LIB_DIR}")

# Clang include directories
include_directories("${LLVM_SRC_ROOT}/tools/clang/include"
                    "${LLVM_OBJ_ROOT}/tools/clang/include")

# We want C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

# Clang doesn't like RTTI
add_definitions("-fno-rtti")

# Mute warnings produced by GCC 4.8 on LLVM/Clang headers
add_definitions("-Wno-strict-aliasing")

#
# Add executable with the settings prepared above
#
add_executable("${PROJECT_NAME}" "main.cpp"
                                 "action.cpp"
                                 "consumer.cpp"
                                 "stacktrace.cpp")

# Clang libraries
target_link_libraries("${PROJECT_NAME}" "clangIndex"
                                        "clangFormat"
                                        "clangTooling"
                                        "clangFrontendTool"
                                        "clangStaticAnalyzerFrontend"
                                        "clangRewriteFrontend"
                                        "clangCodeGen"
                                        "clangARCMigrate"
                                        "clangStaticAnalyzerCheckers"
                                        "clangStaticAnalyzerCore"
                                        "clangRewriteCore"
                                        "clangFrontend"
                                        "clangSerialization"
                                        "clangParse"
                                        "clangSema"
                                        "clangEdit"
                                        "clangAnalysis"
                                        "clangDriver"
                                        "clangDynamicASTMatchers"
                                        "clangASTMatchers"
                                        "clangAST"
                                        "clangLex"
                                        "clangBasic")

# LLVM libraries
target_link_libraries("${PROJECT_NAME}" "${LLVM_LIBS}")

# Extra libraries needed by LLVM/Clang
target_link_libraries("${PROJECT_NAME}" "dl"
                                        "ncurses"
                                        "pthread"
                                        "z")

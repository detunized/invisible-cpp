#include "action.h"

#include "utils.h"
#include "stacktrace.h"

#include <clang/Basic/FileManager.h>
#include <clang/Tooling/Tooling.h>

int main(int argc, char const *argv[])
{
    install_stack_trace_printer({SIGABRT, SIGSEGV, SIGILL, SIGBUS, SIGFPE});

    auto file_manager = make_intrusive<clang::FileManager>(clang::FileSystemOptions());
    auto action = std::make_unique<Action>();

    clang::tooling::ToolInvocation ti(
        {"clang", "-fsyntax-only", "-std=c++11", "labrat.cpp"},
        action.release(), // the tool invocation takes over
        file_manager.getPtr());
    ti.run();

    return 0;
}

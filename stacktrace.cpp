#include "stacktrace.h"

#include <array>
#include <vector>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <execinfo.h>

namespace
{
void print_stack_trace_on_signal(int signum)
{
   fprintf(stderr, "Caught signal %d\n", signum);
   print_stack_trace();
   exit(signum);
}
}

void print_stack_trace()
{
   std::array<void*, 64> addresses;
   auto addrlen = backtrace(addresses.data(), addresses.size());
   backtrace_symbols_fd(addresses.data(), addrlen, fileno(stderr));
}

void install_stack_trace_printer(std::vector<int> const &signums)
{
   for (auto i: signums)
      signal(i, print_stack_trace_on_signal);
}

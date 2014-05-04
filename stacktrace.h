#pragma once

#include <vector>

void print_stack_trace();
void install_stack_trace_printer(std::vector<int> const &signals);

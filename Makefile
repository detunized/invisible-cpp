# Build LLVM on OS X
#
# cd ~/devel
# git clone http://llvm.org/git/llvm.git
# cd llvm/tools
# git clone http://llvm.org/git/clang.git
# cd ~/devel/llvm
# mkdir build
# cd build
# cmake -DCMAKE_CXX_FLAGS="-stdlib=libc++" -DCMAKE_BUILD_TYPE=Release .. && make
# or
# cmake -DCMAKE_CXX_FLAGS="-stdlib=libc++" -DCMAKE_BUILD_TYPE=Release -G Ninja .. && ninja

SHELL=/bin/bash
export SHELLOPTS=pipefail

LLVM=../llvm/build

default: invisible-cpp
	@./invisible-cpp

invisible-cpp: Makefile main.cpp action.h consumer.h stacktrace.cpp stacktrace.h utils.h
	@clang++ \
		-std=c++11 \
		-stdlib=libc++ \
		-fno-rtti \
		-o invisible-cpp \
		$(shell $(LLVM)/bin/llvm-config --cxxflags) \
		-I../llvm/tools/clang/include \
		-I$(shell $(LLVM)/bin/llvm-config --obj-root)/tools/clang/include \
		$(shell $(LLVM)/bin/llvm-config --ldflags --libs) \
		-lclangAnalysis \
		-lclangAST \
		-lclangASTMatchers \
		-lclangBasic \
		-lclangDriver \
		-lclangDynamicASTMatchers \
		-lclangEdit \
		-lclangFormat \
		-lclangFrontend \
		-lclangFrontendTool \
		-lclangIndex \
		-lclangLex \
		-lclangParse \
		-lclangRewriteCore \
		-lclangRewriteFrontend \
		-lclangSema \
		-lclangSerialization \
		-lclangTooling \
		-lz \
		-lcurses \
		main.cpp stacktrace.cpp 2>&1 | perl -pe 's/\x1b\[[0-9;]*m//g'

clean:
	rm -f invisible-cpp

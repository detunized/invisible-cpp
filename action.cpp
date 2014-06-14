#include "action.h"
#include "consumer.h"

#include <llvm/ADT/StringRef.h>

using namespace llvm;
using namespace clang;

ASTConsumer *Action::CreateASTConsumer(CompilerInstance &CI, StringRef InFile)
{
    return new Consumer(CI);
}

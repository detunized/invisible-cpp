#pragma once

#include "consumer.h"

#include <llvm/ADT/StringRef.h>
#include <clang/Frontend/FrontendAction.h>

class Action: public clang::ASTFrontendAction
{
protected:
    virtual clang::ASTConsumer *CreateASTConsumer(clang::CompilerInstance &CI,
                                                  llvm::StringRef InFile) override
    {
        return new Consumer();
    }
};

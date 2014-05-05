#include "consumer.h"
#include <iostream>

#include <clang/Sema/Sema.h>

using namespace llvm;
using namespace clang;

void Consumer::InitializeSema(Sema &S)
{
    sema_ = &S;
}

void Consumer::ForgetSema()
{
    sema_ = nullptr;
}

bool Consumer::HandleTopLevelDecl(DeclGroupRef D)
{
    std::cout << "TopLevelDecl:\n";
    for (auto const &i: D)
        i->dump();

    return true;
}

void Consumer::HandleTagDeclDefinition(TagDecl *D)
{
    std::cout << "TagDeclDefinition:\n";
    D->dump();

    if (auto record = llvm::dyn_cast<clang::CXXRecordDecl>(D))
    {
        // Add default ctor
        if (record->needsImplicitDefaultConstructor())
        {
            auto ctor = sema_->DeclareImplicitDefaultConstructor(record);
            sema_->DefineImplicitDefaultConstructor(record->getLocation(), ctor);
        }
    }
}

#pragma once

#include <iostream>

#include <clang/Sema/Sema.h>
#include <clang/Sema/SemaConsumer.h>

class Consumer: public clang::SemaConsumer
{
    clang::Sema *sema_ = nullptr;

    virtual void InitializeSema(clang::Sema &S) override
    {
        sema_ = &S;
    }

    virtual void ForgetSema() override
    {
        sema_ = nullptr;
    }

    virtual bool HandleTopLevelDecl(clang::DeclGroupRef D) override
    {
        std::cout << "TopLevelDecl:\n";
        for (auto const &i: D)
            i->dump();

        return true;
    }

    virtual void HandleTagDeclDefinition(clang::TagDecl *D) override
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
};

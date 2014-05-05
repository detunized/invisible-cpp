#pragma once

#include <clang/Sema/SemaConsumer.h>

class Consumer: public clang::SemaConsumer
{
protected:
    virtual void InitializeSema(clang::Sema &S) override;
    virtual void ForgetSema() override;
    virtual bool HandleTopLevelDecl(clang::DeclGroupRef D) override;
    virtual void HandleTagDeclDefinition(clang::TagDecl *D) override;

private:
    clang::Sema *sema_ = nullptr;
};

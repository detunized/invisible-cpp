#pragma once

#include <clang/Sema/SemaConsumer.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/Frontend/CompilerInstance.h>

class Consumer: public clang::SemaConsumer
{
public:
    Consumer(clang::CompilerInstance &compiler)
        : compiler_(compiler)
    {
    }

protected:
    virtual void Initialize(clang::ASTContext &context) override;
    virtual void HandleTranslationUnit(clang::ASTContext &context) override;

    virtual void InitializeSema(clang::Sema &S) override;
    virtual void ForgetSema() override;
    virtual bool HandleTopLevelDecl(clang::DeclGroupRef D) override;
    virtual void HandleTagDeclDefinition(clang::TagDecl *D) override;

private:
    clang::CompilerInstance &compiler_;
    clang::Sema *sema_ = nullptr;
    clang::Rewriter rewriter_;
};

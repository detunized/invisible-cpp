#pragma once

#include <clang/AST/RecursiveASTVisitor.h>

class Visitor: public clang::RecursiveASTVisitor<Visitor>
{
public:
    explicit Visitor(clang::ASTContext &context)
        : context_(context)
    {
    }

    bool VisitVarDecl(clang::VarDecl *d);

private:
    clang::ASTContext &context_;
};

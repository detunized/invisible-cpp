#pragma once

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Rewrite/Core/Rewriter.h>

class Visitor: public clang::RecursiveASTVisitor<Visitor>
{
public:
    explicit Visitor(clang::ASTContext &context, clang::Rewriter &rewriter)
        : context_(context)
        , rewriter_(rewriter)
    {
    }

    bool VisitVarDecl(clang::VarDecl *d);

private:
    clang::ASTContext &context_;
    clang::Rewriter &rewriter_;
};

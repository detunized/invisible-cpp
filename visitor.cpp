#include "visitor.h"
#include <iostream>
#include <clang/Basic/SourceManager.h>

using namespace llvm;
using namespace clang;

bool Visitor::VisitVarDecl(VarDecl *d) {
    std::cout << d->getType().getAsString()
              << " | " << d->getQualifiedNameAsString()
              << " | " << (d->getType()->getContainedAutoType() ? d->getType()->getContainedAutoType()->getDeducedType().getAsString() : "-")
              << " | " << d->getNameAsString()
              << std::endl;

    auto &&tl = d->getTypeSourceInfo()->getTypeLoc(); //.getAs<QualifiedTypeLoc>();

    //std::cout << "!!!!!!!!!!!!!!!!! " << tl.getAs<QualifiedTypeLoc>().isKind
    outs() << "!!!!!!!!!!!!!!!!! " << tl.getType()->getTypeClassName() << "\n";
    outs() << "!!!!!!!!!!!!!!!!! " << tl.getTypeLocClass() << '\n';
    //rewriter_.getSourceMgr().getSpellingLoc(tl.getLocStart());
    tl.getLocStart().print(outs(), rewriter_.getSourceMgr());
    outs() << '\n';
    rewriter_.getSourceMgr().getSpellingLoc(tl.getLocStart()).print(outs(), rewriter_.getSourceMgr());
    outs() << '\n';
    d->getInnerLocStart().print(outs(), rewriter_.getSourceMgr());
    outs() << '\n';


    //tl.
    //tl.getBeginLoc()
    //dyn_cast<QualifiedTypeLoc>(&tl);

    //rewriter_.ReplaceText(tl.getSourceRange(), "[" + d->getType().getAsString() + "]");
    //rewriter_.ReplaceText(tl.getSourceRange(), "[" + d->getType().getAsString() + "]");
    rewriter_.ReplaceText(d->getSourceRange(), "[]");


    //rewriter_.InsertTextBefore(tl.getBeginLoc(), "[");
    //rewriter_.InsertTextAfter(tl.getLocEnd(), "]");

    //rewriter_.ReplaceText(d->getQualifierLoc().getSourceRange(), "[" + d->getType().getAsString() + "]");

    return true;
}

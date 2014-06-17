#include "visitor.h"
#include <iostream>

using namespace llvm;
using namespace clang;

bool Visitor::VisitVarDecl(VarDecl *d) {
    std::cout << d->getType().getAsString()
              << " | " << d->getQualifiedNameAsString()
              << " | " << (d->getType()->getContainedAutoType() ? d->getType()->getContainedAutoType()->getDeducedType().getAsString() : "-")
              << " | " << d->getNameAsString()
              << std::endl;

    return true;
}

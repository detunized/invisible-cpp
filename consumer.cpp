#include "consumer.h"
#include <fstream>
#include <iostream>

#include <clang/AST/ASTContext.h>
#include <clang/Sema/Sema.h>
#include <clang/Rewrite/Core/HTMLRewrite.h>

using namespace llvm;
using namespace clang;

namespace
{

void write_to_file(RewriteBuffer const &buffer, std::string const &filename)
{
    std::ofstream file(filename);
    if (!file)
        throw std::runtime_error("Failed to open a file");

    for (auto c: buffer)
        file << c;
}

}

void Consumer::Initialize(ASTContext &context)
{
    rewriter_.setSourceMgr(context.getSourceManager(), context.getLangOpts());
}

void Consumer::HandleTranslationUnit(ASTContext &context)
{
    auto const &source_manager = rewriter_.getSourceMgr();
    auto const file_id = source_manager.getMainFileID();
    auto const file_entry = source_manager.getFileEntryForID(file_id);
    std::string filename = file_entry == nullptr ? "untitled" : file_entry->getName();

    html::AddLineNumbers(rewriter_, file_id);
    html::AddHeaderFooterInternalBuiltinCSS(rewriter_, file_id, filename.c_str());
    html::SyntaxHighlight(rewriter_, file_id, compiler_.getPreprocessor());
    html::EscapeText(rewriter_, file_id, false, true);

    write_to_file(rewriter_.getEditBuffer(file_id), filename + ".html");
}

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

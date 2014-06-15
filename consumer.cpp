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

std::string pad(int indent)
{
    return std::string(indent * 2, ' ');
}

void print_statement(Stmt const *s, int indent = 0);
void print_declaration(Decl const *d, int indent = 0);

void print_statement(Stmt const *s, int indent)
{
    assert(s);

    std::cout << pad(indent) << "S: " << s->getStmtClassName() << std::endl;

    if (auto const ds = dyn_cast<DeclStmt>(s))
        for (auto &&i: ds->decls())
            print_declaration(i, indent + 1);

    for (auto &&i: s->children())
        print_statement(i, indent + 1);
}

void print_declaration(Decl const *d, int indent)
{
    assert(d);

    std::cout << pad(indent) << "D: " << d->getDeclKindName();
    if (auto const nd = dyn_cast<NamedDecl>(d))
        std::cout << " " << nd->getNameAsString();
    std::cout << std::endl;

    if (auto const body = d->getBody())
        print_statement(body, indent);

    // Declaration context
    if (auto const dc = dyn_cast<DeclContext>(d))
        for (auto &&i: dc->decls())
            print_declaration(i, indent + 1);
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

    auto const tu = context.getTranslationUnitDecl();
    print_declaration(tu);

    tu->dump(outs());
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
    return true;
}

void Consumer::HandleTagDeclDefinition(TagDecl *D)
{
//    std::cout << "TagDeclDefinition:\n";
//    D->dump(outs());

//    if (auto record = dyn_cast<CXXRecordDecl>(D))
//    {
//        // Add default ctor
//        if (record->needsImplicitDefaultConstructor())
//        {
//            auto ctor = sema_->DeclareImplicitDefaultConstructor(record);
//            sema_->DefineImplicitDefaultConstructor(record->getLocation(), ctor);
//        }
//    }
}

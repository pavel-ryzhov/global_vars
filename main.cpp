#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>

class GlobalVarPrinter : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
    std::set<std::string> global_vars;
    void run(const clang::ast_matchers::MatchFinder::MatchResult &Result) override {
        const auto* var_decl = Result.Nodes.getNodeAs<clang::VarDecl>("globalVar");
        if (var_decl && var_decl->isFileVarDecl()) {
            global_vars.insert(var_decl->getNameAsString());
        }
    }
};

int main(int argc, const char **argv) {
    llvm::cl::OptionCategory category("global-var-finder");
    auto expected_parser = clang::tooling::CommonOptionsParser::create(argc, argv, category);

    if (!expected_parser) {
        llvm::errs() << expected_parser.takeError();
        return 1;
    }

    auto& options_parser = expected_parser.get();
    auto& compilations = options_parser.getCompilations();
    const auto& source_paths = options_parser.getSourcePathList();
    std::ofstream ofs{"output.txt"};

    for (const auto& source_path : source_paths) {
        clang::tooling::ClangTool tool(compilations, {source_path});

        GlobalVarPrinter printer;

        clang::ast_matchers::DeclarationMatcher global_var_matcher = clang::ast_matchers::varDecl(
            clang::ast_matchers::isExpansionInMainFile(),
            clang::ast_matchers::hasGlobalStorage(),
            clang::ast_matchers::unless(clang::ast_matchers::parmVarDecl()),
            clang::ast_matchers::unless(clang::ast_matchers::isStaticLocal()),
            clang::ast_matchers::unless(clang::ast_matchers::isConstexpr()),
            clang::ast_matchers::unless(clang::ast_matchers::hasType(clang::ast_matchers::isConstQualified()))
        ).bind("globalVar");

        clang::ast_matchers::MatchFinder finder;
        finder.addMatcher(global_var_matcher, &printer);

        tool.run(clang::tooling::newFrontendActionFactory(&finder).get());

        // std::cout << llvm::sys::path::filename(source_path).str() << " ";
        // for (const auto& name : printer.global_vars)
        //     std::cout << name << " ";
        // std::cout << std::endl;
        ofs << llvm::sys::path::filename(source_path).str() << " ";
        for (const auto& name : printer.global_vars)
            ofs << name << " ";
        ofs << std::endl;
    }
    ofs.close();
    return 0;
}

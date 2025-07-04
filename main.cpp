#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <fstream>
#include <set>
#include <map>

struct CaseInsensitiveCompare {
    bool operator()(const std::string& s1, const std::string& s2) const {
        return std::ranges::lexicographical_compare(s1, s2, [](char c1, char c2) {
            return std::tolower(static_cast<unsigned char>(c1)) <
                  std::tolower(static_cast<unsigned char>(c2));
            }
        );
    }
};

class GlobalVarPrinter final : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
    std::map<std::string, std::set<std::string, CaseInsensitiveCompare>> global_vars;

    void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override {
        const auto *var_decl = result.Nodes.getNodeAs<clang::VarDecl>("globalVar");
        if (!var_decl || !var_decl->isFileVarDecl())
            return;
        const auto &source_manager = *result.SourceManager;
        const clang::SourceLocation loc = var_decl->getLocation();
        if (loc.isInvalid() || !loc.isFileID())
            return;
        global_vars[llvm::sys::path::filename(source_manager.getFilename(loc)).str()].insert(
            var_decl->getNameAsString());
    }
};

int main(int argc, const char **argv) {
    llvm::cl::OptionCategory category("global-var-finder");
    auto expected_parser = clang::tooling::CommonOptionsParser::create(argc, argv, category);

    if (!expected_parser) {
        llvm::errs() << expected_parser.takeError();
        return 1;
    }

    auto &options_parser = expected_parser.get();
    auto &compilations = options_parser.getCompilations();
    const auto &source_paths = options_parser.getSourcePathList();
    std::ofstream ofs{"output_without_constexpr.txt"};

    clang::tooling::ClangTool tool(compilations, source_paths);

    GlobalVarPrinter printer;

    clang::ast_matchers::DeclarationMatcher global_var_matcher = clang::ast_matchers::varDecl(
        clang::ast_matchers::isExpansionInMainFile(),
        clang::ast_matchers::hasGlobalStorage(),
        clang::ast_matchers::unless(clang::ast_matchers::parmVarDecl()),
        clang::ast_matchers::unless(clang::ast_matchers::isStaticLocal()),
        clang::ast_matchers::unless(clang::ast_matchers::hasType(clang::ast_matchers::isConstQualified()))
    ).bind("globalVar");

    clang::ast_matchers::MatchFinder finder;
    finder.addMatcher(global_var_matcher, &printer);

    tool.run(clang::tooling::newFrontendActionFactory(&finder).get());

    for (const auto &file: source_paths) {
        std::string filename = llvm::sys::path::filename(file).str();
        ofs << filename << " ";
        if (const auto it = printer.global_vars.find(filename); it != printer.global_vars.end()) {
            for (const auto &var_name: it->second) {
                ofs << var_name << " ";
            }
        }
        ofs << std::endl;
    }

    ofs.close();
    return 0;
}

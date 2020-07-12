#include "./HeaderFiles/DerivedNodes/ProgramNode.hpp"
#include <algorithm>
#include <memory>

extern int yyparse();
std::shared_ptr<ASTNamespace::ProgramNode> pNode;

int main(int argc, char* argv[])
{
    bool emitSourceCode = false;
    bool emitAssemblyCode = false;

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            std::string commandOptions(argv[i]);
            // std::cout << commandOptions << std::endl;
            std::transform(commandOptions.begin(), commandOptions.end(), commandOptions.begin(),
                           ::tolower);
            if (commandOptions.find("s") != std::string::npos)
            {
                emitSourceCode = true;
            }
            if (commandOptions.find("a") != std::string::npos)
            {
                emitAssemblyCode = true;
            }
        }
    }

    yyparse();
    globalSymbolTable.enterScope();
    if (emitAssemblyCode)
    {
        pNode->emit();
    }

    if (emitSourceCode)
    {
        pNode->emitSource();
    }
};

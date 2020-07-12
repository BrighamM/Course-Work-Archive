#ifndef PROGRAM_NODE_HPP
#define PROGRAM_NODE_HPP

#include "../AbstractNode.hpp"
#include "ConstantDeclarations/ConstantDeclNode.hpp"
#include "ProcedureAndFunctionDeclarations/BlockNode.hpp"
#include "ProcedureAndFunctionDeclarations/ProcedureAndFunctionDeclNode.hpp"
#include "TypeDeclarations/TypeDeclNode.hpp"
#include "VariableDeclarations/VarDeclNode.hpp"

// Program : ConstantDeclsList TypeDeclsList VarDeclsList ActualProcedureAndFunctionList Block
// DOT_TOKEN {pNode = std::make_shared<ASTNamespace::ProgramNode>($1,$2,$3,$4,$5);};

namespace ASTNamespace
{
class ProgramNode : public AbstractNode
{
    std::vector<ConstantDeclNode*>* constsList;
    std::vector<TypeDeclNode*>* typesList;
    std::vector<VarDeclNode*>* varsList;
    std::vector<ProcedureAndFunctionDeclNode*>* methodsList;
    BlockNode* mainCodeBlock;

  public:
    ProgramNode(std::vector<ConstantDeclNode*>* inputConstsList,
                std::vector<TypeDeclNode*>* inputTypesList,
                std::vector<VarDeclNode*>* inputVarsList,
                std::vector<ProcedureAndFunctionDeclNode*>* inputMethodsList, BlockNode* inputBlock)
        : constsList(inputConstsList), typesList(inputTypesList), varsList(inputVarsList),
          methodsList(inputMethodsList), mainCodeBlock(inputBlock)
    {
    }
    virtual void emit() const
    {
        if (constsList)
        {
            std::vector<ConstantDeclNode*> inlineConstsList = *constsList;
            for (int i = 0; i < inlineConstsList.size(); i++)
            {
                inlineConstsList[i]->emit();
            }
        }
        if (typesList)
        {
            std::vector<TypeDeclNode*> inlineTypesList = *typesList;
            for (int i = 0; i < inlineTypesList.size(); i++)
            {
                inlineTypesList[i]->emit();
            }
        }
        if (varsList)
        {
            std::vector<VarDeclNode*> inlineVarsList = *varsList;
            for (int i = 0; i < inlineVarsList.size(); i++)
            {
                inlineVarsList[i]->emit();
            }
        }
        if (methodsList)
        {
            std::vector<ProcedureAndFunctionDeclNode*> inlineMethodsList = *methodsList;
            for (int i = 0; i < inlineMethodsList.size(); i++)
            {
                inlineMethodsList[i]->putPrototypeOnSymbolTable();
            }
        }

        std::cout << "#***********************************************" << std::endl;
        std::cout << "#* PRINTING COMPILER BEGINNING SETUP SEQUENCE! *" << std::endl;
        std::cout << "#***********************************************" << std::endl;
        std::cout << "" << std::endl;
        std::cout << ".text" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "    la " << globalRegisterList.getGlobalPointerRegister() << " Global_Area"
                  << std::endl;
        std::cout << "    or " << globalRegisterList.getFramePointerRegister() << " "
                  << globalRegisterList.getStackPointerRegister() << " "
                  << globalRegisterList.getZeroRegister() << std::endl;
        std::cout << "    j main" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "#****************************************" << std::endl;
        std::cout << "#* BEGIN PROGRAM COMPILATION WITH MAIN! *" << std::endl;
        std::cout << "#****************************************" << std::endl;
        if (methodsList)
        {
            std::vector<ProcedureAndFunctionDeclNode*> inlineMethodsList = *methodsList;
            for (int i = 0; i < inlineMethodsList.size(); i++)
            {
                inlineMethodsList[i]->emit();
            }
        }
        std::cout << "" << std::endl;
        std::cout << "main:" << std::endl;
        std::cout << "" << std::endl;

        mainCodeBlock->emit();

        std::cout << "" << std::endl;
        std::cout << "#**********************************************" << std::endl;
        std::cout << "#* END OF PROGRAM COMPILATION!                *" << std::endl;
        std::cout << "#* NOW PRINTING PROGRAM TERMINATION SEQUENCE! *" << std::endl;
        std::cout << "#**********************************************" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "li " << globalRegisterList.getV_ZeroRegister() << " 10" << std::endl;
        std::cout << "syscall" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "#****************************************************" << std::endl;
        std::cout << "#* COMPLETED PRINTING PROGRAM TERMINATION SEQUENCE! *" << std::endl;
        std::cout << "#* NOW PRINTING DATA SECTION, AND GLOBAL AREA!      *" << std::endl;
        std::cout << "#****************************************************" << std::endl;
        std::cout << "" << std::endl;
        std::cout << ".data" << std::endl;
        globalSymbolTable.printDataStringsTable();
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << ".align 2" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "    Global_Area:" << std::endl;
        std::cout << "" << std::endl;
    }
    virtual void emitSource() const
    {
        if (constsList != NULL)
        {
            std::cout << "CONST" << std::endl;
            std::vector<ConstantDeclNode*> inlineConstsList = *constsList;
            for (int i = 0; i < inlineConstsList.size(); i++)
            {
                inlineConstsList[i]->emitSource();
            }
            std::cout << std::endl;
        }

        if (typesList != NULL)
        {
            std::cout << "TYPE" << std::endl;
            std::vector<TypeDeclNode*> inlineTypesList = *typesList;
            for (int i = 0; i < inlineTypesList.size(); i++)
            {
                inlineTypesList[i]->emitSource();
            }
            std::cout << std::endl;
        }

        if (varsList != NULL)
        {
            std::cout << "VAR" << std::endl;
            std::vector<VarDeclNode*> inlineVarsList = *varsList;
            for (int i = 0; i < inlineVarsList.size(); i++)
            {
                inlineVarsList[i]->emitSource();
            }
            std::cout << std::endl;
        }

        if (methodsList != NULL)
        {
            std::vector<ProcedureAndFunctionDeclNode*> inlineMethodsList = *methodsList;
            for (int i = 0; i < inlineMethodsList.size(); i++)
            {
                inlineMethodsList[i]->emitSource();
            }
            std::cout << std::endl;
        }

        mainCodeBlock->emitSource();
        std::cout << '.' << std::endl;
    }
    ~ProgramNode()
    {
        delete constsList;
        constsList = 0;
        delete typesList;
        typesList = 0;
        delete varsList;
        varsList = 0;
        delete methodsList;
        methodsList = 0;
        delete mainCodeBlock;
        mainCodeBlock = 0;
    }
};
} // namespace ASTNamespace

#endif
#ifndef FUNCTION_DECL_NODE_HPP
#define FUNCTION_DECL_NODE_HPP

#include "BodyNode.hpp"
#include "FunctionSignatureNode.hpp"
#include "ProcedureAndFunctionDeclNode.hpp"

// FunctionDecl : FunctionSignature SEMICOLON_TOKEN FORWARD_TOKEN SEMICOLON_TOKEN {$$ = new
// ASTNamespace::FunctionDeclNode($1);}
//              | FunctionSignature SEMICOLON_TOKEN Body SEMICOLON_TOKEN          {$$ = new
//              ASTNamespace::FunctionDeclNode($1,$3);};

namespace ASTNamespace
{
class FunctionDeclNode : public ProcedureAndFunctionDeclNode
{
    FunctionSignatureNode* functionSignature;
    BodyNode* body; // if body == NULL THIS IS A FORWARD
  public:
    FunctionDeclNode(FunctionSignatureNode* inputSignature)
        : functionSignature(inputSignature), body(NULL)
    {
    }
    FunctionDeclNode(FunctionSignatureNode* inputSignature, BodyNode* inputBody)
        : functionSignature(inputSignature), body(inputBody)
    {
    }
    virtual void emit() const
    {
        // MORE STUFF MUST HAPPEN HERE FIRST !!!;

        std::cout << "" << std::endl;
        // First make a label?
        std::cout << functionSignature->getFunctionName() << ":" << std::endl;

        std::cout << "or " << globalRegisterList.getFramePointerRegister() << " "
                  << globalRegisterList.getStackPointerRegister() << " "
                  << globalRegisterList.getZeroRegister() << std::endl;

        globalSymbolTable.pushNewScope();

        if (functionSignature->hasParams())
        {
            std::vector<FormalParametersListTypeNode*> paramList =
                functionSignature->getParametersList();
            for (int i = 0; i < paramList.size(); i++)
            {
                if (paramList[i]->getParamListType()->size() > 4)
                {

                    // bool listIsRef = paramList[i]->getRefBool();
                    globalSymbolTable.saveVarsListToSymbolTable(
                        paramList[i]->getStringIdentityList(), paramList[i]->getParamListType(),
                        paramList[i]->getParamListType()->size(),
                        globalRegisterList.getFramePointerRegister());
                }
                else
                {
                    // bool listIsRef = paramList[i]->getRefBool();
                    globalSymbolTable.saveVarsListToSymbolTable(
                        paramList[i]->getStringIdentityList(), paramList[i]->getParamListType(),
                        paramList[i]->getParamListType()->size(),
                        globalRegisterList.getFramePointerRegister());
                }
            }
        }

        body->emit();
        globalSymbolTable.popLastScope();
        std::cout << "jr " << globalRegisterList.getReturnAddressRegister() << std::endl;
    }
    virtual void emitSource() const
    {
        functionSignature->emitSource();
        std::cout << ";";
        if (body == NULL)
        {
            std::cout << "FORWARD;" << std::endl;
        }
        else
        {
            std::cout << std::endl;
            body->emitSource();
            std::cout << ";" << std::endl;
        }
    }
    virtual void putPrototypeOnSymbolTable() const
    {
        std::string identifierForSymbolTable = functionSignature->getFunctionName();
        std::vector<bool> myBoolVectorForSymbolTable;

        if (functionSignature->hasParams())
        {
            std::vector<FormalParametersListTypeNode*> paramList =
                functionSignature->getParametersList();
            for (int i = 0; i < paramList.size(); i++)
            {
                bool listIsRef = paramList[i]->getRefBool();
                std::vector<std::string> stringIdentityList = paramList[i]->getStringIdentityList();
                for (int j = 0; j < stringIdentityList.size(); j++)
                {
                    myBoolVectorForSymbolTable.emplace_back(listIsRef);
                }
            }
        }
        globalSymbolTable.storeProcedurePrototype(identifierForSymbolTable,
                                                  myBoolVectorForSymbolTable);
    }
    ~FunctionDeclNode()
    {
        delete functionSignature;
        functionSignature = 0;
        delete body;
        body = 0;
    }
};
} // namespace ASTNamespace

#endif
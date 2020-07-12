#ifndef FUNCTION_SIGNATURE_NODE_HPP
#define FUNCTION_SIGNATURE_NODE_HPP

#include "../../AbstractNode.hpp"
#include "../TypeNode.hpp"
#include "FormalParametersListTypeNode.hpp"
#include <vector>

// FunctionSignature : FUNCTION_TOKEN IDENTIFIER_TOKEN LEFT_PARENS_TOKEN FormalParametersList
// RIGHT_PARENS_TOKEN COLON_TOKEN Type {$$ = new ASTNamespace::FunctionSignatureNode($2,$4,$7);};

namespace ASTNamespace
{
class FunctionSignatureNode : public AbstractNode
{
    std::string identifierToken;
    std::vector<FormalParametersListTypeNode*>* formalParamList;
    TypeNode* type;

  public:
    FunctionSignatureNode(char* untouchedPointer,
                          std::vector<FormalParametersListTypeNode*>* inputList,
                          TypeNode* inputType)
        : identifierToken(untouchedPointer), formalParamList(inputList), type(inputType)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "FUNCTION " << identifierToken << "(";
        if (formalParamList != NULL)
        {
            std::vector<FormalParametersListTypeNode*> inlineFormalParameterList = *formalParamList;
            for (int i = 0; i < inlineFormalParameterList.size(); i++)
            {
                inlineFormalParameterList[i]->emitSource();
            }
        }
        std::cout << ")"
                  << ":";
        type->emitSource();
    }
    std::vector<FormalParametersListTypeNode*> getParametersList() { return *formalParamList; }
    bool hasParams()
    {
        if (formalParamList != NULL)
        {
            return true;
        }
        return false;
    }
    std::string getFunctionName() { return identifierToken; }
    ~FunctionSignatureNode()
    {
        delete formalParamList;
        formalParamList = 0;
        delete type;
        type = 0;
    }
};
} // namespace ASTNamespace

#endif
#ifndef PROCEDURE_SIGNATURE_NODE_HPP
#define PROCEDURE_SIGNATURE_NODE_HPP

#include "../../AbstractNode.hpp"
#include "FormalParametersListTypeNode.hpp"
#include <vector>

// ProcedureSignature : PROCEDURE_TOKEN IDENTIFIER_TOKEN LEFT_PARENS_TOKEN FormalParametersList
// RIGHT_PARENS_TOKEN {$$ = new ASTNamespace::ProcedureSignatureNode($2,$4);};

namespace ASTNamespace
{
class ProcedureSignatureNode : public AbstractNode
{
    std::string identifierToken;
    std::vector<FormalParametersListTypeNode*>* formalParamList;

  public:
    ProcedureSignatureNode(char* untouchedPointer,
                           std::vector<FormalParametersListTypeNode*>* inputList)
        : identifierToken(untouchedPointer), formalParamList(inputList)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "PROCEDURE " << identifierToken << "(";
        if (formalParamList != NULL)
        {
            std::vector<FormalParametersListTypeNode*> inlineFormalParameterList = *formalParamList;
            for (int i = 0; i < inlineFormalParameterList.size(); i++)
            {
                inlineFormalParameterList[i]->emitSource();
            }
        }
        std::cout << ")";
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
    std::string getProcedureName() { return identifierToken; }
    ~ProcedureSignatureNode()
    {
        delete formalParamList;
        formalParamList = 0;
    }
};
} // namespace ASTNamespace

#endif
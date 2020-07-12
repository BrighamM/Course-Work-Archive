#ifndef FORMAL_PARAMETERS_LIST_TYPE_NODE_HPP
#define FORMAL_PARAMETERS_LIST_TYPE_NODE_HPP

#include "../TypeNode.hpp"
#include <vector>

namespace ASTNamespace
{
class FormalParametersListTypeNode : public AbstractNode
{
    std::vector<char*>* identifierList; // Identifier List
    TypeNode* type;
    bool listIsRef;

  public:
    FormalParametersListTypeNode(bool inputIsRefList, std::vector<char*>* untouchedPointer,
                                 TypeNode* incomingType)
        : listIsRef(inputIsRefList), identifierList(untouchedPointer), type(incomingType)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::vector<char*> inlineIdentifierList = *identifierList;
        std::vector<std::string> inlineStringIdentifierList;
        for (int i = 0; i < inlineIdentifierList.size(); i++)
        {
            inlineStringIdentifierList.push_back(inlineIdentifierList[i]);
        }
        if (listIsRef)
        {
            std::cout << "REF ";
        }
        else
        {
            std::cout << "VAR ";
        }
        for (int i = 0; i < inlineStringIdentifierList.size(); i++)
        {
            std::cout << inlineStringIdentifierList[i];
            if (i != inlineStringIdentifierList.size() - 1)
            {
                std::cout << ",";
            }
        }
        std::cout << ":";
        type->emitSource();
        std::cout << ";";
    }

    std::shared_ptr<SymbolTableType> getParamListType()
    {
        return type->getSymbolTableTypeForVarDecl();
    }
    std::vector<std::string> getStringIdentityList()
    {
        std::vector<char*> inlineIdentifierList = *identifierList;
        std::vector<std::string> inlineStringIdentifierList;
        for (int i = 0; i < inlineIdentifierList.size(); i++)
        {
            inlineStringIdentifierList.push_back(inlineIdentifierList[i]);
        }
        return inlineStringIdentifierList;
    }
    bool getRefBool() { return listIsRef; }
    ~FormalParametersListTypeNode()
    {
        delete identifierList;
        identifierList = 0;
        delete type;
        type = 0;
    }
};
} // namespace ASTNamespace

#endif
#ifndef FIELD_DECL_NODE_HPP
#define FIELD_DECL_NODE_HPP

#include "../../AbstractNode.hpp"
#include "../TypeNode.hpp"
#include <vector>

// FieldDecl : IdentList COLON_TOKEN Type SEMICOLON_TOKEN {$$ = new
// ASTNamespace::FieldDeclNode($1,$3);};

namespace ASTNamespace
{
class FieldDeclNode : public AbstractNode
{
    std::vector<char*>* identifierList;
    TypeNode* type;

  public:
    FieldDeclNode(std::vector<char*>* inputIdentifierList, TypeNode* inputType)
        : identifierList(inputIdentifierList), type(inputType)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    std::vector<std::string> getStringIdList()
    {
        std::vector<char*> inlineIdentifierList = *identifierList;
        std::vector<std::string> inlineStringIdentifierList;
        for (int i = 0; i < inlineIdentifierList.size(); i++)
        {
            inlineStringIdentifierList.push_back(inlineIdentifierList[i]);
        }
        return inlineStringIdentifierList;
    }
    std::shared_ptr<SymbolTableType> getSymbolTableType() { return type->getSymbolTableType(); }
    virtual void emitSource() const
    {
        std::vector<char*> inlineIdentifierList = *identifierList;
        std::vector<std::string> inlineStringIdentifierList;
        for (int i = 0; i < inlineIdentifierList.size(); i++)
        {
            inlineStringIdentifierList.push_back(inlineIdentifierList[i]);
        }
        for (int i = 0; i < inlineStringIdentifierList.size(); i++)
        {
            std::cout << inlineStringIdentifierList[i];
            std::cout << ":";
            type->emitSource();
            std::cout << ";" << std::endl;
        }
    }
    ~FieldDeclNode()
    {
        delete identifierList;
        identifierList = 0;
        delete type;
        type = 0;
    }
};
} // namespace ASTNamespace

#endif
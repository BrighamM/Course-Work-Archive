#ifndef SIMPLE_TYPE_NODE_HPP
#define SIMPLE_TYPE_NODE_HPP

#include "../TypeNode.hpp"

// SimpleType : IDENTIFIER_TOKEN {$$ = new ASTNamespace::SimpleTypeNode($1);};

namespace ASTNamespace
{
class SimpleTypeNode : public TypeNode
{
    std::string identifierToken; // Identifier Token, i.e.  "integer"
  public:
    SimpleTypeNode(char* untouchedPointer) : identifierToken(untouchedPointer) {}
    virtual std::shared_ptr<SymbolTableType> getSymbolTableType() const
    {
        if (globalSymbolTable.isTypeIdentifierInSymbolTable(toString()))
        {
            return globalSymbolTable.getTypeType(toString());
        }
        else
        {
            // COMPLAIN BITTERLY AND WRITE TO ERROR
            std::cout << "MAJOR ERRORS IN SimpleTYPE NODE!!! " << std::endl;
        }
        return SymbolTableIntType::get();
    }
    virtual std::shared_ptr<SymbolTableType> getSymbolTableTypeForVarDecl() const
    {
        if (globalSymbolTable.isTypeIdentifierInSymbolTable(identifierToken))
        {
            std::shared_ptr<SymbolTableType> typeType =
                globalSymbolTable.getTypeType(identifierToken);
            return typeType;
        }
        else
        {
            std::cout << "Simple Type Node error !!!!!!!!!!" << std::endl;
            return nullptr;
        }
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const { std::cout << identifierToken; }
    virtual std::string toString() const { return identifierToken; }
    ~SimpleTypeNode() {}
};
} // namespace ASTNamespace

#endif
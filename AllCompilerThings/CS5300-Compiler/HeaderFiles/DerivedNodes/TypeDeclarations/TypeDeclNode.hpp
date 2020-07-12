#ifndef TYPE_DECL_NODE_HPP
#define TYPE_DECL_NODE_HPP

#include "../TypeNode.hpp"
#include "ArrayTypeNode.hpp"
#include "RecordTypeNode.hpp"
#include "SimpleTypeNode.hpp"

// TypeDecl : IDENTIFIER_TOKEN EQUIVALENCE_TOKEN Type SEMICOLON_TOKEN {$$ = new
// ASTNamespace::TypeDeclNode($1,$3);};

namespace ASTNamespace
{
class TypeDeclNode : public AbstractNode
{
    std::string identifierToken;
    TypeNode* type;

  public:
    TypeDeclNode(char* untouchedPointer, TypeNode* incomingType)
        : identifierToken(untouchedPointer), type(incomingType)
    {
    }
    virtual void emit() const
    {
        /**
         * In this type decl node I have two things, an identifier, and a type
         * I need to take the lhs(identifier) and store it in the
         * type-symbol-table with the resulting lookup from
         * the rhs(type->)
         */
        if (dynamic_cast<SimpleTypeNode*>(type))
        {
            // SYMBOL TABLE LOOKUP WITH
            // dynamic_cast<SimpleTypeNode*>(incomingType)->toString()
            std::string typeToString = dynamic_cast<SimpleTypeNode*>(type)->toString();
            if (globalSymbolTable.isTypeIdentifierInSymbolTable(typeToString))
            {
                std::shared_ptr<SymbolTableType> typeType =
                    globalSymbolTable.getTypeType(typeToString);
                globalSymbolTable.saveTypeToSymbolTable(identifierToken, typeType);
            }
            else
            {
                // COMPLAIN BITTERLY AND WRITE OUT ERROR
                std::cout << "type decl node error !!!!!!!!!!" << std::endl;
            }
        }
        else if (dynamic_cast<ArrayTypeNode*>(type))
        {
            // std::cout << "This should be the first thing that happens... typedeclnode "
            //           << identifierToken << std::endl;
            std::shared_ptr<SymbolTableType> typeType = type->getSymbolTableType();
            globalSymbolTable.saveTypeToSymbolTable(identifierToken, typeType);
        }
        else if (dynamic_cast<RecordTypeNode*>(type))
        {
            std::shared_ptr<SymbolTableType> typeType = type->getSymbolTableType();
            globalSymbolTable.saveTypeToSymbolTable(identifierToken, typeType);
        }
        else
        {
            std::cout << "We be ERROR type-ing mon." << std::endl;
        }
    }
    virtual void emitSource() const
    {
        std::cout << identifierToken << " = ";
        type->emitSource();
        std::cout << ";" << std::endl;
    }
    ~TypeDeclNode()
    {
        delete type;
        type = 0;
    }
};
} // namespace ASTNamespace

#endif
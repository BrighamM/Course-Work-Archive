#ifndef VAR_DECL_NODE_HPP
#define VAR_DECL_NODE_HPP

#include "../../AbstractNode.hpp"
#include "../TypeDeclarations/ArrayTypeNode.hpp"
#include "../TypeDeclarations/RecordTypeNode.hpp"
#include "../TypeDeclarations/SimpleTypeNode.hpp"
#include "../TypeNode.hpp"
#include <vector>

// VarDecl : IdentList COLON_TOKEN Type SEMICOLON_TOKEN {$$ = new
// ASTNamespace::VarDeclNode($1,$3);};

namespace ASTNamespace
{
class VarDeclNode : public AbstractNode
{
    std::vector<char*>* identifierList;
    TypeNode* type;

  public:
    VarDeclNode(std::vector<char*>* untouchedPointer, TypeNode* inputType)
        : identifierList(untouchedPointer), type(inputType)
    {
    }

    virtual void emit() const
    {
        // Take untouched pointer and turn it into a vector of identifiers.
        std::vector<char*> inlineIdentifierList = *identifierList;
        std::vector<std::string> inlineStringIdentifierList;
        for (int i = 0; i < inlineIdentifierList.size(); i++)
        {
            inlineStringIdentifierList.push_back(inlineIdentifierList[i]);
        }

        std::shared_ptr<SymbolTableType> symbolTableType;
        if (globalSymbolTable.isTypeIdentifierInSymbolTable(type->toString()))
        {
            symbolTableType = globalSymbolTable.getTypeType(type->toString());
        }
        else
        {
            symbolTableType = type->getSymbolTableTypeForVarDecl();
        }

        // HERE IS WHERE I NEED TO CHECK IF S.T. SCOPES IS GREATER THAN 2... OR SOMETHING

        if (globalSymbolTable.shouldUseFramePointer())
        {
            globalSymbolTable.saveVarsListToSymbolTable(
                inlineStringIdentifierList, symbolTableType, symbolTableType->size(),
                globalRegisterList.getFramePointerRegister());
        }
        else
        {
            globalSymbolTable.saveVarsListToSymbolTable(
                inlineStringIdentifierList, symbolTableType, symbolTableType->size(),
                globalRegisterList.getGlobalPointerRegister());
        }

        // std::cout << "FOURTH THING THAT SHOULD HAPPEN var decl node "
        //           << inlineStringIdentifierList.front() << " " << type->toString() << "
        //           type->size"
        //           << symbolTableType->size() << std::endl;

        /**
         *  Preachy time. I am inside of a vardecl node that is being created. Thus I should always
         * have a type That I can look up through toString of the typenode with the symbol table.
         *
         *  First I should check that my type is in the symbol table, if it is proceed as normal,
         * otherwise complain bitterly.
         */
    }
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
    ~VarDeclNode()
    {
        delete identifierList;
        identifierList = 0;
        delete type;
        type = 0;
    }
};
} // namespace ASTNamespace

#endif
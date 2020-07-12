#ifndef CONSTANT_DECL_NODE_HPP
#define CONSTANT_DECL_NODE_HPP

#include "../../AbstractNode.hpp"
#include "../ExpressionNodes/CHARCONSTExpressionNode.hpp"
#include "../ExpressionNodes/EquivalenceExpressionNode.hpp"
#include "../ExpressionNodes/ExpressionNode.hpp"
#include "../ExpressionNodes/INTEGERExpressionNode.hpp"
#include "../ExpressionNodes/LVALExpressionNode.hpp"
#include "../ExpressionNodes/STRINGExpressionNode.hpp"

// ConstantDecl : IDENTIFIER_TOKEN EQUIVALENCE_TOKEN Expression SEMICOLON_TOKEN {$$ = new
// ASTNamespace::ConstantDeclNode($1,$3);};

namespace ASTNamespace
{
class ConstantDeclNode : public AbstractNode
{
    std::string identifierToken;
    ExpressionNode* expression;

  public:
    ConstantDeclNode(char* untouchedPointer, ExpressionNode* incomingExpression)
        : identifierToken(untouchedPointer), expression(incomingExpression)
    {
    }
    virtual void emit() const
    {
        if (expression->getType() == SymbolTableIntType::get())
        {
            globalSymbolTable.saveConstIntToSymbolTable(identifierToken, expression->getIntValue());
        }
        if (expression->getType() == SymbolTableCharType::get())
        {
            globalSymbolTable.saveConstCharToSymbolTable(identifierToken,
                                                         expression->getCharValue());
        }
        if (expression->getType() == SymbolTableBoolType::get())
        {
            globalSymbolTable.saveConstBoolToSymbolTable(identifierToken,
                                                         expression->getBoolValue());
        }
        if (expression->getType() == SymbolTableStringType::get())
        {
            globalSymbolTable.saveConstStringToSymbolTable(identifierToken,
                                                           expression->getStringValue());
        }
    }
    virtual void emitSource() const
    {
        std::cout << identifierToken << " = ";
        expression->emitSource();
        std::cout << ";" << std::endl;
    }
    ~ConstantDeclNode()
    {
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
#ifndef PARENS_EXPRESSION_NODE_HPP
#define PARENS_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN {$$ = new
// ASTNamespace::ParensExpressionNode($2);}
namespace ASTNamespace
{
class ParensExpressionNode : public ExpressionNode
{
    ExpressionNode* expression;

  public:
    ParensExpressionNode(ExpressionNode* inputExpression) : expression(inputExpression) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "(";
        expression->emitSource();
        std::cout << ")";
    }
    virtual PsuedoRegister getTheeIntoRegister() const { return expression->getTheeIntoRegister(); }
    virtual std::shared_ptr<SymbolTableType> getType() const { return expression->getType(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const { return false; }
    ~ParensExpressionNode()
    {
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
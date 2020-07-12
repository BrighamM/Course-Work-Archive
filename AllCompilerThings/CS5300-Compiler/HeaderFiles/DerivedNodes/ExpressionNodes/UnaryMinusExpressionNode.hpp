#ifndef UNARY_MINUS_EXPRESSION_NODE_HPP
#define UNARY_MINUS_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// SUBTRACTION_TOKEN Expression %prec UNARY_MINUS_TOKEN {$$ = new
// ASTNamespace::UnaryMinusExpressionNode($2);}
namespace ASTNamespace
{
class UnaryMinusExpressionNode : public ExpressionNode
{
    ExpressionNode* expression;

  public:
    UnaryMinusExpressionNode(ExpressionNode* inputExpression) : expression(inputExpression) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "-";
        expression->emitSource();
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        std::cout << "Not Yet Implemented!!! " << std::endl;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return SymbolTableIntType::get(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const
    {
        if (expression->getType() == SymbolTableCharType::get())
        {
            std::cout << "ERROR WITH TYPES UnaryMinusExpressionNode" << std::endl;
            return false;
        }
        if (expression->getType() == SymbolTableIntType::get())
        {
            return expression->getIntValue() * -1;
        }
        if (expression->getType() == SymbolTableBoolType::get())
        {
            return expression->getBoolValue() * -1;
        }
        if (expression->getType() == SymbolTableStringType::get())
        {
            std::cout << "ERROR WITH TYPES UnaryMinusExpressionNode" << std::endl;
            return false;
        }
        else
        {
            std::cout << "ERROR WITH TYPES UnaryMinusExpressionNode" << std::endl;
            return false;
        }
    }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const { return false; }
    ~UnaryMinusExpressionNode()
    {
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
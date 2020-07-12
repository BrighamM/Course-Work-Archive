#ifndef PRED_EXPRESSION_NODE_HPP
#define PRED_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// PRED_TOKEN LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN {$$ = new
// ASTNamespace::PRED_ExpressionNode($3);}
namespace ASTNamespace
{
class PRED_ExpressionNode : public ExpressionNode
{
    ExpressionNode* expression;

  public:
    PRED_ExpressionNode(ExpressionNode* inputExpression) : expression(inputExpression) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "PRED(";
        expression->emitSource();
        std::cout << ")";
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        std::cout << "Not Yet Implemented!!!" << std::endl;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return expression->getType(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const { return false; }
    ~PRED_ExpressionNode()
    {
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
#ifndef GREATER_THAN_OR_EQUAL_EXPRESSION_NODE_HPP
#define GREATER_THAN_OR_EQUAL_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// Expression GREATER_THAN_OR_EQUAL_TOKEN Expression {$$ = new
// ASTNamespace::GreaterThanOrEqualExpressionNode($1,$3);}
namespace ASTNamespace
{
class GreaterThanOrEqualExpressionNode : public ExpressionNode
{
    ExpressionNode* leftExpression;
    ExpressionNode* rightExpression;

  public:
    GreaterThanOrEqualExpressionNode(ExpressionNode* inputLhs, ExpressionNode* inputRhs)
        : leftExpression(inputLhs), rightExpression(inputRhs)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        leftExpression->emitSource();
        std::cout << ">=";
        rightExpression->emitSource();
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        PsuedoRegister lhsRegister = leftExpression->getTheeIntoRegister();
        PsuedoRegister rhsRegister = rightExpression->getTheeIntoRegister();
        std::cout << "sge " << lhsRegister.getRegisterName() << " " << lhsRegister.getRegisterName()
                  << " " << rhsRegister.getRegisterName() << std::endl;
        return lhsRegister;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return SymbolTableBoolType::get(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const
    {
        if (leftExpression->getType() != rightExpression->getType())
        {
            std::cout << "ERROR WITH TYPES GreaterThanOrEqualExpressionNode" << std::endl;
            return false;
        }
        else if (leftExpression->getType() == SymbolTableCharType::get())
        {
            return leftExpression->getCharValue() >= rightExpression->getCharValue();
        }
        else if (leftExpression->getType() == SymbolTableStringType::get())
        {
            return leftExpression->getStringValue() >= rightExpression->getStringValue();
        }
        else if (leftExpression->getType() == SymbolTableBoolType::get())
        {
            return leftExpression->getBoolValue() >= rightExpression->getBoolValue();
        }
        else if (leftExpression->getType() == SymbolTableIntType::get())
        {
            return leftExpression->getIntValue() >= rightExpression->getIntValue();
        }
        else
        {
            std::cout << "ERROR WITH TYPES GreaterThanOrEqualExpressionNode" << std::endl;
            return false;
        }
    }
    ~GreaterThanOrEqualExpressionNode()
    {
        delete leftExpression;
        leftExpression = 0;
        delete rightExpression;
        rightExpression = 0;
    }
};
} // namespace ASTNamespace

#endif
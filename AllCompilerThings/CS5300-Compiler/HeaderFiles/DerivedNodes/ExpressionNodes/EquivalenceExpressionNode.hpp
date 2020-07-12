#ifndef EQUIVALENCE_EXPRESSION_NODE_HPP
#define EQUIVALENCE_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// Expression EQUIVALENCE_TOKEN Expression {$$ = new
// ASTNamespace::EquivalenceExpressionNode($1,$3);}
namespace ASTNamespace
{
class EquivalenceExpressionNode : public ExpressionNode
{
    ExpressionNode* leftExpression;
    ExpressionNode* rightExpression;

  public:
    EquivalenceExpressionNode(ExpressionNode* inputLhs, ExpressionNode* inputRhs)
        : leftExpression(inputLhs), rightExpression(inputRhs)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        leftExpression->emitSource();
        std::cout << "=";
        rightExpression->emitSource();
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        PsuedoRegister lhsRegister = leftExpression->getTheeIntoRegister();
        PsuedoRegister rhsRegister = rightExpression->getTheeIntoRegister();
        std::cout << "seq " << lhsRegister.getRegisterName() << " " << lhsRegister.getRegisterName()
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
            std::cout << "ERROR WITH TYPES EquivalenceExpressionNode" << std::endl;
            return false;
        }
        else if (leftExpression->getType() == SymbolTableCharType::get())
        {
            return leftExpression->getCharValue() == rightExpression->getCharValue();
        }
        else if (leftExpression->getType() == SymbolTableStringType::get())
        {
            return leftExpression->getStringValue() == rightExpression->getStringValue();
        }
        else if (leftExpression->getType() == SymbolTableBoolType::get())
        {
            return leftExpression->getBoolValue() == rightExpression->getBoolValue();
        }
        else if (leftExpression->getType() == SymbolTableIntType::get())
        {
            return leftExpression->getIntValue() == rightExpression->getIntValue();
        }
        else
        {
            std::cout << "ERROR WITH TYPES EquivalenceExpressionNode" << std::endl;
            return false;
        }
    }
    ~EquivalenceExpressionNode()
    {
        delete leftExpression;
        leftExpression = 0;
        delete rightExpression;
        rightExpression = 0;
    }
};
} // namespace ASTNamespace

#endif
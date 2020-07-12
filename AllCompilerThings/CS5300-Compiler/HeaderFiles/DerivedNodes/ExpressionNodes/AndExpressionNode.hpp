#ifndef AND_EXPRESSION_NODE_HPP
#define AND_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// Expression AND_TOKEN Expression {$$ = new ASTNamespace::AndExpressionNode($1,$3);}
namespace ASTNamespace
{
class AndExpressionNode : public ExpressionNode
{
    ExpressionNode* leftExpression;
    ExpressionNode* rightExpression;

  public:
    AndExpressionNode(ExpressionNode* inputLhs, ExpressionNode* inputRhs)
        : leftExpression(inputLhs), rightExpression(inputRhs)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        leftExpression->emitSource();
        std::cout << "&";
        rightExpression->emitSource();
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        PsuedoRegister lhsRegister = leftExpression->getTheeIntoRegister();
        PsuedoRegister rhsRegister = rightExpression->getTheeIntoRegister();
        // Bitwise AND
        std::cout << "and " << lhsRegister.getRegisterName() << " " << lhsRegister.getRegisterName()
                  << " " << rhsRegister.getRegisterName() << std::endl;
        // Absolute Value
        std::cout << "abs " << lhsRegister.getRegisterName() << " "
                  << lhsRegister.getRegisterName();
        // If the absolute value is greater than zero...
        std::cout << "sgt " << lhsRegister.getRegisterName() << " " << lhsRegister.getRegisterName()
                  << " " << globalRegisterList.getZeroRegister();
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
            std::cout << "ERROR WITH TYPES AndExpressionNode" << std::endl;
            return false;
        }
        else if (leftExpression->getType() == SymbolTableCharType::get())
        {
            return leftExpression->getCharValue() && rightExpression->getCharValue();
        }
        else if (leftExpression->getType() == SymbolTableStringType::get())
        {
            std::cout << "ERROR WITH TYPES AndExpressionNode" << std::endl;
            return false;
        }
        else if (leftExpression->getType() == SymbolTableBoolType::get())
        {
            return leftExpression->getBoolValue() && rightExpression->getBoolValue();
        }
        else if (leftExpression->getType() == SymbolTableIntType::get())
        {
            return leftExpression->getIntValue() && rightExpression->getIntValue();
        }
        else
        {
            std::cout << "ERROR WITH TYPES AndExpressionNode" << std::endl;
            return false;
        }
    }
    ~AndExpressionNode()
    {
        delete leftExpression;
        leftExpression = 0;
        delete rightExpression;
        rightExpression = 0;
    }
};
} // namespace ASTNamespace

#endif
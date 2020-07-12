#ifndef SUCC_EXPRESSION_NODE_HPP
#define SUCC_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// SUCC_TOKEN LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN {$$ = new
// ASTNamespace::SUCC_ExpressionNode($3);}
namespace ASTNamespace
{
class SUCC_ExpressionNode : public ExpressionNode
{
    ExpressionNode* expression;

  public:
    SUCC_ExpressionNode(ExpressionNode* inputExpression) : expression(inputExpression) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "SUCC(";
        expression->emitSource();
        std::cout << ")";
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        PsuedoRegister psuedoRegister = expression->getTheeIntoRegister();
        std::cout << "addi " << psuedoRegister.getRegisterName() << " "
                  << psuedoRegister.getRegisterName() << " 1 " << std::endl;
        return psuedoRegister;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return expression->getType(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const { return false; }
    ~SUCC_ExpressionNode()
    {
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
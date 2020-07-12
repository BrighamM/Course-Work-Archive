#ifndef ORD_EXPRESSION_NODE_HPP
#define ORD_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

/* FROM CHAR TO INT */
// ORD_TOKEN LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN {$$ = new
// ASTNamespace::ORD_ExpressionNode($3);}
namespace ASTNamespace
{
class ORD_ExpressionNode : public ExpressionNode
{
    ExpressionNode* expression;

  public:
    ORD_ExpressionNode(ExpressionNode* inputExpression) : expression(inputExpression) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "ORD(";
        expression->emitSource();
        std::cout << ")";
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        if (expression->getType() == SymbolTableCharType::get())
        {
            return expression->getTheeIntoRegister();
        }
        else
        {
            std::cout << "We have major issues in ORD" << std::endl;
        }
        PsuedoRegister psuedoRegister;
        return psuedoRegister;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return SymbolTableIntType::get(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const { return false; }
    ~ORD_ExpressionNode()
    {
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
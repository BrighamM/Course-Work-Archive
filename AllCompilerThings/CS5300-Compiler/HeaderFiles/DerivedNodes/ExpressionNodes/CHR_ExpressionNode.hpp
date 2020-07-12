#ifndef CHR_EXPRESSION_NODE_HPP
#define CHR_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

/* FROM INT TO CHAR */
// CHR_TOKEN LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN {$$ = new
// ASTNamespace::CHR_ExpressionNode($3);}
namespace ASTNamespace
{
class CHR_ExpressionNode : public ExpressionNode
{
    ExpressionNode* expression;

  public:
    CHR_ExpressionNode(ExpressionNode* inputExpression) : expression(inputExpression) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "CHR(";
        expression->emitSource();
        std::cout << ")";
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        if (expression->getType() == SymbolTableIntType::get())
        {
            return expression->getTheeIntoRegister();
        }
        else
        {
            std::cout << "We have major issues in CHR" << std::endl;
        }
        PsuedoRegister psuedoRegister;
        return psuedoRegister;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return SymbolTableCharType::get(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const { return false; }
    ~CHR_ExpressionNode()
    {
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
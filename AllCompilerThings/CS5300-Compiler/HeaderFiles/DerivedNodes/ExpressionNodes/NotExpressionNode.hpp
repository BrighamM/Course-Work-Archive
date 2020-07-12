#ifndef NOT_EXPRESSION_NODE_HPP
#define NOT_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// NOT_TOKEN Expression {$$ = new ASTNamespace::NotExpressionNode($2);}
namespace ASTNamespace
{
class NotExpressionNode : public ExpressionNode
{
    ExpressionNode* expression;

  public:
    NotExpressionNode(ExpressionNode* inputExpression) : expression(inputExpression) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "~";
        expression->emitSource();
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        // CAREFUL!!! Past Brigham Worked really hard on this.
        PsuedoRegister psuedoRegister = expression->getTheeIntoRegister();
        // Absolute Value
        std::cout << "abs " << psuedoRegister.getRegisterName() << " "
                  << psuedoRegister.getRegisterName();
        // If the absolute value is greater than zero...
        std::cout << "sgt " << psuedoRegister.getRegisterName() << " "
                  << psuedoRegister.getRegisterName() << " "
                  << globalRegisterList.getZeroRegister();
        // Now psuedoRegister is holding a 1 or a zero... We just need to flip it.
        std::cout << "sle " << psuedoRegister.getRegisterName() << " "
                  << psuedoRegister.getRegisterName() << " "
                  << globalRegisterList.getZeroRegister();
        return psuedoRegister;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return SymbolTableBoolType::get(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const
    {
        if (expression->getType() == SymbolTableBoolType::get())
        {
            return !expression->getBoolValue();
        }
        else if (expression->getType() == SymbolTableCharType::get())
        {
            return !expression->getCharValue();
        }
        else if (expression->getType() == SymbolTableIntType::get())
        {
            return !expression->getIntValue();
        }
        else if (expression->getType() == SymbolTableStringType::get())
        {
            std::cout << "ERROR WITH TYPES NotExpressionNode" << std::endl;
            return false;
        }
        else
        {
            std::cout << "ERROR WITH TYPES NotExpressionNode" << std::endl;
            return false;
        }
    }
    ~NotExpressionNode()
    {
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
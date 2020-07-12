#ifndef INTEGER_EXPRESSION_NODE_HPP
#define INTEGER_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// INTEGER_TOKEN {$$ = new ASTNamespace::INTEGERExpressionNode($1);}
namespace ASTNamespace
{
class INTEGERExpressionNode : public ExpressionNode
{
    int integerValue;

  public:
    INTEGERExpressionNode(int inputInt) : integerValue(inputInt) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const { std::cout << integerValue; }
    virtual int getIntegerValue() const { return integerValue; }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        /**
         * 1. Request a register from the register pool
         *
         */
        PsuedoRegister psuedoRegister;
        std::cout << "li " << psuedoRegister.getRegisterName() << " " << integerValue << std::endl;
        return psuedoRegister;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return SymbolTableIntType::get(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return integerValue; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const { return false; }
    ~INTEGERExpressionNode() {}
};
} // namespace ASTNamespace

#endif
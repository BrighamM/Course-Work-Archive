#ifndef LVAL_EXPRESSION_NODE_HPP
#define LVAL_EXPRESSION_NODE_HPP

#include "../LValueNode.hpp"
#include "ExpressionNode.hpp"
#include <cstring>

// LValue {$$ = new ASTNamespace::LvalExpressionNode($1);}
namespace ASTNamespace
{
class LvalExpressionNode : public ExpressionNode
{
    LValueNode* lValue;

  public:
    LvalExpressionNode(LValueNode* inputLValue) : lValue(inputLValue) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const { lValue->emitSource(); }
    LValueNode* getMyLValue() { return lValue; }
    virtual PsuedoRegister getTheeIntoRegister() const { return lValue->getTheeIntoRegister(); }
    virtual PsuedoRegister getThyAddressIntoRegister() const
    {
        return lValue->getThyAddressIntoRegister();
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return lValue->getType(); }
    std::string getIdentifier() const { return lValue->getIdentifier(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const
    {
        /**
         * This is all wrong!!!
         * in registerLand I need to get the value of I from the GlobalPointer and shove it into a
         * register. Once it is in a register I can take it and shove it into the global pointer.
         * Which is what happens thanks to the assignment Statement Node. But I need to get whatever
         * value is saved off in the symbol table into it's own register and then save that off into
         * the globale pointer. then I can do a simple look up when I do my write.
         *
         */
        // This must be a constant decl
        return globalSymbolTable.getConstIntValue(lValue->getIdentifier());
    }
    virtual std::string getStringValue() const { return getIdentifier(); }
    virtual char getCharValue() const { return getIdentifier()[0]; }
    virtual bool getBoolValue() const
    {
        return globalStringConstants.getLowerCaseTrueString() == getIdentifier();
    }
    ~LvalExpressionNode()
    {
        delete lValue;
        lValue = 0;
    }
};
} // namespace ASTNamespace

#endif
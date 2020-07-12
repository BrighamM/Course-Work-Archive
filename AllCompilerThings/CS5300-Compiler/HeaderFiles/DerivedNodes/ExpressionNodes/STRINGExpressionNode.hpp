#ifndef STRING_EXPRESSION_NODE_HPP
#define STRING_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// STRING_TOKEN {$$ = new ASTNamespace::STRINGExpressionNode($1);}
namespace ASTNamespace
{
class STRINGExpressionNode : public ExpressionNode
{
  public:
    STRINGExpressionNode(char* untouchedPointer) : stringExpression(untouchedPointer) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const { std::cout << stringExpression; }
    std::string getStringExpression() const { return stringExpression; }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        PsuedoRegister psuedoRegister;
        std::string stringLabel = globalSymbolTable.getDataStringLabel(getStringExpression());
        std::cout << "la " << psuedoRegister.getRegisterName() << " " << stringLabel << std::endl;
        return psuedoRegister;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const
    {
        return SymbolTableStringType::get();
    }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return stringExpression; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const { return false; }
    ~STRINGExpressionNode() {}

  private:
    std::string stringExpression;
};
} // namespace ASTNamespace

#endif
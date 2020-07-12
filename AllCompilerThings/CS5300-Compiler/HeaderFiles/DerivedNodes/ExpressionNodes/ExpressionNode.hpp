#ifndef EXPRESSION_NODE_HPP
#define EXPRESSION_NODE_HPP

#include "../../AbstractNode.hpp"

namespace ASTNamespace
{
class ExpressionNode : public AbstractNode
{
  public:
    ExpressionNode() {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << "EXPRESSION NODE PARENT CLASS ERROR ERROR!" << std::endl;
    }
    virtual PsuedoRegister getTheeIntoRegister() const = 0;
    virtual std::shared_ptr<SymbolTableType> getType() const = 0;
    virtual int getIntValue() const = 0;
    virtual std::string getStringValue() const = 0;
    virtual char getCharValue() const = 0;
    virtual bool getBoolValue() const = 0;
    ~ExpressionNode() {}
};
} // namespace ASTNamespace

#endif
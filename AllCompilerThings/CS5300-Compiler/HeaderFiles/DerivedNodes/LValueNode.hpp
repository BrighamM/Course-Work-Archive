#ifndef LVAL_MVAL_HPP
#define LVAL_MVAL_HPP

#include "../AbstractNode.hpp"

namespace ASTNamespace
{
class LValueNode : public AbstractNode
{
  public:
    LValueNode() {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const { std::cout << "I am the program!!!!" << std::endl; }
    virtual PsuedoRegister getThyAddressIntoRegister() const = 0;
    virtual PsuedoRegister getTheeIntoRegister() const = 0;
    virtual std::shared_ptr<SymbolTableType> getType() = 0;
    virtual std::string getIdentifier() const = 0;
    ~LValueNode() {}
};
} // namespace ASTNamespace

#endif
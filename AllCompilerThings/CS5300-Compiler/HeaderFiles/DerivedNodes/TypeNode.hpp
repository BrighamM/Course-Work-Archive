#ifndef TYPE_NODE_HPP
#define TYPE_NODE_HPP

#include "../AbstractNode.hpp"
#include <string>

namespace ASTNamespace
{
class TypeNode : public AbstractNode
{
  public:
    TypeNode() {}
    virtual std::shared_ptr<SymbolTableType> getSymbolTableType() const = 0;
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual std::shared_ptr<SymbolTableType> getSymbolTableTypeForVarDecl() const = 0;
    virtual void emitSource() const { std::cout << "I am the program!!!!" << std::endl; }
    virtual std::string toString() const { return "I am the program!!! to string()!!"; }
    virtual ~TypeNode() = default;
};
} // namespace ASTNamespace

#endif
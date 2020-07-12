#ifndef STATEMENT_NODE_HPP
#define STATEMENT_NODE_HPP

#include "../../AbstractNode.hpp"

namespace ASTNamespace
{
class StatementNode : public AbstractNode
{
  public:
    StatementNode() {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const { std::cout << "I am the program!!!!" << std::endl; }
    ~StatementNode() {}
};
} // namespace ASTNamespace

#endif
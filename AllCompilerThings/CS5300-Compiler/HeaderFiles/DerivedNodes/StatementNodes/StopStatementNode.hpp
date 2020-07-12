#ifndef STOP_STATEMENT_NODE_HPP
#define STOP_STATEMENT_NODE_HPP

#include "StatementNode.hpp"

namespace ASTNamespace
{
class StopStatementNode : public StatementNode
{
  public:
    StopStatementNode() {}
    virtual void emit() const
    {
        std::cout << "#";
        emitSource();
        std::cout << "li " << globalRegisterList.getV_ZeroRegister() << " 10" << std::endl;
        std::cout << "syscall" << std::endl;
        std::cout << std::endl;
    }
    virtual void emitSource() const { std::cout << "STOP" << std::endl; }
    ~StopStatementNode() {}
};
} // namespace ASTNamespace

#endif
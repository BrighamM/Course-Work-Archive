#ifndef PROCEDURE_AND_FUNCTION_DECL_NODE_HPP
#define PROCEDURE_AND_FUNCTION_DECL_NODE_HPP

#include "../../AbstractNode.hpp"

namespace ASTNamespace
{
class ProcedureAndFunctionDeclNode : public AbstractNode
{
  public:
    ProcedureAndFunctionDeclNode() {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const { std::cout << "I am the program!!!!" << std::endl; }
    virtual void putPrototypeOnSymbolTable() const = 0;
    ~ProcedureAndFunctionDeclNode() {}
};
} // namespace ASTNamespace

#endif
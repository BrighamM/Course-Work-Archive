#ifndef RETURN_STATEMENT_NODE_HPP
#define RETURN_STATEMENT_NODE_HPP

#include "../ExpressionNodes/ExpressionNode.hpp"
#include "StatementNode.hpp"

namespace ASTNamespace
{
class ReturnStatementNode : public StatementNode
{
    ExpressionNode* expression;
    bool hasExpression;

  public:
    ReturnStatementNode(ExpressionNode* inputExpression)
        : expression(inputExpression), hasExpression(true)
    {
    }
    ReturnStatementNode() : hasExpression(false) {}
    virtual void emit() const
    {
        PsuedoRegister psuedoRegister = expression->getTheeIntoRegister();
        PsuedoRegister lastRegister(true);
        std::cout << "or " << lastRegister.getRegisterName() << " "
                  << psuedoRegister.getRegisterName() << " " << globalRegisterList.getZeroRegister()
                  << std::endl;
        //
    }
    virtual void emitSource() const
    {
        std::cout << "RETURN ";
        if (hasExpression)
        {
            expression->emitSource();
        }
        std::cout << std::endl;
    }
    ~ReturnStatementNode()
    {
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
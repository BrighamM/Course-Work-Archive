#ifndef FUNCTION_CALL_NODE_HPP
#define FUNCTION_CALL_NODE_HPP

#include "../AbstractNode.hpp"
#include "ExpressionNodes/ExpressionNode.hpp"
#include <vector>

namespace ASTNamespace
{
class FunctionCallNode : public AbstractNode
{
    std::string identifierToken;
    std::vector<ExpressionNode*>* argumentList;

  public:
    FunctionCallNode(char* untouchedPointer, std::vector<ExpressionNode*>* inputArgumentList)
        : identifierToken(untouchedPointer), argumentList(inputArgumentList)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        std::cout << identifierToken << "(";
        if (argumentList != NULL)
        {
            std::vector<ExpressionNode*> inlineExpressionList = *argumentList;
            for (int i = 0; i < inlineExpressionList.size(); i++)
            {
                inlineExpressionList[i]->emitSource();
                if (i != (inlineExpressionList.size() - 1))
                {
                    std::cout << ", ";
                }
            }
        }
        std::cout << ")";
    }
    std::vector<ExpressionNode*>* getFunctionCallNodeArgumentList() { return argumentList; }
    std::string getFunctionCallNodeIdentifier() { return identifierToken; }
    std::vector<ExpressionNode*> getArgsList() {}
    ~FunctionCallNode() {}
};
} // namespace ASTNamespace

#endif
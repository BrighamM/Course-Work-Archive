#ifndef ELSE_IF_CLAUSE_NODE_HPP
#define ELSE_IF_CLAUSE_NODE_HPP

#include "../../AbstractNode.hpp"
#include "../ExpressionNodes/ExpressionNode.hpp"
#include "StatementNode.hpp"
#include <vector>

namespace ASTNamespace
{
class ElseIfClauseNode : public AbstractNode
{
    ExpressionNode* expression;
    std::vector<StatementNode*>* statementSequence;

  public:
    ElseIfClauseNode(ExpressionNode* inputExpression,
                     std::vector<StatementNode*>* inputStatementSequence)
        : expression(inputExpression), statementSequence(inputStatementSequence)
    {
    }
    virtual void emit() const
    {
        std::vector<StatementNode*> inlineStatementSequenceList = *statementSequence;
        for (int i = 0; i < inlineStatementSequenceList.size(); i++)
        {
            // If the statement is Null then continue.
            if (inlineStatementSequenceList[i] == NULL)
            {
                continue;
            }
            inlineStatementSequenceList[i]->emit();
        }
    }
    virtual void emitSource() const
    {
        std::cout << " ELSE_IF ";
        expression->emitSource();
        std::cout << " THEN " << std::endl;
        std::vector<StatementNode*> inlineStatementSequenceList = *statementSequence;
        for (int i = 0; i < inlineStatementSequenceList.size(); i++)
        {
            // If the statement is Null then continue.
            if (inlineStatementSequenceList[i] == NULL)
            {
                continue;
            }
            inlineStatementSequenceList[i]->emitSource();
        }
    }

    ExpressionNode* getExpression() { return expression; }
    ~ElseIfClauseNode()
    {
        delete expression;
        expression = 0;
        delete statementSequence;
        statementSequence = 0;
    }
};
} // namespace ASTNamespace

#endif
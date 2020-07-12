#ifndef ELSE_CLAUSE_NODE_HPP
#define ELSE_CLAUSE_NODE_HPP

#include "../../AbstractNode.hpp"
#include "StatementNode.hpp"
#include <vector>

namespace ASTNamespace
{
class ElseClauseNode : public AbstractNode
{
    std::vector<StatementNode*>* statementSequence;

  public:
    ElseClauseNode(std::vector<StatementNode*>* inputStatementSequence)
        : statementSequence(inputStatementSequence)
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
        std::cout << " ELSE " << std::endl;
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
    ~ElseClauseNode()
    {
        delete statementSequence;
        statementSequence = 0;
    }
};
} // namespace ASTNamespace

#endif
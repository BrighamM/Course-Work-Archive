#ifndef BLOCK_NODE_HPP
#define BLOCK_NODE_HPP

#include "../../AbstractNode.hpp"
#include "../StatementNodes/StatementNode.hpp"
#include <vector>

// Block : BEGIN_TOKEN StatementSequence END_TOKEN {$$ = new ASTNamespace::BlockNode($2);};

namespace ASTNamespace
{
class BlockNode : public AbstractNode
{
    std::vector<StatementNode*>* statementSequence;

  public:
    BlockNode(std::vector<StatementNode*>* incomingStatementSequence)
        : statementSequence(incomingStatementSequence)
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
        std::cout << "BEGIN" << std::endl;
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
        std::cout << "END";
    }
    ~BlockNode()
    {
        delete statementSequence;
        statementSequence = 0;
    }
};
} // namespace ASTNamespace

#endif
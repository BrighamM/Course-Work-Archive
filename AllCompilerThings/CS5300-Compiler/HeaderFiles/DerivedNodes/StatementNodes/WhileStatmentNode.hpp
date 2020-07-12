#ifndef WHILE_STATEMENT_NODE_HPP
#define WHILE_STATEMENT_NODE_HPP

#include "../ExpressionNodes/ExpressionNode.hpp"
#include "StatementNode.hpp"
#include <vector>

namespace ASTNamespace
{
class WhileStatementNode : public StatementNode
{
    ExpressionNode* expression;
    std::vector<StatementNode*>* statementSequence;

  public:
    WhileStatementNode(ExpressionNode* inputExpression,
                       std::vector<StatementNode*>* inputStatementSequence)
        : expression(inputExpression), statementSequence(inputStatementSequence)
    {
    }
    virtual void emit() const
    {
        globalSymbolTable.pushNewScope();
        std::vector<std::string> whileEndLables = globalSymbolTable.getNextWhileEndLabels();

        std::cout << "b " << whileEndLables[0] << std::endl;
        std::cout << whileEndLables[0] << ":" << std::endl;

        PsuedoRegister conditionalRegister = expression->getTheeIntoRegister();
        std::cout << "abs " << conditionalRegister.getRegisterName() << " "
                  << conditionalRegister.getRegisterName() << std::endl;
        std::cout << "sge " << conditionalRegister.getRegisterName() << " "
                  << conditionalRegister.getRegisterName() << " 1" << std::endl;
        std::cout << "beq " << conditionalRegister.getRegisterName() << " "
                  << globalRegisterList.getZeroRegister() << " " << whileEndLables[1] << std::endl;

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

        std::cout << "b " << whileEndLables[0] << std::endl;
        std::cout << whileEndLables[1] << ":" << std::endl;
        globalSymbolTable.popLastScope();
    }
    virtual void emitSource() const
    {
        std::cout << " WHILE ";
        expression->emitSource();
        std::cout << " DO" << std::endl;
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
        std::cout << " END " << std::endl;
    }
    ~WhileStatementNode()
    {
        delete expression;
        expression = 0;
        delete statementSequence;
        statementSequence = 0;
    }
};
} // namespace ASTNamespace

#endif
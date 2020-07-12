#ifndef REPEAT_STATEMENT_NODE_HPP
#define REPEAT_STATEMENT_NODE_HPP

#include "../ExpressionNodes/ExpressionNode.hpp"
#include "StatementNode.hpp"
#include <vector>

namespace ASTNamespace
{
class RepeatStatementNode : public StatementNode
{
    std::vector<StatementNode*>* statementSequence;
    ExpressionNode* expression;

  public:
    RepeatStatementNode(std::vector<StatementNode*>* inputStatementSequence,
                        ExpressionNode* inputExpression)
        : statementSequence(inputStatementSequence), expression(inputExpression)
    {
    }
    virtual void emit() const
    {
        globalSymbolTable.pushNewScope();
        std::vector<std::string> repeatEndLabels = globalSymbolTable.getNextRepeatEndLabels();

        std::cout << "b " << repeatEndLabels[0] << std::endl;
        std::cout << repeatEndLabels[0] << ":" << std::endl;
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

        // BEGIN TRUEIFICATION
        PsuedoRegister conditionalRegister = expression->getTheeIntoRegister();
        std::cout << "abs " << conditionalRegister.getRegisterName() << " "
                  << conditionalRegister.getRegisterName() << std::endl;
        std::cout << "sge " << conditionalRegister.getRegisterName() << " "
                  << conditionalRegister.getRegisterName() << " 1" << std::endl;
        std::cout << "sle " << conditionalRegister.getRegisterName() << " "
                  << conditionalRegister.getRegisterName() << " "
                  << globalRegisterList.getZeroRegister() << std::endl;
        std::cout << "beq " << conditionalRegister.getRegisterName() << " 1 " << repeatEndLabels[0]
                  << std::endl;
        std::cout << "b " << repeatEndLabels[1] << std::endl;
        // END TRUEIFICATION

        std::cout << repeatEndLabels[1] << ":" << std::endl;
        globalSymbolTable.popLastScope();
    }
    virtual void emitSource() const
    {
        std::cout << " REPEAT " << std::endl;
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
        std::cout << " UNTIL ";
        expression->emitSource();
        std::cout << std::endl;
    }
    ~RepeatStatementNode()
    {
        delete statementSequence;
        statementSequence = 0;
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
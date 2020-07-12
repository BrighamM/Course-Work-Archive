#ifndef IF_STATEMENT_NODE_HPP
#define IF_STATEMENT_NODE_HPP

#include "../ExpressionNodes/ExpressionNode.hpp"
#include "ElseClauseNode.hpp"
#include "ElseIfClauseNode.hpp"
#include "StatementNode.hpp"
#include <vector>

namespace ASTNamespace
{
class IfStatementNode : public StatementNode
{
    ExpressionNode* expression;
    std::vector<StatementNode*>* statementSequence;
    std::vector<ElseIfClauseNode*>* elseIfClauseList;
    ElseClauseNode* elseClause;

  public:
    IfStatementNode(ExpressionNode* inputExpression,
                    std::vector<StatementNode*>* inputStatementSequence,
                    std::vector<ElseIfClauseNode*>* inputElseIfClauseList,
                    ElseClauseNode* inputElseClause)
        : expression(inputExpression), statementSequence(inputStatementSequence),
          elseIfClauseList(inputElseIfClauseList), elseClause(inputElseClause)
    {
    }
    virtual void emit() const
    {
        // First request the ifBlock, elseBlock, and endIfBlock labels from the global symboltable.
        std::vector<std::string> if_ElseIf_Else_EndLabels =
            globalSymbolTable.getNextIf_ElseIf_Else_EndLabels();
        // get elseExists bool
        bool elseExists;
        if (elseClause != nullptr)
        {
            elseExists = true;
        }
        bool elseIfsExist = false;
        int elseIfsCount = 0;

        if (elseIfClauseList != NULL)
        {
            std::vector<ElseIfClauseNode*> inlineElseIfClauseList = *elseIfClauseList;
            elseIfsExist = true;
            elseIfsCount = inlineElseIfClauseList.size();
        }

        // BEGIN PREHEADER
        PsuedoRegister conditionalRegister = expression->getTheeIntoRegister();

        // BEGIN REGISTER TRUEIFICATION
        std::cout << "abs " << conditionalRegister.getRegisterName() << " "
                  << conditionalRegister.getRegisterName() << std::endl;
        std::cout << "sge " << conditionalRegister.getRegisterName() << " "
                  << conditionalRegister.getRegisterName() << " 1" << std::endl;
        // END REGISTER TRUEIFICATION

        // BEGIN IFBLOCK BRANCHER
        std::cout << "beq " << conditionalRegister.getRegisterName() << " 1 "
                  << if_ElseIf_Else_EndLabels[0] << std::endl;
        // END IFBLOCK BRANCHER

        // BEGIN ELSEIF BLOCKS
        if (elseIfsExist)
        {
            std::vector<ElseIfClauseNode*> inlineElseIfClauseList = *elseIfClauseList;
            for (int i = 0; i < elseIfsCount; i++)
            {
                conditionalRegister =
                    inlineElseIfClauseList[i]->getExpression()->getTheeIntoRegister();
                // BEGIN REGISTER TRUEIFICATION
                std::cout << "abs " << conditionalRegister.getRegisterName() << " "
                          << conditionalRegister.getRegisterName() << std::endl;
                std::cout << "sge " << conditionalRegister.getRegisterName() << " "
                          << conditionalRegister.getRegisterName() << " 1" << std::endl;
                // END REGISTER TRUEIFICATION
                // BEGIN IFBLOCK BRANCHER
                std::cout << "beq " << conditionalRegister.getRegisterName() << " 1 "
                          << if_ElseIf_Else_EndLabels[1] << std::to_string(i) << std::endl;
                // END IFBLOCK BRANCHER
            }
        }
        // END ELSEIF BLOCKS

        // BEGIN ELSE BLOCK
        if (elseExists)
        {
            std::cout << "b " << if_ElseIf_Else_EndLabels[2] << std::endl;
        }
        // END ELSE BLOCK

        std::cout << "b " << if_ElseIf_Else_EndLabels[3] << std::endl;
        // END PREHEADER

        // PRINT IFBLOCK
        globalSymbolTable.pushNewScope();
        std::cout << if_ElseIf_Else_EndLabels[0] << ":" << std::endl;
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
        std::cout << "b " << if_ElseIf_Else_EndLabels[3] << std::endl;
        globalSymbolTable.popLastScope();
        // END IFBLOCK

        // PRINT ELSEIFBLOCKS
        if (elseIfsExist)
        {
            globalSymbolTable.pushNewScope();
            std::vector<ElseIfClauseNode*> inlineElseIfClauseList = *elseIfClauseList;
            for (int i = 0; i < elseIfsCount; i++)
            {
                std::cout << if_ElseIf_Else_EndLabels[1] << std::to_string(i) << ":" << std::endl;
                inlineElseIfClauseList[i]->emit();
                std::cout << "b " << if_ElseIf_Else_EndLabels[3] << std::endl;
            }
            globalSymbolTable.popLastScope();
        }
        // END IFBLOCKS

        // CONDITIONALLY PRINT ELSEBLOCK
        if (elseExists)
        {
            globalSymbolTable.pushNewScope();
            std::cout << if_ElseIf_Else_EndLabels[2] << ":" << std::endl;
            elseClause->emit();
            std::cout << "b " << if_ElseIf_Else_EndLabels[3] << std::endl;
            globalSymbolTable.popLastScope();
        }
        // END ELSEBLOCK

        // PRINT ENDIFBLOCK
        std::cout << if_ElseIf_Else_EndLabels[3] << ":" << std::endl;
    }
    virtual void emitSource() const
    {
        std::cout << " IF ";
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
        if (elseIfClauseList != NULL)
        {
            std::vector<ElseIfClauseNode*> inlineElseIfClauseList = *elseIfClauseList;
            for (int i = 0; i < inlineElseIfClauseList.size(); i++)
            {
                inlineElseIfClauseList[i]->emitSource();
            }
        }
        if (elseClause != NULL)
        {
            elseClause->emitSource();
        }
        std::cout << " END " << std::endl;
    }
    ~IfStatementNode()
    {
        delete expression;
        expression = 0;
        delete statementSequence;
        statementSequence = 0;
        delete elseIfClauseList;
        elseIfClauseList = 0;
        delete elseClause;
        elseClause = 0;
    }
};
} // namespace ASTNamespace

#endif
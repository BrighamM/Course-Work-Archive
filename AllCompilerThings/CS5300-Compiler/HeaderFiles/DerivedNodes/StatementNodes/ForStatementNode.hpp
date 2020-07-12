#ifndef FOR_STATEMENT_NODE_HPP
#define FOR_STATEMENT_NODE_HPP

#include "../ExpressionNodes/ExpressionNode.hpp"
#include "AssignmentNode.hpp"
#include "StatementNode.hpp"
#include <vector>

// ForStatement : FOR_TOKEN Assignment TO_TOKEN Expression DO_TOKEN StatementSequence END_TOKEN
// {$$ = new ASTNamespace::ForStatementNode(true,$2,$4,$6);}

//              | FOR_TOKEN Assignment DOWNTO_TOKEN Expression DO_TOKEN StatementSequence END_TOKEN
// {$$ = new ASTNamespace::ForStatementNode(false,$2,$4,$6);};
namespace ASTNamespace
{
class ForStatementNode : public StatementNode
{
    ExpressionNode* endExpression;
    std::vector<StatementNode*>* assignmentStatement;
    std::vector<StatementNode*>* statementSequence;
    bool isForTo;

  public:
    ForStatementNode(bool inputIsForTo, std::vector<StatementNode*>* inputAssignmentNode,
                     ExpressionNode* inputExpression,
                     std::vector<StatementNode*>* inputStatementSequence)
        : isForTo(inputIsForTo), assignmentStatement(inputAssignmentNode),
          endExpression(inputExpression), statementSequence(inputStatementSequence)
    {
    }

    virtual void emit() const
    {
        // Enter Scope
        globalSymbolTable.pushNewScope();
        // Get the Labels
        std::vector<std::string> forAndExitLabels = globalSymbolTable.getNextForLoopExitLabels();
        // Check for errors then emit the code for the assignment statement
        std::vector<StatementNode*> inlineAssignmentStatementSequenceList = *assignmentStatement;
        if (inlineAssignmentStatementSequenceList.size() != 1)
        {
            std::cout << "We have major issues in For Statement node kei92" << std::endl;
        }
        else if (dynamic_cast<AssignmentNode*>(inlineAssignmentStatementSequenceList[0]) == nullptr)
        {
            std::cout << "We have major issues in For Statement node op09nb" << std::endl;
        }
        AssignmentNode* assignmentNode =
            dynamic_cast<AssignmentNode*>(inlineAssignmentStatementSequenceList[0]);

        // If the lvalue in the assignment statement is not already in the symbol table we should
        // create it and place it there with a default type of int.
        if (!globalSymbolTable.isVarConstIdentifierInSymbolTable(
                assignmentNode->getLValue()->getIdentifier()))
        {
            // Place into symbol table
            std::vector<std::string> inlineVector;
            inlineVector.emplace_back(assignmentNode->getLValue()->getIdentifier());
            // globalSymbolTable.saveVarsListToSymbolTable(
            //     inlineVector, SymbolTableIntType::get(), SymbolTableIntType::get()->size(),
            //     globalRegisterList.getGlobalPointerRegister()); // Again default to GP
            if (globalSymbolTable.shouldUseFramePointer())
            {
                globalSymbolTable.saveVarsListToSymbolTable(
                    inlineVector, SymbolTableIntType::get(), SymbolTableIntType::get()->size(),
                    globalRegisterList.getFramePointerRegister());
            }
            else
            {
                globalSymbolTable.saveVarsListToSymbolTable(
                    inlineVector, SymbolTableIntType::get(), SymbolTableIntType::get()->size(),
                    globalRegisterList.getGlobalPointerRegister());
            }
        }
        assignmentNode->emit();

        // Capture the current value of the Lvalue into a register
        PsuedoRegister psuedoLvalueRegister = assignmentNode->getLValue()->getTheeIntoRegister();
        // Capture the address of the Lvalue into a register
        PsuedoRegister psuedoLvalueAddressRegister =
            assignmentNode->getLValue()->getThyAddressIntoRegister();
        // Capture the current value of the Rvalue into a register
        PsuedoRegister psuedoRvalueRegister = endExpression->getTheeIntoRegister();

        // Deduce if we are using bgt or blt and addi or subi
        std::string branchInstruction = isForTo ? "bgt " : "blt ";

        // START OF THE LOOP
        std::cout << forAndExitLabels[0] << ": " << std::endl;
        // Set up branch instruction to check if we should leave
        std::cout << branchInstruction << psuedoLvalueRegister.getRegisterName() << " "
                  << psuedoRvalueRegister.getRegisterName() << " " << forAndExitLabels[1]
                  << std::endl;

        // Print out assembly for statements in statement sequence list
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

        // Appropriately increment our sentinal and store the result to the symbol table
        std::string incrementInstruction = isForTo ? "addi " : "subi ";
        std::cout << incrementInstruction << psuedoLvalueRegister.getRegisterName() << "  "
                  << psuedoLvalueRegister.getRegisterName() << " 1" << std::endl;
        std::cout << "sw " << psuedoLvalueRegister.getRegisterName() << " ("
                  << psuedoLvalueAddressRegister.getRegisterName() << ") " << std::endl;

        // go to the start of the loop
        std::cout << "j " << forAndExitLabels[0] << std::endl;

        // Write out the exit point
        std::cout << forAndExitLabels[1] << ": " << std::endl;

        // We are finished... so... POP SCOPE
        globalSymbolTable.popLastScope();
    }
    virtual void emitSource() const
    {
        std::string toOrDownTo = isForTo ? " TO " : " DOWNTO ";
        std::cout << "FOR ";

        std::vector<StatementNode*> inlineAssignmentStatementSequenceList = *assignmentStatement;
        for (int i = 0; i < inlineAssignmentStatementSequenceList.size(); i++)
        {
            // If the statement is Null then continue.
            if (inlineAssignmentStatementSequenceList[i] == NULL)
            {
                continue;
            }
            inlineAssignmentStatementSequenceList[i]->emitSource();
        }

        std::cout << toOrDownTo;
        endExpression->emitSource();
        std::cout << " DO " << std::endl;
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
    ~ForStatementNode()
    {
        delete statementSequence;
        statementSequence = 0;
        delete endExpression;
        endExpression = 0;
        delete assignmentStatement;
        assignmentStatement = 0;
    }
};
} // namespace ASTNamespace

#endif
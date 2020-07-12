#ifndef WRITE_STATEMENT_NODE_HPP
#define WRITE_STATEMENT_NODE_HPP

#include "../ExpressionNodes/CHARCONSTExpressionNode.hpp"
#include "../ExpressionNodes/ExpressionNode.hpp"
#include "../ExpressionNodes/INTEGERExpressionNode.hpp"
#include "../ExpressionNodes/LVALExpressionNode.hpp"
#include "../ExpressionNodes/STRINGExpressionNode.hpp"
#include "StatementNode.hpp"
#include <vector>
/**
 * WriteStatement : WRITE_TOKEN LEFT_PARENS_TOKEN WriteArguments RIGHT_PARENS_TOKEN {$$ = new
 * ASTNamespace::WriteStatementNode($3);}; WriteArguments : WriteArguments COMMA_TOKEN Expression
 * {$1->push_back($3); $$ = $1;} | Expression                            {$$ = new
 * std::vector<ASTNamespace::ExpressionNode*>(); $$->push_back($1);};
 */
namespace ASTNamespace
{
class WriteStatementNode : public StatementNode
{
    std::vector<ExpressionNode*>* argumentList;

  public:
    WriteStatementNode(std::vector<ExpressionNode*>* inputArgumentList)
        : argumentList(inputArgumentList)
    {
    }
    virtual void emit() const
    {
        std::cout << "#";
        emitSource();

        // For each expression I am going  to generate a write thingy...
        // There are lots of options when printing.
        // I could print
        /**
         *
         *   li $v0 (input code to $v0)
         *   add $a0 $t0 $zero # for an integer
         *   syscall
         *
         *
         * 1. Integer           code =  1; and $a0 contains the integer to print;
         * 2. String            code =  4; and $a0 contains the address of the null-terminated
         * string to print;
         * 3. HexIngteger       code = 34; and $a0 contains the integer to print;
         * 4. BinaryInteger     code = 35; and $a0 contains the integer to print;
         * 5. UnsignedInteger   code = 36; and $a0 contains the integer to print;
         */

        if (argumentList != NULL)
        {
            std::vector<ExpressionNode*> inlineExpressionList = *argumentList;
            for (int i = 0; i < inlineExpressionList.size(); i++)
            {
                if (inlineExpressionList[i]->getType() == SymbolTableIntType::get())
                {
                    PsuedoRegister psuedoRegister = inlineExpressionList[i]->getTheeIntoRegister();
                    std::cout << "li " << globalRegisterList.getV_ZeroRegister() << " "
                              << "1" << std::endl; // TODO: Don't use magic strings!!!
                    std::cout << "or " << globalRegisterList.getA_ZeroRegister() << " "
                              << psuedoRegister.getRegisterName() << " "
                              << globalRegisterList.getZeroRegister() << std::endl;
                    std::cout << "syscall" << std::endl;
                    continue;
                }
                if (inlineExpressionList[i]->getType() == SymbolTableBoolType::get())
                {
                    PsuedoRegister psuedoRegister = inlineExpressionList[i]->getTheeIntoRegister();
                    std::cout << "li " << globalRegisterList.getV_ZeroRegister() << " "
                              << "1" << std::endl; // TODO: Don't use magic strings!!!
                    std::cout << "or " << globalRegisterList.getA_ZeroRegister() << " "
                              << psuedoRegister.getRegisterName() << " "
                              << globalRegisterList.getZeroRegister() << std::endl;
                    std::cout << "syscall" << std::endl;
                    continue;
                }
                if (inlineExpressionList[i]->getType() == SymbolTableCharType::get())
                {
                    PsuedoRegister psuedoRegister = inlineExpressionList[i]->getTheeIntoRegister();
                    std::cout << "li " << globalRegisterList.getV_ZeroRegister() << " "
                              << "11" << std::endl;
                    std::cout << "move " << globalRegisterList.getA_ZeroRegister() << " "
                              << psuedoRegister.getRegisterName() << std::endl;
                    std::cout << "syscall" << std::endl;
                    continue;
                }
                if (inlineExpressionList[i]->getType() == SymbolTableStringType::get())
                {
                    PsuedoRegister psuedoRegister = inlineExpressionList[i]->getTheeIntoRegister();
                    std::cout << "li " << globalRegisterList.getV_ZeroRegister() << " "
                              << "4" << std::endl;
                    std::cout << "move " << globalRegisterList.getA_ZeroRegister() << " "
                              << psuedoRegister.getRegisterName() << std::endl;
                    std::cout << "syscall" << std::endl;
                    continue;
                }
            }
        }
        std::cout << std::endl;
    }
    virtual void emitSource() const
    {
        std::cout << "WRITE(";
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
        std::cout << ")" << std::endl;
    }

    ~WriteStatementNode()
    {
        delete argumentList;
        argumentList = 0;
    }
};
} // namespace ASTNamespace

#endif
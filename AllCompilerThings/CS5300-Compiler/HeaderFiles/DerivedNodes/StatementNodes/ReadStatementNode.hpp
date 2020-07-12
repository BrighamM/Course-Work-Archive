#ifndef READ_STATEMENT_NODE_HPP
#define READ_STATEMENT_NODE_HPP

#include "../LValueNode.hpp"
#include "StatementNode.hpp"
#include <vector>

namespace ASTNamespace
{
class ReadStatementNode : public StatementNode
{
    std::vector<LValueNode*>* argumentList;

  public:
    ReadStatementNode(std::vector<LValueNode*>* inputArgumentList) : argumentList(inputArgumentList)
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
            std::vector<LValueNode*> inlineLValueList = *argumentList;
            for (int i = 0; i < inlineLValueList.size(); i++)
            {
                std::string lValueIdentifier = inlineLValueList[i]->getIdentifier();
                std::shared_ptr<SymbolTableType> lValueType =
                    globalSymbolTable.getVarConstType(lValueIdentifier);
                if (lValueType == SymbolTableIntType::get())
                {
                    std::cout << "li " << globalRegisterList.getV_ZeroRegister() << " 5 "
                              << std::endl;
                    std::cout << "syscall" << std::endl;
                    std::string baseRegister =
                        globalSymbolTable.getVarIdentierBaseRegister(lValueIdentifier);
                    int baseRegisterOffset =
                        globalSymbolTable.getVarIdentifierBaseRegisterOffSet(lValueIdentifier);

                    std::cout << "sw " << globalRegisterList.getV_ZeroRegister() << " "
                              << baseRegisterOffset << "(" << baseRegister << ")" << std::endl;
                }
                if (lValueType == SymbolTableBoolType::get())
                {
                    std::cout << "li " << globalRegisterList.getV_ZeroRegister() << " 5 "
                              << std::endl;
                    std::cout << "syscall" << std::endl;
                    std::string baseRegister =
                        globalSymbolTable.getVarIdentierBaseRegister(lValueIdentifier);
                    int baseRegisterOffset =
                        globalSymbolTable.getVarIdentifierBaseRegisterOffSet(lValueIdentifier);

                    std::cout << "sw " << globalRegisterList.getV_ZeroRegister() << " "
                              << baseRegisterOffset << "(" << baseRegister << ")" << std::endl;
                }
                if (lValueType == SymbolTableCharType::get())
                {
                    std::cout << "li " << globalRegisterList.getV_ZeroRegister() << " 12 "
                              << std::endl;
                    std::cout << "syscall" << std::endl;
                    std::string baseRegister =
                        globalSymbolTable.getVarIdentierBaseRegister(lValueIdentifier);
                    int baseRegisterOffset =
                        globalSymbolTable.getVarIdentifierBaseRegisterOffSet(lValueIdentifier);
                    std::cout << "sw " << globalRegisterList.getV_ZeroRegister() << " "
                              << baseRegisterOffset << "(" << baseRegister << ")" << std::endl;
                }
                if (lValueType == SymbolTableStringType::get())
                {
                    std::cout << "ERROR ERROR ERROR IN READ STATEMENT " << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
    virtual void emitSource() const
    {
        std::cout << "READ(";
        std::vector<LValueNode*> inlineLValueList = *argumentList;
        for (int i = 0; i < inlineLValueList.size(); i++)
        {
            inlineLValueList[i]->emitSource();
            if (i != (inlineLValueList.size() - 1))
            {
                std::cout << ", ";
            }
        }
        std::cout << ")" << std::endl;
    }
    ~ReadStatementNode()
    {
        delete argumentList;
        argumentList = 0;
    }
};
} // namespace ASTNamespace

#endif
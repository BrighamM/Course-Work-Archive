#ifndef PROCEDURE_CALL_NODE_HPP
#define PROCEDURE_CALL_NODE_HPP

#include "../ExpressionNodes/ExpressionNode.hpp"
#include "../ExpressionNodes/LVALExpressionNode.hpp"
#include "StatementNode.hpp"
#include <vector>

namespace ASTNamespace
{
class ProcedureCallNode : public StatementNode
{
    std::string identifierToken;
    std::vector<ExpressionNode*>* argumentList;

  public:
    ProcedureCallNode(char* untouchedPointer, std::vector<ExpressionNode*>* incomingArgumentList)
        : identifierToken(untouchedPointer), argumentList(incomingArgumentList)
    {
    }
    virtual void emit() const
    {
        // SPILL REGISTERS
        globalRegisterList.spillRegisters();
        // std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
        //           << globalRegisterList.getStackPointerRegister() << " " << -8 << std::endl;

        // std::cout << "sw " << globalRegisterList.getFramePointerRegister() << " " << 4 << "("
        //           << globalRegisterList.getStackPointerRegister() << ")" << std::endl;

        // std::cout << "sw " << globalRegisterList.getReturnAddressRegister() << " " << 0 << "("
        //           << globalRegisterList.getStackPointerRegister() << ")" << std::endl;

        // SPILL ARGS
        if (argumentList != NULL)
        {
            std::vector<bool> myRefBoolVector =
                globalSymbolTable.getProcedurePrototypeBoolVector(identifierToken);
            std::vector<ExpressionNode*> inlineExpressionList = *argumentList;
            if (inlineExpressionList.size() != myRefBoolVector.size())
            {
                std::cout << "WE ARE VERY BROKEN IN PROCEDURE CALL NODE!!!" << std::endl;
            }

            int numElements = inlineExpressionList.size();
            int accumSize = 0;
            for (int j1 = 0; j1 < numElements; j1++)
            {
                if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[j1]))
                {
                    accumSize += dynamic_cast<LvalExpressionNode*>(inlineExpressionList[j1])
                                     ->getType()
                                     ->size();
                }
                else
                {
                    accumSize += 4;
                }
            }

            std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
                      << globalRegisterList.getStackPointerRegister() << " -" << accumSize
                      << std::endl;

            int currByteBlockValue = 0;
            for (int i = 0; i < inlineExpressionList.size(); i++)
            {
                // FOR SOME PROCEDURE MYPROCEDURE(a,b,c...)
                // First make room for a, then store a, then make room for b, then store b,
                // then make room for c then store c, etc.....
                if (myRefBoolVector[i])
                {
                    if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i]))
                    {
                        bool sizeIsBig = false;
                        if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i]))
                        {
                            if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                    ->getType()
                                    ->size() > 4)
                            {
                                sizeIsBig = true;
                            }
                        }
                        if (sizeIsBig)
                        {
                            PsuedoRegister psuedoRightRegister =
                                dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                    ->getThyAddressIntoRegister();
                            int typeSize =
                                dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                    ->getType()
                                    .get()
                                    ->size();
                            PsuedoRegister helperRegister;
                            for (int i3 = 0; i3 < typeSize; i3 += 4)
                            {
                                std::cout << "lw " << helperRegister.getRegisterName() << " " << i3
                                          << "(" << psuedoRightRegister.getRegisterName() << ")"
                                          << std::endl;
                                std::cout << "sw " << helperRegister.getRegisterName() << " " << i3
                                          << "(" << globalRegisterList.getStackPointerRegister()
                                          << ")" << std::endl;
                            }
                            currByteBlockValue += typeSize;
                        }
                        else
                        {
                            PsuedoRegister psuedoRegister =
                                dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                    ->getTheeIntoRegister();
                            std::cout << "sw " << psuedoRegister.getRegisterName() << " "
                                      << currByteBlockValue << "("
                                      << globalRegisterList.getStackPointerRegister() << ") "
                                      << std::endl;
                            currByteBlockValue += 4;
                        }
                    }
                    else
                    {
                        std::cout << "WE ARE VERY BROKEN IN PROCEDURE CALL NODE!!! WORSE EVEN"
                                  << std::endl;
                    }
                }
                else
                {
                    PsuedoRegister psuedoRegister = inlineExpressionList[i]->getTheeIntoRegister();
                    // std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
                    //           << globalRegisterList.getStackPointerRegister() << " -4" <<
                    //           std::endl;
                    std::cout << "sw " << psuedoRegister.getRegisterName() << " "
                              << currByteBlockValue << "("
                              << globalRegisterList.getStackPointerRegister() << ") " << std::endl;
                    currByteBlockValue += 4;
                }
            }
        }
        std::cout << "jal " << identifierToken << std::endl;
        // UNSPILL ARGS
        if (argumentList != NULL)
        {
            // std::vector<ExpressionNode*> inlineExpressionList = *argumentList;
            // for (int i = 0; i < inlineExpressionList.size(); i++)
            // {
            //     std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
            //               << globalRegisterList.getStackPointerRegister() << " 4" << std::endl;
            // }
            std::vector<bool> myRefBoolVector =
                globalSymbolTable.getProcedurePrototypeBoolVector(identifierToken);
            std::vector<ExpressionNode*> inlineExpressionList = *argumentList;
            if (inlineExpressionList.size() != myRefBoolVector.size())
            {
                std::cout << "WE ARE VERY BROKEN IN PROCEDURE CALL NODE!!!" << std::endl;
            }

            int numElements = inlineExpressionList.size();
            int accumSize = 0;
            for (int j1 = 0; j1 < numElements; j1++)
            {
                if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[j1]))
                {
                    accumSize += dynamic_cast<LvalExpressionNode*>(inlineExpressionList[j1])
                                     ->getType()
                                     ->size();
                }
                else
                {
                    accumSize += 4;
                }
            }

            // std::cout << "lw " << globalRegisterList.getReturnAddressRegister() << " "
            //           << accumSize + 0 << "(" << globalRegisterList.getStackPointerRegister() <<
            //           ")"
            //           << std::endl;

            std::cout << "lw " << globalRegisterList.getFramePointerRegister() << " "
                      << accumSize + 100 << "(" << globalRegisterList.getStackPointerRegister()
                      << ")" << std::endl;

            int currByteBlockValue = 0;
            for (int i = 0; i < inlineExpressionList.size(); i++)
            {
                // FOR SOME PROCEDURE MYPROCEDURE(a,b,c...)
                // First make room for a, then store a, then make room for b, then store b,
                // then make room for c then store c, etc.....
                if (myRefBoolVector[i])
                {
                    if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i]))
                    {

                        bool sizeIsBig = false;
                        if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i]))
                        {
                            if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                    ->getType()
                                    ->size() > 4)
                            {
                                sizeIsBig = true;
                            }
                        }
                        if (sizeIsBig)
                        {
                            PsuedoRegister psuedoAddressRegister =
                                dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                    ->getThyAddressIntoRegister();

                            int typeSize =
                                dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                    ->getType()
                                    .get()
                                    ->size();

                            for (int i3 = 0; i3 < typeSize; i3 += 4)
                            {
                                PsuedoRegister psuedoRegisterRValue;
                                std::cout << "lw " << psuedoRegisterRValue.getRegisterName() << " "
                                          << i3 << "("
                                          << globalRegisterList.getStackPointerRegister() << ") "
                                          << std::endl;
                                std::cout << "sw " << psuedoRegisterRValue.getRegisterName() << " "
                                          << i3 << "(" << psuedoAddressRegister.getRegisterName()
                                          << ") " << std::endl;
                            }
                            currByteBlockValue += typeSize;
                        }
                        else
                        {
                            // from the stack I need to read the value that is stored
                            PsuedoRegister psuedoRegisterRValue;
                            std::cout << "lw " << psuedoRegisterRValue.getRegisterName() << " "
                                      << currByteBlockValue << "("
                                      << globalRegisterList.getStackPointerRegister() << ") "
                                      << std::endl;

                            PsuedoRegister psuedoAddressRegister =
                                dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                    ->getThyAddressIntoRegister();

                            std::cout << "sw " << psuedoRegisterRValue.getRegisterName() << " ("
                                      << psuedoAddressRegister.getRegisterName() << ") "
                                      << std::endl;

                            std::cout << std::endl;
                            currByteBlockValue += 4;
                        }
                    }
                    else
                    {
                        std::cout << "WE ARE VERY BROKEN IN PROCEDURE CALL NODE!!! WORSE EVEN"
                                  << std::endl;
                    }
                }
                else
                {
                }
                // std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
                //           << globalRegisterList.getStackPointerRegister() << " 4" << std::endl;
            }
            std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
                      << globalRegisterList.getStackPointerRegister() << " " << accumSize
                      << std::endl;
        }
        // UNSPILL REGISTERS
        // std::cout << "lw " << globalRegisterList.getReturnAddressRegister() << " " << 0 << "("
        //           << globalRegisterList.getStackPointerRegister() << ")" << std::endl;

        // std::cout << "lw " << globalRegisterList.getFramePointerRegister() << " " << 4 << "("
        //           << globalRegisterList.getStackPointerRegister() << ")" << std::endl;

        // std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
        //           << globalRegisterList.getStackPointerRegister() << " " << 8 << std::endl;

        globalRegisterList.unSpillRegisters();
    }
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
        std::cout << ")" << std::endl;
    }
    ~ProcedureCallNode()
    {
        delete argumentList;
        argumentList = 0;
    }
};
} // namespace ASTNamespace

#endif
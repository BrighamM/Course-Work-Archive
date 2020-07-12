#ifndef FUNCTION_CALL_EXPRESSION_NODE_HPP
#define FUNCTION_CALL_EXPRESSION_NODE_HPP

#include "../FunctionCallNode.hpp"
#include "../Lval_Bracketed_Expression_Node.hpp"
#include "ExpressionNode.hpp"
#include "LVALExpressionNode.hpp"

// FunctionCall {$$ = new ASTNamespace::FunctionCallExpressionNode($1);}
namespace ASTNamespace
{
class FunctionCallExpressionNode : public ExpressionNode
{
    FunctionCallNode* functionCall;

  public:
    FunctionCallExpressionNode(FunctionCallNode* inputFunctionCall)
        : functionCall(inputFunctionCall)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const { functionCall->emitSource(); }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        // SPILL REGISTERS
        std::string identifierToken = functionCall->getFunctionCallNodeIdentifier();
        std::vector<ExpressionNode*>* argumentList =
            functionCall->getFunctionCallNodeArgumentList();

        globalRegisterList.spillRegisters();
        // THE SIZE OF THE RETURN VALUE FOR ALL FUNCTIONS WILL BE 4 SO  I AM JUST GOING TO HARD CODE
        // IT.
        std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
                  << globalRegisterList.getStackPointerRegister() << " " << -4 << std::endl;
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
                std::cout << "WE ARE VERY BROKEN IN Function CALL NODE!!!" << std::endl;
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

            // int myInt = inlineExpressionList.size();
            std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
                      << globalRegisterList.getStackPointerRegister() << " -" << accumSize
                      << std::endl;
            for (int i = 0; i < inlineExpressionList.size(); i++)
            {
                // FOR SOME PROCEDURE MYPROCEDURE(a,b,c...)
                // First make room for a, then store a, then make room for b, then store b,
                // then make room for c then store c, etc.....
                if (myRefBoolVector[i])
                {
                    if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i]))
                    {
                        // PsuedoRegister psuedoRegister =
                        //     dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                        //         ->getThyAddressIntoRegister();
                        // std::cout << "addi " << globalRegisterList.getStackPointerRegister() << "
                        // "
                        //           << globalRegisterList.getStackPointerRegister() << " -4"
                        //           << std::endl;
                        // std::cout << "sw " << psuedoRegister.getRegisterName() << " 4("
                        //           << globalRegisterList.getStackPointerRegister() << ") "
                        //           << std::endl;
                        // std::cout << "addi " << globalRegisterList.getStackPointerRegister() << "
                        // "
                        //           << globalRegisterList.getStackPointerRegister() << " -4"
                        //           << std::endl;
                        PsuedoRegister psuedoRegister =
                            dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                ->getTheeIntoRegister();
                        std::cout << "sw " << psuedoRegister.getRegisterName() << " " << i * 4
                                  << "(" << globalRegisterList.getStackPointerRegister() << ") "
                                  << std::endl;
                    }
                    else
                    {
                        std::cout << "WE ARE VERY BROKEN IN Function CALL NODE!!! WORSE EVEN"
                                  << std::endl;
                    }
                }
                else
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
                        int typeSize = dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
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
                                      << "(" << globalRegisterList.getStackPointerRegister() << ")"
                                      << std::endl;
                        }
                    }
                    else
                    {
                        PsuedoRegister psuedoRegister =
                            inlineExpressionList[i]->getTheeIntoRegister();
                        // std::cout << "addi " << globalRegisterList.getStackPointerRegister() << "
                        // "
                        //           << globalRegisterList.getStackPointerRegister() << " -4" <<
                        //           std::endl;
                        std::cout << "sw " << psuedoRegister.getRegisterName() << " " << i * 4
                                  << "(" << globalRegisterList.getStackPointerRegister() << ") "
                                  << std::endl;
                    }
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
                std::cout << "WE ARE VERY BROKEN IN Function CALL NODE!!!" << std::endl;
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

            for (int i = 0; i < inlineExpressionList.size(); i++)
            {
                // FOR SOME PROCEDURE MYPROCEDURE(a,b,c...)
                // First make room for a, then store a, then make room for b, then store b,
                // then make room for c then store c, etc.....
                if (myRefBoolVector[i])
                {
                    if (dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i]))
                    {
                        // from the stack I need to read the value that is stored
                        PsuedoRegister psuedoRegisterRValue;
                        std::cout << "lw " << psuedoRegisterRValue.getRegisterName() << " " << i * 4
                                  << "(" << globalRegisterList.getStackPointerRegister() << ") "
                                  << std::endl;

                        PsuedoRegister psuedoAddressRegister =
                            dynamic_cast<LvalExpressionNode*>(inlineExpressionList[i])
                                ->getThyAddressIntoRegister();

                        std::cout << "sw " << psuedoRegisterRValue.getRegisterName() << " ("
                                  << psuedoAddressRegister.getRegisterName() << ") " << std::endl;

                        std::cout << std::endl;
                    }
                    else
                    {
                        std::cout << "WE ARE VERY BROKEN IN Function CALL NODE!!! WORSE EVEN"
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
        PsuedoRegister retValRegister(true);
        // std::cout << "lw " << retValRegister.getRegisterName() << " " << 0 << "("
        //           << globalRegisterList.getStackPointerRegister() << ")" << std::endl;

        std::cout << "addi " << globalRegisterList.getStackPointerRegister() << " "
                  << globalRegisterList.getStackPointerRegister() << " " << 4 << std::endl;

        globalRegisterList.unSpillRegisters(true);

        return retValRegister;

        //

        //

        //

        //

        //

        // THERE ARE NO CASES WHERE FUNCTIONS TAKE IN THINGS BY REFERENCE, SO I AM NOT GOING TO
        // WORRY ABOUT IT.
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return SymbolTableIntType::get(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return '\0'; }
    virtual bool getBoolValue() const { return false; }
    ~FunctionCallExpressionNode()
    {
        delete functionCall;
        functionCall = 0;
    }
};
} // namespace ASTNamespace

#endif
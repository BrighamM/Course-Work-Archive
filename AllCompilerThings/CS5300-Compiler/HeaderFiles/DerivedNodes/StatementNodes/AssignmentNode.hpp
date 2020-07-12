#ifndef ASSIGNMENT_NODE_HPP
#define ASSIGNMENT_NODE_HPP

#include "../ExpressionNodes/ExpressionNode.hpp"
#include "../ExpressionNodes/LVALExpressionNode.hpp"
#include "../LValueNode.hpp"
#include "StatementNode.hpp"

// Assignment : LValue ASSIGNMENT_TOKEN Expression {$$ = new ASTNamespace::AssignmentNode($1,$3);};

namespace ASTNamespace
{
class AssignmentNode : public StatementNode
{
    LValueNode* lValue;
    ExpressionNode* expression;

  public:
    AssignmentNode(LValueNode* inputLvalue, ExpressionNode* inputExpression)
        : lValue(inputLvalue), expression(inputExpression)
    {
    }
    virtual void emit() const
    {
        std::cout << "#";
        emitSource();

        if ((lValue->getType().get()->size() > 4) &&
            (expression->getType().get()->size() == lValue->getType().get()->size()))
        {
            PsuedoRegister psuedoRightRegister =
                dynamic_cast<LvalExpressionNode*>(expression)->getThyAddressIntoRegister();
            PsuedoRegister psuedoLeftRegister = lValue->getThyAddressIntoRegister();

            int typeSize = lValue->getType().get()->size();

            PsuedoRegister helperRegister;
            for (int i = 0; i < typeSize; i += 4)
            {

                std::cout << "lw " << helperRegister.getRegisterName() << " " << i << "("
                          << psuedoRightRegister.getRegisterName() << ")" << std::endl;

                std::cout << "sw " << helperRegister.getRegisterName() << " " << i << "("
                          << psuedoLeftRegister.getRegisterName() << ")" << std::endl;
            }
        }
        else
        {
            PsuedoRegister psuedoRegister = expression->getTheeIntoRegister();
            PsuedoRegister psuedoAddressRegister = lValue->getThyAddressIntoRegister();

            std::cout << "sw " << psuedoRegister.getRegisterName() << " ("
                      << psuedoAddressRegister.getRegisterName() << ") " << std::endl;

            std::cout << std::endl;
        }
    }
    LValueNode* getLValue() { return lValue; }
    virtual void emitSource() const
    {
        lValue->emitSource();
        std::cout << " := ";
        expression->emitSource();
        std::cout << std::endl;
    }
    ~AssignmentNode()
    {
        delete lValue;
        lValue = 0;
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
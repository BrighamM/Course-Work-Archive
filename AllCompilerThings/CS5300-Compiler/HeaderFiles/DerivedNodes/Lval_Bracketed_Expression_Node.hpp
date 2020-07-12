#ifndef LVAL_BRACKETED_EXPRESSION_HPP
#define LVAL_BRACKETED_EXPRESSION_HPP

#include "ExpressionNodes/ExpressionNode.hpp"
#include "LValueNode.hpp"

//  LValue : LValue LEFT_BRACKET_TOKEN Expression RIGHT_BRACKET_TOKEN {$$ = new
//  ASTNamespace::LvalBracketedExpressionNode($1,$3);}
namespace ASTNamespace
{
class LvalBracketedExpressionNode : public LValueNode
{
    LValueNode* lValue;
    ExpressionNode* expression;

  public:
    LvalBracketedExpressionNode(LValueNode* inputLvalue, ExpressionNode* inputExpression)
        : lValue(inputLvalue), expression(inputExpression)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        lValue->emitSource();
        std::cout << " [";
        expression->emitSource();
        std::cout << "] ";
    }
    virtual PsuedoRegister getThyAddressIntoRegister() const
    {
        PsuedoRegister psuedoRegisterParentAddress = lValue->getThyAddressIntoRegister();
        auto myType = lValue->getType();
        std::string baseRegisterForIdentifier =
            globalSymbolTable.getVarIdentierBaseRegister(getIdentifier());
        int offSetFromBaseRegister =
            globalSymbolTable.getVarIdentifierBaseRegisterOffSet(getIdentifier());
        int elementSize = -999999;
        int arrayLowerBound = -999999;
        if (dynamic_cast<SymbolTableArrayType*>(myType.get()))
        {
            elementSize = dynamic_cast<SymbolTableArrayType*>(myType.get())->elementSize();
            arrayLowerBound = dynamic_cast<SymbolTableArrayType*>(myType.get())->lowerBound();
        }
        else
        {
            std::cout << "lval GETTING bracket node complaining!!!" << std::endl;
        }
        PsuedoRegister psuedoRegister = expression->getTheeIntoRegister();

        std::cout << "subi " << psuedoRegister.getRegisterName() << " "
                  << psuedoRegister.getRegisterName() << " " << arrayLowerBound << std::endl;

        { // Scoped so as to release helper register as soon as possible.
            PsuedoRegister helperRegister;
            std::cout << "li " << helperRegister.getRegisterName() << " " << elementSize
                      << std::endl;
            std::cout << "mult " << psuedoRegister.getRegisterName() << " "
                      << helperRegister.getRegisterName() << std::endl;
        }
        std::cout << "mflo " << psuedoRegister.getRegisterName() << std::endl;

        std::cout << "add " << psuedoRegister.getRegisterName() << " "
                  << psuedoRegister.getRegisterName() << " "
                  << psuedoRegisterParentAddress.getRegisterName() << std::endl;
        return psuedoRegister;
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        PsuedoRegister psuedoRegisterParentAddress = lValue->getThyAddressIntoRegister();
        auto myType = lValue->getType();
        std::string baseRegisterForIdentifier =
            globalSymbolTable.getVarIdentierBaseRegister(getIdentifier());
        int offSetFromBaseRegister =
            globalSymbolTable.getVarIdentifierBaseRegisterOffSet(getIdentifier());
        int elementSize = -999999;
        int arrayLowerBound = -999999;
        if (dynamic_cast<SymbolTableArrayType*>(myType.get()))
        {
            elementSize = dynamic_cast<SymbolTableArrayType*>(myType.get())->elementSize();
            arrayLowerBound = dynamic_cast<SymbolTableArrayType*>(myType.get())->lowerBound();
        }
        else
        {
            std::cout << "lval bracket node complaining!!!" << std::endl;
        }
        PsuedoRegister psuedoRegister = expression->getTheeIntoRegister();
        std::cout << "subi " << psuedoRegister.getRegisterName() << " "
                  << psuedoRegister.getRegisterName() << " " << arrayLowerBound << std::endl;

        { // Scoped so as to release helper register as soon as possible.
            PsuedoRegister helperRegister;
            std::cout << "li " << helperRegister.getRegisterName() << " " << elementSize
                      << std::endl;
            std::cout << "mult " << psuedoRegister.getRegisterName() << " "
                      << helperRegister.getRegisterName() << std::endl;
        }
        std::cout << "mflo " << psuedoRegister.getRegisterName() << std::endl;

        std::cout << "add " << psuedoRegister.getRegisterName() << " "
                  << psuedoRegister.getRegisterName() << " "
                  << psuedoRegisterParentAddress.getRegisterName() << std::endl;

        std::cout << "lw " << psuedoRegister.getRegisterName() << " ("
                  << psuedoRegister.getRegisterName() << ") " << std::endl;

        return psuedoRegister;
    }
    virtual std::string getIdentifier() const { return lValue->getIdentifier(); }
    std::shared_ptr<SymbolTableType> getType()
    {
        if (dynamic_cast<SymbolTableArrayType*>(lValue->getType().get()))
        {
            return lValue->getType()->getType();
        }

        std::cout << "LVAL BRACKET EXPRESSION NODE GET TYPE DOESN'T WORK" << std::endl;
        return nullptr;
    }
    ~LvalBracketedExpressionNode()
    {
        delete lValue;
        lValue = 0;
        delete expression;
        expression = 0;
    }
};
} // namespace ASTNamespace

#endif
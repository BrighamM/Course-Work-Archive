#ifndef LVAL_DOT_ID_NODE_HPP
#define LVAL_DOT_ID_NODE_HPP

#include "LValueNode.hpp"

// LValue : LValue DOT_TOKEN IDENTIFIER_TOKEN
// {$$ = new ASTNamespace::LvalDotIdNode($1,$3);}
namespace ASTNamespace
{
class LvalDotIdNode : public LValueNode
{
    LValueNode* lValue;
    std::string identifierToken;

  public:
    LvalDotIdNode(LValueNode* inputLValue, char* untouchedPointer)
        : lValue(inputLValue), identifierToken(untouchedPointer)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const
    {
        lValue->emitSource();
        std::cout << "." << identifierToken << " ";
    }
    virtual PsuedoRegister getThyAddressIntoRegister() const
    {
        PsuedoRegister psuedoRegister = lValue->getThyAddressIntoRegister();
        auto myThing = lValue->getType();
        if (dynamic_cast<SymbolTableRecordType*>(myThing.get()))
        {
            auto myPair = dynamic_cast<SymbolTableRecordType*>(myThing.get())
                              ->getOffsetAndType(identifierToken);
            auto myPairInt = myPair.first;
            std::cout << "addi " << psuedoRegister.getRegisterName() << " "
                      << psuedoRegister.getRegisterName() << " " << myPairInt << std::endl;
            return psuedoRegister;
        }
        std::cout << "BAD!!! End getThyAddressIntoRegister " << std::endl;
    }
    virtual std::string getIdentifier() const { return lValue->getIdentifier(); }
    std::shared_ptr<SymbolTableType> getType()
    {
        if (dynamic_cast<SymbolTableRecordType*>(lValue->getType().get()))
        {
            return dynamic_cast<SymbolTableRecordType*>(lValue->getType().get())
                ->getOffsetAndType(identifierToken)
                .second;
        }
        std::cout << "LVAL DOT ID NODE GET TYPE DOESN'T WORK" << std::endl;
        return nullptr;
    }

    virtual PsuedoRegister getTheeIntoRegister() const
    {
        PsuedoRegister psuedoRegister = lValue->getThyAddressIntoRegister();
        auto myThing = lValue->getType();
        if (dynamic_cast<SymbolTableRecordType*>(myThing.get()))
        {
            auto myPair = dynamic_cast<SymbolTableRecordType*>(myThing.get())
                              ->getOffsetAndType(identifierToken);
            auto myPairInt = myPair.first;
            std::cout << "addi " << psuedoRegister.getRegisterName() << " "
                      << psuedoRegister.getRegisterName() << " " << myPairInt << std::endl;
            std::cout << "lw " << psuedoRegister.getRegisterName() << " ("
                      << psuedoRegister.getRegisterName() << ") " << std::endl;
            return psuedoRegister;
        }
        std::cout << "BAD!!! getTheeIntoRegister " << std::endl;
    }
    ~LvalDotIdNode()
    {
        delete lValue;
        lValue = 0;
    }
};
} // namespace ASTNamespace

#endif
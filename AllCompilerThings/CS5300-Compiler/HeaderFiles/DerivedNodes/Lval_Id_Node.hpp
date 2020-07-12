#ifndef LVAL_ID_NODE_HPP
#define LVAL_ID_NODE_HPP

#include "LValueNode.hpp"

namespace ASTNamespace
{
class LvalIdNode : public LValueNode
{
    std::string identifierToken;

  public:
    LvalIdNode(char* untouchedPointer) : identifierToken(untouchedPointer) {}
    virtual void emit() const { std::cout << identifierToken; }
    virtual void emitSource() const { std::cout << identifierToken; }
    virtual PsuedoRegister getThyAddressIntoRegister() const
    {
        // std::string identifier = lValue->getIdentifier();
        // std::string baseRegister = globalSymbolTable.getVarIdentierBaseRegister(identifier);
        // int baseRegisterOffset =
        //     globalSymbolTable.getVarIdentifierBaseRegisterOffSet(identifier);

        // std::cout << "IDNODE: " << globalSymbolTable.getVarConstType(identifierToken)->size()
        //           << std::endl;
        std::string baseRegister = globalSymbolTable.getVarIdentierBaseRegister(getIdentifier());
        int baseRegisterOffset =
            globalSymbolTable.getVarIdentifierBaseRegisterOffSet(getIdentifier());
        PsuedoRegister psuedoRegister;
        std::cout << "la " << psuedoRegister.getRegisterName() << " "
                  << std::to_string(baseRegisterOffset) << "(" << baseRegister << ")" << std::endl;
        return psuedoRegister;
    }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        PsuedoRegister psuedoRegister;
        bool isConst = globalSymbolTable.isConst(getIdentifier());
        if (!isConst)
        {
            int baseRegisterOffset =
                globalSymbolTable.getVarIdentifierBaseRegisterOffSet(getIdentifier());
            std::string baseRegister =
                globalSymbolTable.getVarIdentierBaseRegister(getIdentifier());
            std::cout << "lw " << psuedoRegister.getRegisterName() << " " << baseRegisterOffset
                      << "(" << baseRegister << ")" << std::endl;
            return psuedoRegister;
        }
        else
        {
            // Because I am a const, the stuff I need to do to get myself into a register is going
            // to be dependent on my type. So first I need my type
            if (getType() == SymbolTableIntType::get())
            {
                int rValue = globalSymbolTable.getConstIntValue(getIdentifier());
                std::cout << "li " << psuedoRegister.getRegisterName() << " " << rValue
                          << std::endl;
                return psuedoRegister;
            }

            if (getType() == SymbolTableBoolType::get())
            {
                bool rValue = globalSymbolTable.getConstBoolValue(getIdentifier());
                std::cout << "li " << psuedoRegister.getRegisterName() << " " << rValue
                          << std::endl;
                return psuedoRegister;
            }
            if (getType() == SymbolTableCharType::get())
            {
                char rValue = globalSymbolTable.getConstCharValue(getIdentifier());
                std::cout << "li " << psuedoRegister.getRegisterName() << " "
                          << "\'" << rValue << "\'" << std::endl;
                return psuedoRegister;
            }
            if (getType() == SymbolTableStringType::get())
            {
                std::string rValue = globalSymbolTable.getConstStringValue(getIdentifier());
                std::string Label = globalSymbolTable.getDataStringLabel(rValue);
                std::cout << "la " << psuedoRegister.getRegisterName() << " " << Label << std::endl;
                return psuedoRegister;
            }
        }
    }
    std::shared_ptr<SymbolTableType> getType() const
    {
        // return SymbolTableCharType::get();
        // I can do this because an Lvalue is associated with memory, therefore it is in the
        // SymbolTable.
        if (globalSymbolTable.isVarConstIdentifierInSymbolTable(getIdentifier()))
        {
            return globalSymbolTable.getVarConstType(getIdentifier());
        }
        else if (globalSymbolTable.isTypeIdentifierInSymbolTable(getIdentifier()))
        {
            return globalSymbolTable.getTypeType(getIdentifier());
        }
        else
        {
            return nullptr;
        }
    }
    virtual std::string getIdentifier() const { return identifierToken; }
    std::shared_ptr<SymbolTableType> getType()
    {
        // return SymbolTableCharType::get();
        // I can do this because an Lvalue is associated with memory, therefore it is in the
        // SymbolTable.
        if (globalSymbolTable.isVarConstIdentifierInSymbolTable(getIdentifier()))
        {
            return globalSymbolTable.getVarConstType(getIdentifier());
        }
        else if (globalSymbolTable.isTypeIdentifierInSymbolTable(getIdentifier()))
        {
            return globalSymbolTable.getTypeType(getIdentifier());
        }
        else
        {
            return nullptr;
        }
    }
    ~LvalIdNode() {}
};
} // namespace ASTNamespace

#endif
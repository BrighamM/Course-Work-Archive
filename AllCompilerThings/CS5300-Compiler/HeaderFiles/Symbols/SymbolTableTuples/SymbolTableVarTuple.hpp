#ifndef SYMBOL_TABLE_VAR_TUPLE_HPP
#define SYMBOL_TABLE_VAR_TUPLE_HPP

#include "./AbstractSymbolTableTuple.hpp"

namespace ASTNamespace
{
class SymbolTableVarTuple : public AbstractSymbolTableTuple
{
  public:
    SymbolTableVarTuple(std::string inputSymbolIdentifier,
                        std::shared_ptr<SymbolTableType> inputSymbolType, int inputSymbolSize,
                        int inputRegisterOffset, std::string inputBaseRegister)
        : symbolIdentifier(inputSymbolIdentifier), symbolType(inputSymbolType),
          symbolSize(inputSymbolSize), registerOffSet(inputRegisterOffset),
          baseRegister(inputBaseRegister)
    {
    }

    std::string getIdentifier() const { return symbolIdentifier; }

    std::shared_ptr<SymbolTableType> getType() const { return symbolType; }

    int getSize() const { return symbolSize; }

    int getRegisterOffSet() const { return registerOffSet; }

    std::string getRegister() const { return baseRegister; }

  private:
    std::string symbolIdentifier;
    std::shared_ptr<SymbolTableType> symbolType;
    int symbolSize;
    int registerOffSet;
    std::string baseRegister;
};
} // namespace ASTNamespace

#endif
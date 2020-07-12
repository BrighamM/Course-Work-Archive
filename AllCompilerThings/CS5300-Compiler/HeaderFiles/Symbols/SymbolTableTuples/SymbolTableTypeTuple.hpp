#ifndef SYMBOL_TABLE_TYPE_TUPLE_HPP
#define SYMBOL_TABLE_TYPE_TUPLE_HPP

#include "./AbstractSymbolTableTuple.hpp"

namespace ASTNamespace
{
class SymbolTableTypeTuple : public AbstractSymbolTableTuple
{
  public:
    SymbolTableTypeTuple(std::string inputSymbolIdentifier,
                         std::shared_ptr<SymbolTableType> inputSymbolType)
        : symbolIdentifier(inputSymbolIdentifier), symbolType(inputSymbolType)
    {
    }

    std::string getIdentifier() const { return symbolIdentifier; }

    std::shared_ptr<SymbolTableType> getType() const { return symbolType; }

  private:
    std::string symbolIdentifier;
    std::shared_ptr<SymbolTableType> symbolType;
};
} // namespace ASTNamespace

#endif
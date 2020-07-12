#ifndef SYMBOL_TABLE_TYPE_SUB_SCOPE_HPP
#define SYMBOL_TABLE_TYPE_SUB_SCOPE_HPP

#include "../SymbolTableTuples/SymbolTableTypeTuple.hpp"
#include "./AbstractSymbolTableSubScope.hpp"
#include <vector>

namespace ASTNamespace
{
class SymbolTableTypeSubScope : AbstractSymbolTableSubScope
{
  public:
    SymbolTableTypeSubScope() {}

    std::vector<SymbolTableTypeTuple> typeSymbols;
};
} // namespace ASTNamespace

#endif
#ifndef SYMBOL_TABLE_CONST_SUB_SCOPE_HPP
#define SYMBOL_TABLE_CONST_SUB_SCOPE_HPP

#include "../SymbolTableTuples/SymbolTableConstTuple.hpp"
#include "./AbstractSymbolTableSubScope.hpp"
#include <vector>

namespace ASTNamespace
{
class SymbolTableConstSubScope : AbstractSymbolTableSubScope
{
  public:
    SymbolTableConstSubScope() {}

    std::vector<SymbolTableConstTuple> constSymbols;
};
} // namespace ASTNamespace

#endif
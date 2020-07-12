#ifndef SYMBOL_TABLE_VAR_SUB_SCOPE_HPP
#define SYMBOL_TABLE_VAR_SUB_SCOPE_HPP

#include "../SymbolTableTuples/SymbolTableVarTuple.hpp"
#include "./AbstractSymbolTableSubScope.hpp"
#include <vector>

namespace ASTNamespace
{
class SymbolTableVarSubScope : AbstractSymbolTableSubScope
{
  public:
    SymbolTableVarSubScope() {}

    std::vector<SymbolTableVarTuple> varSymbols;
};
} // namespace ASTNamespace

#endif
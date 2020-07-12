#ifndef SYMBOL_TABLE_TYPE_HPP
#define SYMBOL_TABLE_TYPE_HPP

#include "../../StringConstants/StringConstants.hpp"
#include <memory>

namespace ASTNamespace
{
class SymbolTableType
{
  public:
    virtual int size() = 0;
    virtual ~SymbolTableType() = default;
    virtual std::shared_ptr<SymbolTableType> getType() = 0;
};
} // namespace ASTNamespace

#endif
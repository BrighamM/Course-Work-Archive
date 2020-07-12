#ifndef ABSTRACT_SYMBOL_TABLE_TUPLE_HPP
#define ABSTRACT_SYMBOL_TABLE_TUPLE_HPP

#include "../../Registers/RegisterList/RegisterList.hpp"
#include "../SymbolTableTypes/SymbolTableType.hpp"
#include <iostream>
#include <memory>

namespace ASTNamespace
{
class AbstractSymbolTableTuple
{
  public:
    virtual std::string getIdentifier() const = 0;
    virtual std::shared_ptr<SymbolTableType> getType() const = 0;
};
} // namespace ASTNamespace

#endif
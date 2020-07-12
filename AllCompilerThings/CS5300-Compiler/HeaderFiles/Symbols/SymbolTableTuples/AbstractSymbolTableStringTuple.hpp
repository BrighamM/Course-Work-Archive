#ifndef ABSTRACT_SYMBOL_TABLE_STRING_TUPLE_HPP
#define ABSTRACT_SYMBOL_TABLE_STRING_TUPLE_HPP

#include "../../Registers/RegisterList/RegisterList.hpp"
#include <iostream>

namespace ASTNamespace
{
class AbstractSymbolTableStringTuple
{
  public:
    virtual std::string getIdentifier() const = 0;
    virtual std::string getLabel() const = 0;
};
} // namespace ASTNamespace

#endif
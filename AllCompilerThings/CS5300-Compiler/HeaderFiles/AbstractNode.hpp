#ifndef ABSTRACT_NODE_H
#define ABSTRACT_NODE_H

#include "./Registers/RegisterList/RegisterList.hpp"
#include "./Registers/RegisterPool/PsuedoRegister.hpp"
#include "./StringConstants/StringConstants.hpp"
#include "./Symbols/SymbolTable/SymbolTable.hpp"
#include "./Symbols/SymbolTableTypes/SymbolTableArrayType.hpp"
#include "./Symbols/SymbolTableTypes/SymbolTableBoolType.hpp"
#include "./Symbols/SymbolTableTypes/SymbolTableCharType.hpp"
#include "./Symbols/SymbolTableTypes/SymbolTableIntType.hpp"
#include "./Symbols/SymbolTableTypes/SymbolTableRecordType.hpp"
#include "./Symbols/SymbolTableTypes/SymbolTableStringType.hpp"
#include "./Symbols/SymbolTableTypes/SymbolTableType.hpp"
#include <iostream>
#include <memory>

namespace ASTNamespace
{
class AbstractNode
{
  public:
    virtual void emit() const = 0;
    virtual void emitSource() const = 0;
};
} // namespace ASTNamespace

#endif
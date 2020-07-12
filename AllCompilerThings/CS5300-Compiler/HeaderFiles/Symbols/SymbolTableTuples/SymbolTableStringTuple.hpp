#ifndef SYMBOL_TABLE_STRING_TUPLE_HPP
#define SYMBOL_TABLE_STRING_TUPLE_HPP

#include "./AbstractSymbolTableStringTuple.hpp"

namespace ASTNamespace
{
class SymbolTableStringTuple : public AbstractSymbolTableStringTuple
{
  public:
    SymbolTableStringTuple(std::string inputSymbolIdentifier, std::string inputSymbolLabel)
        : symbolIdentifier(inputSymbolIdentifier), symbolLabel(inputSymbolLabel)
    {
    }

    std::string getIdentifier() const { return symbolIdentifier; }

    std::string getLabel() const { return symbolLabel; }

    std::string getMipsDataString() const
    {
        return symbolLabel + ":" + "    " + ".asciiz" + "    " + symbolIdentifier;
    }

  private:
    std::string symbolIdentifier;
    std::string symbolLabel;
};
} // namespace ASTNamespace

#endif
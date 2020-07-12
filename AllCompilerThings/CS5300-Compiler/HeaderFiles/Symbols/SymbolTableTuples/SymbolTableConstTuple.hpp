#ifndef SYMBOL_TABLE_CONST_TUPLE_HPP
#define SYMBOL_TABLE_CONST_TUPLE_HPP

#include "./AbstractSymbolTableTuple.hpp"

namespace ASTNamespace
{
class SymbolTableConstTuple : public AbstractSymbolTableTuple
{
  public:
    SymbolTableConstTuple(std::string inputSymbolIdentifier,
                          std::shared_ptr<SymbolTableType> inputSymbolType, int inputIntRValue)
        : symbolIdentifier(inputSymbolIdentifier), symbolType(inputSymbolType),
          intRValue(inputIntRValue), stringRValue(""), charRValue(int(0)), boolRValue(nullptr)
    {
    }

    SymbolTableConstTuple(std::string inputSymbolIdentifier,
                          std::shared_ptr<SymbolTableType> inputSymbolType, bool inputBoolRValue)
        : symbolIdentifier(inputSymbolIdentifier), symbolType(inputSymbolType), intRValue(0),
          stringRValue(""), charRValue(int(0)), boolRValue(inputBoolRValue)
    {
    }

    SymbolTableConstTuple(std::string inputSymbolIdentifier,
                          std::shared_ptr<SymbolTableType> inputSymbolType, char inputCharRValue)
        : symbolIdentifier(inputSymbolIdentifier), symbolType(inputSymbolType), intRValue(0),
          stringRValue(""), charRValue(inputCharRValue), boolRValue(nullptr)
    {
    }

    SymbolTableConstTuple(std::string inputSymbolIdentifier,
                          std::shared_ptr<SymbolTableType> inputSymbolType,
                          std::string inputStringRValue)
        : symbolIdentifier(inputSymbolIdentifier), symbolType(inputSymbolType), intRValue(0),
          stringRValue(inputStringRValue), charRValue(int(0)), boolRValue(nullptr)
    {
    }

    std::string getIdentifier() const { return symbolIdentifier; }

    std::shared_ptr<SymbolTableType> getType() const { return symbolType; }

    std::string getStringRValue() const { return stringRValue; }

    char getCharRValue() const { return charRValue; }

    int getIntRValue() const { return intRValue; }

    bool getBoolRValue() const { return boolRValue; }

  private:
    std::string symbolIdentifier;
    std::shared_ptr<SymbolTableType> symbolType;
    std::string stringRValue;
    int intRValue;
    char charRValue;
    bool boolRValue;
};
} // namespace ASTNamespace

#endif
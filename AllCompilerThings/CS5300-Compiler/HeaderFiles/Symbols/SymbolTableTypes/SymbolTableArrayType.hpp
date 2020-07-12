#ifndef SYMBOL_TABLE_ARRAY_TYPE_HPP
#define SYMBOL_TABLE_ARRAY_TYPE_HPP

#include "SymbolTableType.hpp"

namespace ASTNamespace
{
struct SymbolTableArrayType : public SymbolTableType
{
  public:
    SymbolTableArrayType(std::shared_ptr<SymbolTableType> incomingElementArrayType,
                         int inputLowerBound, int inputUpperBound)
        : arrayElementType(incomingElementArrayType), arrayLowerBound(inputLowerBound),
          arrayUpperBound(inputUpperBound)
    {
    }

    int size()
    {
        int typeSize = arrayElementType->size();
        int numberOfArrayElements = arrayUpperBound - arrayLowerBound + 1;
        return numberOfArrayElements * typeSize;
    }

    int elementSize()
    {
        int typeSize = arrayElementType->size();
        return typeSize;
    }

    int lowerBound() { return arrayLowerBound; }
    std::shared_ptr<SymbolTableType> getType() { return arrayElementType; }

  private:
    std::shared_ptr<SymbolTableType> arrayElementType;
    int arrayLowerBound;
    int arrayUpperBound;
};
} // namespace ASTNamespace

#endif
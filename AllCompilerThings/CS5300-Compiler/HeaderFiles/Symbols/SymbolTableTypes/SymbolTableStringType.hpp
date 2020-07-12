#ifndef SYMBOL_TABLE_STRING_TYPE_HPP
#define SYMBOL_TABLE_STRING_TYPE_HPP

#include "SymbolTableType.hpp"

namespace ASTNamespace
{
struct SymbolTableStringType : public SymbolTableType
{
  public:
    static std::shared_ptr<SymbolTableType> get()
    {
        if (!pString)
        {
            pString = std::make_shared<SymbolTableStringType>();
        }
        return pString;
    }
    int size() { return globalStringConstants.getByteSizeFourInt(); }

    std::shared_ptr<SymbolTableType> getType() { return this->get(); }

  private:
    static std::shared_ptr<SymbolTableType> pString;
};
} // namespace ASTNamespace

#endif
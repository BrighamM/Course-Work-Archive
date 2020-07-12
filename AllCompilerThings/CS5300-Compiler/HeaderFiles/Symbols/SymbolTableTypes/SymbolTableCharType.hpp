#ifndef SYMBOL_TABLE_CHAR_TYPE_HPP
#define SYMBOL_TABLE_CHAR_TYPE_HPP

#include "SymbolTableType.hpp"

namespace ASTNamespace
{
struct SymbolTableCharType : public SymbolTableType
{
  public:
    static std::shared_ptr<SymbolTableType> get()
    {
        if (!pChar)
        {
            pChar = std::make_shared<SymbolTableCharType>();
        }
        return pChar;
    }
    int size() { return globalStringConstants.getByteSizeFourInt(); }
    std::shared_ptr<SymbolTableType> getType() { return this->get(); }

  private:
    static std::shared_ptr<SymbolTableType> pChar;
};
} // namespace ASTNamespace

#endif
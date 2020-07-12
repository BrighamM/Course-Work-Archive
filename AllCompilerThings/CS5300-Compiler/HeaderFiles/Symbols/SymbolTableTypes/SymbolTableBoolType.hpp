#ifndef SYMBOL_TABLE_BOOL_TYPE_HPP
#define SYMBOL_TABLE_BOOL_TYPE_HPP

#include "SymbolTableType.hpp"

namespace ASTNamespace
{
struct SymbolTableBoolType : public SymbolTableType
{
  public:
    static std::shared_ptr<SymbolTableType> get()
    {
        if (!pBool)
        {
            pBool = std::make_shared<SymbolTableBoolType>();
        }
        return pBool;
    }
    int size() { return globalStringConstants.getByteSizeFourInt(); }
    std::shared_ptr<SymbolTableType> getType() { return this->get(); }

  private:
    static std::shared_ptr<SymbolTableType> pBool;
};
} // namespace ASTNamespace

#endif
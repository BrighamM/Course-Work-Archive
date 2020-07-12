#ifndef SYMBOL_TABLE_INT_TYPE_HPP
#define SYMBOL_TABLE_INT_TYPE_HPP

#include "SymbolTableType.hpp"

namespace ASTNamespace
{
struct SymbolTableIntType : public SymbolTableType
{
  public:
    static std::shared_ptr<SymbolTableType> get()
    {
        if (!pInt)
        {
            pInt = std::make_shared<SymbolTableIntType>();
        }
        return pInt;
    }
    int size() { return globalStringConstants.getByteSizeFourInt(); }
    std::shared_ptr<SymbolTableType> getType() { return this->get(); }

  private:
    static std::shared_ptr<SymbolTableType> pInt;
};
} // namespace ASTNamespace

#endif
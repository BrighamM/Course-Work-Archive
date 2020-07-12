#ifndef SYMBOL_TABLE_RECORD_TYPE_HPP
#define SYMBOL_TABLE_RECORD_TYPE_HPP

#include "SymbolTableType.hpp"
#include "string"
#include <iostream>
#include <map>
#include <utility>
#include <vector>

namespace ASTNamespace
{
struct SymbolTableRecordType : public SymbolTableType
{
  public:
    SymbolTableRecordType(std::map<std::string, std::pair<int, std::shared_ptr<SymbolTableType>>>
                              inputMiniSymbolTable,
                          int inputRecordSize)
        : myMiniSymbolTable(inputMiniSymbolTable), recordSize(inputRecordSize)
    {
    }
    int size() { return recordSize; }

    std::shared_ptr<SymbolTableType> getType()
    {
        // std::shared_ptr<SymbolTableRecordType> sp =
        // std::make_shared<SymbolTableRecordType>(this);
        std::cout << "THIS SHOULD NEVER HAPPEN!!!" << std::endl;
        return nullptr;
        // std::cout << "SymbolTableRecordTYpe is not working yet" << std::endl;
        // return nullptr;
    }

    std::pair<int, std::shared_ptr<SymbolTableType>> getOffsetAndType(std::string keyValue)
    {
        return myMiniSymbolTable.at(keyValue);
    }

    int recordSize;
    std::map<std::string, std::pair<int, std::shared_ptr<SymbolTableType>>> myMiniSymbolTable;

  private:
};
} // namespace ASTNamespace

#endif
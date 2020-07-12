#ifndef RECORD_TYPE_NODE_HPP
#define RECORD_TYPE_NODE_HPP

#include "../TypeNode.hpp"
#include "FieldDeclNode.hpp"
#include <map>
#include <utility>
#include <vector>

// RecordType : RECORD_TOKEN FieldDeclsList END_TOKEN {$$ = new ASTNamespace::RecordTypeNode($2);};

namespace ASTNamespace
{
class RecordTypeNode : public TypeNode
{
    std::vector<FieldDeclNode*>* fieldDeclList;

  public:
    RecordTypeNode(std::vector<FieldDeclNode*>* inputList) : fieldDeclList(inputList) {}
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual std::shared_ptr<SymbolTableType> getSymbolTableType() const
    {
        // This was written with help from Philip Nelson.
        // I am going to do the same thing in getSymboltableType()
        std::map<std::string, std::pair<int, std::shared_ptr<SymbolTableType>>> miniSymbolTable;
        std::vector<FieldDeclNode*> inlineFieldDeclList = *fieldDeclList;
        int offset = 0;
        for (auto&& f : inlineFieldDeclList)
        {
            for (auto&& id : f->getStringIdList())
            {
                miniSymbolTable.emplace(id, std::make_pair(offset, f->getSymbolTableType()));
                offset += f->getSymbolTableType()->size();
            }
        }
        std::shared_ptr<SymbolTableRecordType> recordTypePointer =
            std::make_shared<SymbolTableRecordType>(miniSymbolTable, offset);
        return recordTypePointer;
    }
    virtual void emitSource() const
    {
        std::cout << "RECORD" << std::endl;
        std::vector<FieldDeclNode*> inlineFieldDeclList = *fieldDeclList;
        for (int i = 0; i < inlineFieldDeclList.size(); i++)
        {
            inlineFieldDeclList[i]->emitSource();
        }
        std::cout << "END";
    }
    virtual std::shared_ptr<SymbolTableType> getSymbolTableTypeForVarDecl() const
    {
        // This was written with help from Philip Nelson.
        // I am going to do the same thing in getSymboltableType()
        std::map<std::string, std::pair<int, std::shared_ptr<SymbolTableType>>> miniSymbolTable;
        std::vector<FieldDeclNode*> inlineFieldDeclList = *fieldDeclList;
        int offset = 0;
        for (auto&& f : inlineFieldDeclList)
        {
            for (auto&& id : f->getStringIdList())
            {
                miniSymbolTable.emplace(id, std::make_pair(offset, f->getSymbolTableType()));
                offset += f->getSymbolTableType()->size();
            }
        }
        std::shared_ptr<SymbolTableRecordType> recordTypePointer =
            std::make_shared<SymbolTableRecordType>(miniSymbolTable, offset);
        return recordTypePointer;
    }
    ~RecordTypeNode()
    {
        delete fieldDeclList;
        fieldDeclList = 0;
    }
};
} // namespace ASTNamespace

#endif
#ifndef SYMBOL_TABLE_SCOPE_HPP
#define SYMBOL_TABLE_SCOPE_HPP

#include "../../StringConstants/StringConstants.hpp"
#include "../SymbolTableTypes/SymbolTableBoolType.hpp"
#include "../SymbolTableTypes/SymbolTableCharType.hpp"
#include "../SymbolTableTypes/SymbolTableIntType.hpp"
#include "../SymbolTableTypes/SymbolTableStringType.hpp"
#include "./SymbolTableConstSubScope.hpp"
#include "./SymbolTableTypeSubScope.hpp"
#include "./SymbolTableVarSubScope.hpp"

namespace ASTNamespace
{
class SymbolTableScope
{
  public:
    SymbolTableScope() {}

    void loadDefaults()
    {
        // "true" = true => 1
        SymbolTableConstTuple symbolTableConstTupleTrue(
            globalStringConstants.getLowerCaseTrueString(),
            ASTNamespace::SymbolTableBoolType::get(), true);
        this->symbolTableConstSubScope.constSymbols.emplace_back(symbolTableConstTupleTrue);
        // "false" = false => 0
        SymbolTableConstTuple symbolTableConstTupleFalse(
            globalStringConstants.getLowerCaseFalseString(),
            ASTNamespace::SymbolTableBoolType::get(), false);
        this->symbolTableConstSubScope.constSymbols.emplace_back(symbolTableConstTupleFalse);

        // "int"
        SymbolTableTypeTuple symbolTableTypeTupleInt(globalStringConstants.getLowerCaseIntString(),
                                                     ASTNamespace::SymbolTableIntType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleInt);
        // "integer"
        SymbolTableTypeTuple symbolTableTypeTupleInteger(
            globalStringConstants.getLowerCaseIntegerString(),
            ASTNamespace::SymbolTableIntType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleInteger);
        // "INT"
        SymbolTableTypeTuple symbolTableTypeTupleInt1(globalStringConstants.getUpperCaseIntString(),
                                                      ASTNamespace::SymbolTableIntType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleInt1);
        // "INTEGER"
        SymbolTableTypeTuple symbolTableTypeTupleInteger1(
            globalStringConstants.getUpperCaseIntegerString(),
            ASTNamespace::SymbolTableIntType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleInteger1);

        // "string"
        SymbolTableTypeTuple symbolTableTypeTupleString(
            globalStringConstants.getLowerCaseStringString(),
            ASTNamespace::SymbolTableStringType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleString);
        // "STRING"
        SymbolTableTypeTuple symbolTableTypeTupleString1(
            globalStringConstants.getUpperCaseStringString(),
            ASTNamespace::SymbolTableStringType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleString1);

        // "char"
        SymbolTableTypeTuple symbolTableTypeTupleChar(
            globalStringConstants.getLowerCaseCharString(),
            ASTNamespace::SymbolTableCharType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleChar);
        // "character"
        SymbolTableTypeTuple symbolTableTypeTupleCharacter(
            globalStringConstants.getLowerCaseCharacterString(),
            ASTNamespace::SymbolTableCharType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleCharacter);
        // "CHAR"
        SymbolTableTypeTuple symbolTableTypeTupleChar1(
            globalStringConstants.getUpperCaseCharString(),
            ASTNamespace::SymbolTableCharType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleChar1);
        // "CHARACTER"
        SymbolTableTypeTuple symbolTableTypeTupleCharacter1(
            globalStringConstants.getUpperCaseCharacterString(),
            ASTNamespace::SymbolTableCharType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleCharacter1);

        // "bool"
        SymbolTableTypeTuple symbolTableTypeTupleBool(
            globalStringConstants.getLowerCaseBoolString(),
            ASTNamespace::SymbolTableBoolType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleBool);
        // "boolean"
        SymbolTableTypeTuple symbolTableTypeTupleBoolean(
            globalStringConstants.getLowerCaseBooleanString(),
            ASTNamespace::SymbolTableBoolType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleBoolean);
        // "BOOL"
        SymbolTableTypeTuple symbolTableTypeTupleBool1(
            globalStringConstants.getUpperCaseBoolString(),
            ASTNamespace::SymbolTableBoolType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleBool1);
        // "BOOLEAN"
        SymbolTableTypeTuple symbolTableTypeTupleBoolean1(
            globalStringConstants.getUpperCaseBooleanString(),
            ASTNamespace::SymbolTableBoolType::get());
        this->symbolTableTypeSubScope.typeSymbols.emplace_back(symbolTableTypeTupleBoolean1);
    }

    SymbolTableConstSubScope symbolTableConstSubScope;
    SymbolTableVarSubScope symbolTableVarSubScope;
    SymbolTableTypeSubScope symbolTableTypeSubScope;
};
} // namespace ASTNamespace

#endif
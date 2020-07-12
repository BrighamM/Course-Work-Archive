#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "../SymbolTableScopes/SymbolTableScope.hpp"
#include "../SymbolTableTuples/SymbolTableStringTuple.hpp"
#include "../SymbolTableTypes/SymbolTableBoolType.hpp"
#include "../SymbolTableTypes/SymbolTableCharType.hpp"
#include "../SymbolTableTypes/SymbolTableIntType.hpp"
#include "../SymbolTableTypes/SymbolTableStringType.hpp"
#include "./AbstractSymbolTable.hpp"
#include <utility>

// #include "../SymbolTableTuples/SymbolTableVarTuple.hpp"

namespace ASTNamespace
{
class SymbolTable : public AbstractSymbolTable
{
  public:
    SymbolTable() {}

    /**
     *
     * Everytime register that gets thrown into the symbol table needs to be accounted for and
     * the symbol table needs to know where the next empty location is that can be written to for
     * that respective register.
     *
     */

    void saveConstIntToSymbolTable(std::string identifier, int inputIntRValue)
    {
        symbolTableStack.back().symbolTableConstSubScope.constSymbols.emplace_back(
            identifier, SymbolTableIntType::get(), inputIntRValue);
    }
    void saveConstBoolToSymbolTable(std::string identifier, bool inputBoolRValue)
    {
        symbolTableStack.back().symbolTableConstSubScope.constSymbols.emplace_back(
            identifier, SymbolTableBoolType::get(), inputBoolRValue);
    }
    void saveConstStringToSymbolTable(std::string identifier, std::string inputStringRValue)
    {
        symbolTableStack.back().symbolTableConstSubScope.constSymbols.emplace_back(
            identifier, SymbolTableStringType::get(), inputStringRValue);
        // now I need to add a label to the string portion of the table.
        std::string tempLabel = getDataStringLabel(inputStringRValue);
    }
    void saveConstCharToSymbolTable(std::string identifier, char inputCharRValue)
    {
        symbolTableStack.back().symbolTableConstSubScope.constSymbols.emplace_back(
            identifier, SymbolTableCharType::get(), inputCharRValue);
    }

    void saveVarsListToSymbolTable(std::vector<std::string> identifierList,
                                   std::shared_ptr<SymbolTableType> typeType, int typeSize,
                                   std::string baseRegister)
    {
        if (registerMap.find(baseRegister) == registerMap.end())
        {
            // Key was not found, so do an insert.
            registerMap.insert(std::make_pair(baseRegister, 0));
        }
        for (int i = 0; i < identifierList.size(); i++)
        {
            int nextAvailableAddressAtRegister = registerMap.at(baseRegister);
            symbolTableStack.back().symbolTableVarSubScope.varSymbols.emplace_back(
                SymbolTableVarTuple(identifierList[i], typeType, typeSize,
                                    nextAvailableAddressAtRegister, baseRegister));
            registerMap[baseRegister] = registerMap.at(baseRegister) + typeSize;
        }
    }

    void saveTypeToSymbolTable(std::string identifier, std::shared_ptr<SymbolTableType> typeType)
    {
        SymbolTableTypeTuple symbolTableTypeTuple(identifier, typeType);
        symbolTableStack.back().symbolTableTypeSubScope.typeSymbols.emplace_back(
            symbolTableTypeTuple);
    }

    std::string getDataStringLabel(std::string inputString)
    {
        /**
         * 1. Check to see if the label exists in the String Symbol Table
         */
        if (findStringPositionInStringLabelTable(inputString) == -1)
        {
            // Did not find it. Now insert it into table
            SymbolTableStringTuple symbolTableStringTuple(
                inputString, globalStringConstants.getLowerCaseStringString() +
                                 std::to_string(stringLabelTable.size()));
            stringLabelTable.emplace_back(symbolTableStringTuple);
            return symbolTableStringTuple.getLabel();
        }
        else
        {
            // found it!
            return stringLabelTable[findStringPositionInStringLabelTable(inputString)].getLabel();
        }
    }

    int findStringPositionInStringLabelTable(std::string inputString)
    {
        if (stringLabelTable.size() == 0)
        {
            return -1;
        }
        for (int i = stringLabelTable.size() - 1; i >= 0; --i)
        {
            if (stringLabelTable[i].getIdentifier() == inputString)
            {
                return i;
            }
        }
        return -1;
    }

    std::vector<std::string> getNextForLoopExitLabels()
    {
        // get the current size of the forLoopExitLabels vector.
        int currSize = forLoopExitLabels.size();
        // make a new string pair;
        std::string forLoopLabel = "ForLoop" + std::to_string(currSize);
        std::string exitLoopLabel = "Exit" + std::to_string(currSize);
        std::vector<std::string> tempVector;
        tempVector.emplace_back(forLoopLabel);
        tempVector.emplace_back(exitLoopLabel);
        forLoopExitLabels.emplace_back(tempVector);
        return tempVector;
    }

    std::vector<std::string> getNextRepeatEndLabels()
    {
        // get the current size of the forLoopExitLabels vector.
        int currSize = repeatLabels.size();
        // make a new string pair;
        std::string repeatLabelString = "RepeatLabel" + std::to_string(currSize);
        std::string endRepeatLabelString = "EndRepeatLabel" + std::to_string(currSize);
        std::vector<std::string> tempVector;
        tempVector.emplace_back(repeatLabelString);
        tempVector.emplace_back(endRepeatLabelString);
        repeatLabels.emplace_back(tempVector);
        return tempVector;
    }

    std::vector<std::string> getNextWhileEndLabels()
    {
        // get the current size of the forLoopExitLabels vector.
        int currSize = whileLabels.size();
        // make a new string pair;
        std::string whileLabelString = "WhileLabel" + std::to_string(currSize);
        std::string endWhileLabelString = "EndWhileLabel" + std::to_string(currSize);
        std::vector<std::string> tempVector;
        tempVector.emplace_back(whileLabelString);
        tempVector.emplace_back(endWhileLabelString);
        whileLabels.emplace_back(tempVector);
        return tempVector;
    }

    std::vector<std::string> getNextIf_ElseIf_Else_EndLabels()
    {
        int currSize = ifElseEndLabels.size();
        std::string ifBlock = "ifBlock" + std::to_string(currSize);
        std::string elseIfBlock = "elseIfBlock" + std::to_string(currSize);
        std::string elseBlock = "elseBlock" + std::to_string(currSize);
        std::string endBlock = "endBlock" + std::to_string(currSize);
        std::vector<std::string> returnVector;
        returnVector.emplace_back(ifBlock);
        returnVector.emplace_back(elseIfBlock);
        returnVector.emplace_back(elseBlock);
        returnVector.emplace_back(endBlock);
        ifElseEndLabels.emplace_back(returnVector);
        return returnVector;
    }

    void printDataStringsTable()
    {
        for (int i = 0; i < stringLabelTable.size(); ++i)
        {
            std::cout << stringLabelTable[i].getMipsDataString() << std::endl;
        }
    }

    void enterScope()
    {
        SymbolTableScope firstSymboleTableScope;
        firstSymboleTableScope.loadDefaults();
        symbolTableStack.emplace_back(firstSymboleTableScope);
        pushNewScope();
    }

    void pushNewScope()
    {
        SymbolTableScope newSymbolTableScope;
        symbolTableStack.emplace_back(newSymbolTableScope);
    }

    void popLastScope()
    {
        symbolTableStack.pop_back();
        if (registerMap.find(globalRegisterList.getFramePointerRegister()) != registerMap.end())
        {
            // I found it!
            // registerMap.insert(std::make_pair(globalRegisterList.getFramePointerRegister(), 0));
            registerMap.at(globalRegisterList.getFramePointerRegister()) = 0;
        }
    }

    std::string getVarIdentierBaseRegister(std::string identifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int varTableSize = symbolTableStack[k].symbolTableVarSubScope.varSymbols.size();
            for (int i = varTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableVarSubScope.varSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return symbolTableStack[k].symbolTableVarSubScope.varSymbols[i].getRegister();
                }
            }
        }
    }

    int getVarIdentifierBaseRegisterOffSet(std::string identifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int varTableSize = symbolTableStack[k].symbolTableVarSubScope.varSymbols.size();
            for (int i = varTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableVarSubScope.varSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return symbolTableStack[k]
                        .symbolTableVarSubScope.varSymbols[i]
                        .getRegisterOffSet();
                }
            }
        }
        std::cout << "SYMBOL TABLE RegisterOffSet error!" << std::endl;
        return -99; // Error
    }

    std::shared_ptr<SymbolTableType> getVarConstType(std::string identifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int varTableSize = symbolTableStack[k].symbolTableVarSubScope.varSymbols.size();
            for (int i = varTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableVarSubScope.varSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return symbolTableStack[k].symbolTableVarSubScope.varSymbols[i].getType();
                }
            }

            int constTableSize = symbolTableStack[k].symbolTableConstSubScope.constSymbols.size();
            for (int i = constTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableConstSubScope.constSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return symbolTableStack[k].symbolTableConstSubScope.constSymbols[i].getType();
                }
            }
        }
        return nullptr;
    }

    std::shared_ptr<SymbolTableType> getTypeType(std::string typeIdentifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int typeTableSize = symbolTableStack[k].symbolTableTypeSubScope.typeSymbols.size();
            for (int i = typeTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableTypeSubScope.typeSymbols[i].getIdentifier() ==
                    typeIdentifier)
                {
                    return symbolTableStack[k].symbolTableTypeSubScope.typeSymbols[i].getType();
                }
            }
        }
        return nullptr;
    }

    int getTypeTypeSize(std::string typeIdentifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int typeTableSize = symbolTableStack[k].symbolTableTypeSubScope.typeSymbols.size();
            for (int i = typeTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableTypeSubScope.typeSymbols[i].getIdentifier() ==
                    typeIdentifier)
                {
                    return symbolTableStack[k]
                        .symbolTableTypeSubScope.typeSymbols[i]
                        .getType()
                        ->size();
                }
            }
        }
    }

    bool isVarConstIdentifierInSymbolTable(std::string identifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int varTableSize = symbolTableStack[k].symbolTableVarSubScope.varSymbols.size();
            for (int i = varTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableVarSubScope.varSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return true;
                }
            }
            int constTableSize = symbolTableStack[k].symbolTableConstSubScope.constSymbols.size();
            for (int i = constTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableConstSubScope.constSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool isTypeIdentifierInSymbolTable(std::string typeIdentifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int typeTableSize = symbolTableStack[k].symbolTableTypeSubScope.typeSymbols.size();
            for (int i = typeTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableTypeSubScope.typeSymbols[i].getIdentifier() ==
                    typeIdentifier)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool isConst(std::string identifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int varTableSize = symbolTableStack[k].symbolTableVarSubScope.varSymbols.size();
            for (int i = varTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableVarSubScope.varSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return false;
                }
            }

            int typeTableSize = symbolTableStack[k].symbolTableTypeSubScope.typeSymbols.size();
            for (int i = typeTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableTypeSubScope.typeSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return false;
                }
            }

            int constTableSize = symbolTableStack[k].symbolTableConstSubScope.constSymbols.size();
            for (int i = constTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableConstSubScope.constSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return true;
                }
            }
        }
        std::cout << "We have issues in the symbol Table " << std::endl;
        return false; // WE HAVE OTHER PROBLEMS IF WE HIT HERE.
    }

    int getConstIntValue(std::string identifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int constTableSize = symbolTableStack[k].symbolTableConstSubScope.constSymbols.size();
            for (int i = constTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableConstSubScope.constSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return symbolTableStack[k]
                        .symbolTableConstSubScope.constSymbols[i]
                        .getIntRValue();
                }
            }
        }
    }

    bool getConstBoolValue(std::string identifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int constTableSize = symbolTableStack[k].symbolTableConstSubScope.constSymbols.size();
            for (int i = constTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableConstSubScope.constSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return symbolTableStack[k]
                        .symbolTableConstSubScope.constSymbols[i]
                        .getBoolRValue();
                }
            }
        }
    }

    char getConstCharValue(std::string identifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int constTableSize = symbolTableStack[k].symbolTableConstSubScope.constSymbols.size();
            for (int i = constTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableConstSubScope.constSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return symbolTableStack[k]
                        .symbolTableConstSubScope.constSymbols[i]
                        .getCharRValue();
                }
            }
        }
    }

    std::string getConstStringValue(std::string identifier)
    {
        for (int k = symbolTableStack.size() - 1; k >= 0; k--)
        {
            int constTableSize = symbolTableStack[k].symbolTableConstSubScope.constSymbols.size();
            for (int i = constTableSize - 1; i >= 0; i--)
            {
                if (symbolTableStack[k].symbolTableConstSubScope.constSymbols[i].getIdentifier() ==
                    identifier)
                {
                    return symbolTableStack[k]
                        .symbolTableConstSubScope.constSymbols[i]
                        .getStringRValue();
                }
            }
        }
    }

    bool shouldUseFramePointer()
    {
        if (symbolTableStack.size() > 2)
        {
            return true;
        }
        return false;
    }

    void storeProcedurePrototype(std::string theIdentifier, std::vector<bool> refVector)
    {
        std::vector<bool> myRefVector;
        for (int i = 0; i < refVector.size(); i++)
        {
            myRefVector.emplace_back(refVector[i]);
        }
        std::string myIdentifier = theIdentifier;

        std::pair<std::string, std::vector<bool>> myTempPair =
            std::make_pair(myIdentifier, myRefVector);
        prototypeProcedureTable.emplace_back(myTempPair);
    }

    std::vector<bool> getProcedurePrototypeBoolVector(std::string someIdentifier)
    {
        for (int i = 0; i < prototypeProcedureTable.size(); i++)
        {
            if (someIdentifier == prototypeProcedureTable[i].first)
            {
                return prototypeProcedureTable[i].second;
            }
        }
        std::cout << "STUFF IS REALLY BROKEN SKEI89" << std::endl;
        return prototypeProcedureTable[0].second;
    }

  private:
    std::vector<std::pair<std::string, std::vector<bool>>> prototypeProcedureTable;
    std::vector<SymbolTableScope> symbolTableStack;
    std::vector<SymbolTableStringTuple> stringLabelTable;
    std::unordered_map<std::string, int> registerMap;
    std::vector<std::vector<std::string>> forLoopExitLabels;
    std::vector<std::vector<std::string>> ifElseEndLabels;
    std::vector<std::vector<std::string>> repeatLabels;
    std::vector<std::vector<std::string>> whileLabels;
};
} // namespace ASTNamespace

extern ASTNamespace::SymbolTable globalSymbolTable;

#endif
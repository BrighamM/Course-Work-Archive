cmake_minimum_required(VERSION 2.8)
project(cpsl)

find_package(BISON)
find_package(FLEX)

bison_target(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
flex_target(Scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
add_flex_bison_dependency(Scanner Parser)

set(EXTRA_COMPILE_FLAGS "-g3 -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(cpsl_srcs
  main.cpp
  HeaderFiles/globals.hpp
  SourceFiles/globals.cpp

  HeaderFiles/Registers/RegisterList/AbstractRegisterList.hpp
  HeaderFiles/Registers/RegisterList/RegisterList.hpp
  HeaderFiles/Registers/RegisterList/RegisterList.cpp

  HeaderFiles/Registers/RegisterPool/AbstractPsuedoRegister.hpp
  HeaderFiles/Registers/RegisterPool/AbstractRegisterPool.hpp
  HeaderFiles/Registers/RegisterPool/PsuedoRegister.hpp
  HeaderFiles/Registers/RegisterPool/RegisterPool.cpp
  HeaderFiles/Registers/RegisterPool/RegisterPool.hpp

  HeaderFiles/StringConstants/AbstractStringConstants.hpp
  HeaderFiles/StringConstants/StringConstants.hpp
  HeaderFiles/StringConstants/StringConstants.cpp

  HeaderFiles/Symbols/SymbolTable/AbstractSymbolTable.hpp
  HeaderFiles/Symbols/SymbolTable/SymbolTable.cpp
  HeaderFiles/Symbols/SymbolTable/SymbolTable.hpp

  HeaderFiles/Symbols/SymbolTableScopes/AbstractSymbolTableScope.hpp
  HeaderFiles/Symbols/SymbolTableScopes/AbstractSymbolTableSubScope.hpp
  HeaderFiles/Symbols/SymbolTableScopes/SymbolTableConstSubScope.hpp
  HeaderFiles/Symbols/SymbolTableScopes/SymbolTableScope.hpp
  HeaderFiles/Symbols/SymbolTableScopes/SymbolTableTypeSubScope.hpp
  HeaderFiles/Symbols/SymbolTableScopes/SymbolTableVarSubScope.hpp

  HeaderFiles/Symbols/SymbolTableTuples/AbstractSymbolTableTuple.hpp
  HeaderFiles/Symbols/SymbolTableTuples/AbstractSymbolTableStringTuple.hpp
  HeaderFiles/Symbols/SymbolTableTuples/SymbolTableStringTuple.hpp
  HeaderFiles/Symbols/SymbolTableTuples/SymbolTableConstTuple.hpp
  HeaderFiles/Symbols/SymbolTableTuples/SymbolTableTypeTuple.hpp
  HeaderFiles/Symbols/SymbolTableTuples/SymbolTableVarTuple.hpp



  HeaderFiles/AbstractNode.hpp

  HeaderFiles/DerivedNodes/ConstantDeclarations/ConstantDeclNode.hpp

  HeaderFiles/DerivedNodes/ExpressionNodes/AdditionExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/AndExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/CHARCONSTExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/CHR_ExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/DivisionExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/EquivalenceExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/ExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/FunctionCallExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/GreaterThanExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/GreaterThanOrEqualExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/INTEGERExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/LessThanExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/LessThanOrEqualExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/LVALExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/ModulusExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/MultiplicationExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/NotEqualExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/NotExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/ORD_ExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/OrExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/ParensExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/PRED_ExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/STRINGExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/SubtractionExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/SUCC_ExpressionNode.hpp
  HeaderFiles/DerivedNodes/ExpressionNodes/UnaryMinusExpressionNode.hpp

  HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/BlockNode.hpp
  HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/BodyNode.hpp
  HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/FormalParametersListTypeNode.hpp
  HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/FunctionDeclNode.hpp
  HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/FunctionSignatureNode.hpp
  HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/ProcedureAndFunctionDeclNode.hpp
  HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/ProcedureDeclNode.hpp
  HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/ProcedureSignatureNode.hpp

  HeaderFiles/DerivedNodes/StatementNodes/AssignmentNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/ElseClauseNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/ElseIfClauseNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/ForStatementNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/IfStatementNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/ProcedureCallNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/ReadStatementNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/RepeatStatementNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/ReturnStatementNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/StatementNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/StopStatementNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/WhileStatmentNode.hpp
  HeaderFiles/DerivedNodes/StatementNodes/WriteStatementNode.hpp

  HeaderFiles/DerivedNodes/TypeDeclarations/ArrayTypeNode.hpp
  HeaderFiles/DerivedNodes/TypeDeclarations/FieldDeclNode.hpp
  HeaderFiles/DerivedNodes/TypeDeclarations/RecordTypeNode.hpp
  HeaderFiles/DerivedNodes/TypeDeclarations/SimpleTypeNode.hpp
  HeaderFiles/DerivedNodes/TypeDeclarations/TypeDeclNode.hpp  

  HeaderFiles/DerivedNodes/VariableDeclarations/VarDeclNode.hpp

  HeaderFiles/DerivedNodes/FunctionCallNode.hpp
  HeaderFiles/DerivedNodes/Lval_Bracketed_Expression_Node.hpp
  HeaderFiles/DerivedNodes/Lval_Dot_Id_Node.hpp
  HeaderFiles/DerivedNodes/Lval_Id_Node.hpp
  HeaderFiles/DerivedNodes/LValueNode.hpp
  HeaderFiles/DerivedNodes/ProgramNode.hpp
  HeaderFiles/DerivedNodes/TypeNode.hpp

  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableBoolType.hpp
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableBoolType.cpp
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableIntType.hpp
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableIntType.cpp
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableCharType.hpp
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableCharType.cpp
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableStringType.hpp
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableStringType.cpp
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableArrayType.hpp
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableRecordType.hpp 
  HeaderFiles/Symbols/SymbolTableTypes/SymbolTableType.hpp
  
  ${BISON_Parser_OUTPUTS}
  ${FLEX_Scanner_OUTPUTS}
)
source_group("cpsl" FILES ${cpsl_srcs})

add_executable(cpsl ${cpsl_srcs})
target_link_libraries(cpsl ${BISON_LIBRARIES})
target_include_directories(cpsl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


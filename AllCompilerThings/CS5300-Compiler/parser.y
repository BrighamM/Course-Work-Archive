%{
/**
Referenced and used code from https://github.com/ksundberg/CourseMaterials/blob/master/cs5300/examples/calc/parser.y
and https://github.com/ksundberg/CS6300/blob/master/FrontEnd/parser.y
for the creation of this file.
*/
#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "HeaderFiles/AbstractNode.hpp"

#include "HeaderFiles/DerivedNodes/ConstantDeclarations/ConstantDeclNode.hpp"

#include "HeaderFiles/DerivedNodes/ExpressionNodes/AdditionExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/AndExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/CHARCONSTExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/CHR_ExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/DivisionExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/EquivalenceExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/ExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/FunctionCallExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/GreaterThanExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/GreaterThanOrEqualExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/INTEGERExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/LessThanExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/LessThanOrEqualExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/LVALExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/ModulusExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/MultiplicationExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/NotEqualExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/NotExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/ORD_ExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/OrExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/ParensExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/PRED_ExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/STRINGExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/SubtractionExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/SUCC_ExpressionNode.hpp"
#include "HeaderFiles/DerivedNodes/ExpressionNodes/UnaryMinusExpressionNode.hpp"

#include "HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/BlockNode.hpp"
#include "HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/BodyNode.hpp"
#include "HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/FormalParametersListTypeNode.hpp"
#include "HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/FunctionDeclNode.hpp"
#include "HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/FunctionSignatureNode.hpp"
#include "HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/ProcedureAndFunctionDeclNode.hpp"
#include "HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/ProcedureDeclNode.hpp"
#include "HeaderFiles/DerivedNodes/ProcedureAndFunctionDeclarations/ProcedureSignatureNode.hpp"

#include "HeaderFiles/DerivedNodes/StatementNodes/AssignmentNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/ElseClauseNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/ElseIfClauseNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/ForStatementNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/IfStatementNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/ProcedureCallNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/ReadStatementNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/RepeatStatementNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/ReturnStatementNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/StatementNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/StopStatementNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/WhileStatmentNode.hpp"
#include "HeaderFiles/DerivedNodes/StatementNodes/WriteStatementNode.hpp"

#include "HeaderFiles/DerivedNodes/TypeDeclarations/ArrayTypeNode.hpp"
#include "HeaderFiles/DerivedNodes/TypeDeclarations/FieldDeclNode.hpp"
#include "HeaderFiles/DerivedNodes/TypeDeclarations/RecordTypeNode.hpp"
#include "HeaderFiles/DerivedNodes/TypeDeclarations/SimpleTypeNode.hpp"
#include "HeaderFiles/DerivedNodes/TypeDeclarations/TypeDeclNode.hpp"

#include "HeaderFiles/DerivedNodes/VariableDeclarations/VarDeclNode.hpp"

#include "HeaderFiles/DerivedNodes/FunctionCallNode.hpp"
#include "HeaderFiles/DerivedNodes/Lval_Bracketed_Expression_Node.hpp"
#include "HeaderFiles/DerivedNodes/Lval_Dot_Id_Node.hpp"
#include "HeaderFiles/DerivedNodes/Lval_Id_Node.hpp"
#include "HeaderFiles/DerivedNodes/LValueNode.hpp"
#include "HeaderFiles/DerivedNodes/ProgramNode.hpp"
#include "HeaderFiles/DerivedNodes/TypeNode.hpp"

extern int yylex();
void yyerror (char const*);
extern std::shared_ptr<ASTNamespace::ProgramNode> pNode;
%}

%union
{
  ASTNamespace::ProgramNode* programNode_type;
  ASTNamespace::ConstantDeclNode* constantDeclNode_type;
  ASTNamespace::TypeDeclNode* typeDeclNode_type;
  ASTNamespace::TypeNode* typeNode_type;
  ASTNamespace::SimpleTypeNode* simpleTypeNode_type;
  ASTNamespace::RecordTypeNode* recordTypeNode_type;
  ASTNamespace::ArrayTypeNode* arrayTypeNode_type;
  ASTNamespace::FieldDeclNode* fieldDeclNode_type;
  ASTNamespace::VarDeclNode* varDeclNode_type;
  ASTNamespace::ProcedureAndFunctionDeclNode* procedureAndFunctionDeclNode_type;
  ASTNamespace::ProcedureDeclNode* procedureDeclNode_type;
  ASTNamespace::FunctionDeclNode* functionDeclNode_type;
  ASTNamespace::ProcedureSignatureNode* procedureSignatureNode_type;
  ASTNamespace::FunctionSignatureNode* functionSignatureNode_type;
  ASTNamespace::FormalParametersListTypeNode* FormalParametersListTypeNode_type;
  ASTNamespace::BodyNode* bodyNode_type;
  ASTNamespace::BlockNode* blockNode_type;
  ASTNamespace::StatementNode* statementNode_type;
  ASTNamespace::ElseIfClauseNode* elseIfClauseNode_type;
  ASTNamespace::ElseClauseNode* elseClauseNode_type;
  ASTNamespace::ExpressionNode* expressionNode_type;
  ASTNamespace::FunctionCallNode* functionCallNode_type;
  ASTNamespace::LValueNode* lValueNode_type;
 
  std::vector<ASTNamespace::ConstantDeclNode*>* constantDeclVector_type;
  std::vector<ASTNamespace::TypeDeclNode*>* typeDeclVector_type;
  std::vector<ASTNamespace::FieldDeclNode*>* fieldDeclVector_type;
  std::vector<ASTNamespace::VarDeclNode*>* varDeclVector_type;
  std::vector<ASTNamespace::ProcedureAndFunctionDeclNode*>* procedureAndFunctionDeclVector_type;
  std::vector<ASTNamespace::FormalParametersListTypeNode*>* formalParameterVector_type;
  std::vector<ASTNamespace::StatementNode*>* statementVector_type;
  std::vector<ASTNamespace::ElseIfClauseNode*>* elseIfClauseVector_type;
  std::vector<ASTNamespace::ExpressionNode*>* expressionVector_type;
  std::vector<ASTNamespace::LValueNode*>* lValueVector_type;

  std::vector<char*>* stringVector_type;

  char* string_type;
  int int_type;
  char char_type;
}

%token ARRAY_TOKEN 
%token BEGIN_TOKEN 
%token CHR_TOKEN 
%token CONST_TOKEN 
%token DOWNTO_TOKEN 
%token DO_TOKEN 
%token ELSE_TOKEN 
%token ELSEIF_TOKEN 
%token END_TOKEN 
%token FORWARD_TOKEN 
%token FOR_TOKEN 
%token FUNCTION_TOKEN 
%token IF_TOKEN 
%token OF_TOKEN
%token ORD_TOKEN 
%token PRED_TOKEN 
%token PROCEDURE_TOKEN 
%token READ_TOKEN 
%token RECORD_TOKEN 
%token REF_TOKEN 
%token REPEAT_TOKEN 
%token RETURN_TOKEN 
%token STOP_TOKEN 
%token SUCC_TOKEN
%token THEN_TOKEN 
%token TO_TOKEN 
%token TYPE_TOKEN 
%token UNTIL_TOKEN 
%token VAR_TOKEN 
%token WHILE_TOKEN 
%token WRITE_TOKEN

%token ASSIGNMENT_TOKEN 

%token COLON_TOKEN 
%token SEMICOLON_TOKEN 
%token COMMA_TOKEN 
%token DOT_TOKEN 

%token IDENTIFIER_TOKEN

%token INTEGER_TOKEN
%token CHARCONST_TOKEN
%token STRING_TOKEN

%token LEFT_BRACKET_TOKEN 
%token RIGHT_BRACKET_TOKEN

%token LEFT_PARENS_TOKEN 
%token RIGHT_PARENS_TOKEN 

%left OR_TOKEN
%left AND_TOKEN

%right NOT_TOKEN

%nonassoc EQUIVALENCE_TOKEN NOT_EQUAL_TOKEN
%nonassoc LESS_THAN_TOKEN LESS_THAN_OR_EQUAL_TOKEN
%nonassoc GREATER_THAN_TOKEN GREATER_THAN_OR_EQUAL_TOKEN

%left ADDITION_TOKEN SUBTRACTION_TOKEN
%left MULTIPLICATION_TOKEN DIVISION_TOKEN MODULUS_TOKEN

%right UNARY_MINUS_TOKEN

%type <string_type> IDENTIFIER_TOKEN
%type <int_type> INTEGER_TOKEN
%type <char_type> CHARCONST_TOKEN
%type <string_type> STRING_TOKEN

%type <programNode_type> Program
%type <constantDeclVector_type> ConstantDeclsList
%type <constantDeclVector_type> ConstantDecls
%type <constantDeclNode_type> ConstantDecl
%type <typeDeclVector_type> TypeDeclsList
%type <typeDeclVector_type> TypeDecls
%type <typeDeclNode_type> TypeDecl
%type <varDeclVector_type> VarDeclsList
%type <varDeclVector_type> VarDecls
%type <varDeclNode_type> VarDecl
%type <procedureAndFunctionDeclVector_type> ActualProcedureAndFunctionList
%type <procedureAndFunctionDeclVector_type> ProcedureAndFunctionDeclsList
%type <blockNode_type> Block
%type <expressionNode_type> Expression
%type <typeNode_type> Type
%type <simpleTypeNode_type> SimpleType
%type <recordTypeNode_type> RecordType
%type <arrayTypeNode_type> ArrayType
%type <fieldDeclVector_type> FieldDeclsList
%type <fieldDeclVector_type> FieldDecls
%type <fieldDeclNode_type> FieldDecl
%type <stringVector_type> IdentList
%type <procedureAndFunctionDeclNode_type> FirstProcedureOrFunctionDecl
%type <procedureDeclNode_type> ProcedureDecl
%type <functionDeclNode_type> FunctionDecl
%type <bodyNode_type> Body
%type <procedureSignatureNode_type> ProcedureSignature
%type <functionSignatureNode_type> FunctionSignature
%type <formalParameterVector_type> FormalParametersList
%type <formalParameterVector_type> FormalParameters
%type <FormalParametersListTypeNode_type> FormalParameter
%type <statementVector_type> StatementSequence
%type <statementNode_type> Statement
%type <statementNode_type> Assignment
%type <statementNode_type> IfStatement
%type <statementNode_type> WhileStatement
%type <statementNode_type> RepeatStatement
%type <statementNode_type> ForStatement
%type <statementNode_type> StopStatement
%type <statementNode_type> ReturnStatement
%type <statementNode_type> ReadStatement
%type <statementNode_type> WriteStatement
%type <statementNode_type> ProcedureCall
%type <statementNode_type> NullStatement
%type <lValueNode_type> LValue
%type <elseIfClauseVector_type> ActualElseIfList
%type <elseIfClauseVector_type> ElseIfList
%type <elseIfClauseNode_type> ElseIfClause
%type <elseClauseNode_type> ElseClause
%type <lValueVector_type> ReadArguments
%type <expressionVector_type> WriteArguments
%type <expressionVector_type> ProcedureArguments
%type <expressionVector_type> Arguments
%type <functionCallNode_type> FunctionCall

%%

Program : ConstantDeclsList TypeDeclsList VarDeclsList ActualProcedureAndFunctionList Block DOT_TOKEN {pNode = std::make_shared<ASTNamespace::ProgramNode>($1,$2,$3,$4,$5);};

ConstantDeclsList : CONST_TOKEN ConstantDecls {$$ = $2;}
                  |                           {$$ = NULL;};

ConstantDecls : ConstantDecls ConstantDecl {$1->push_back($2); $$ = $1;}
					    | ConstantDecl               {$$ = new std::vector<ASTNamespace::ConstantDeclNode*>(); $$->push_back($1);};

ConstantDecl : IDENTIFIER_TOKEN EQUIVALENCE_TOKEN Expression SEMICOLON_TOKEN {$$ = new ASTNamespace::ConstantDeclNode($1,$3);};

TypeDeclsList : TYPE_TOKEN TypeDecls {$$ = $2;}
              |                      {$$ = NULL;};

TypeDecls    : TypeDecls TypeDecl {$1->push_back($2); $$ = $1;}
             | TypeDecl           {$$ = new std::vector<ASTNamespace::TypeDeclNode*>(); $$->push_back($1);};

TypeDecl : IDENTIFIER_TOKEN EQUIVALENCE_TOKEN Type SEMICOLON_TOKEN {$$ = new ASTNamespace::TypeDeclNode($1,$3);};

Type : SimpleType {$$ = $1;}
     | RecordType {$$ = $1;}
     | ArrayType  {$$ = $1;};

SimpleType : IDENTIFIER_TOKEN {$$ = new ASTNamespace::SimpleTypeNode($1);};

RecordType : RECORD_TOKEN FieldDeclsList END_TOKEN {$$ = new ASTNamespace::RecordTypeNode($2);};

FieldDeclsList : FieldDecls {$$ = $1;}
               |            {$$ = NULL;};

FieldDecls : FieldDecls FieldDecl {$1->push_back($2); $$ = $1;}
           | FieldDecl            {$$ = new std::vector<ASTNamespace::FieldDeclNode*>(); $$->push_back($1);};

FieldDecl : IdentList COLON_TOKEN Type SEMICOLON_TOKEN {$$ = new ASTNamespace::FieldDeclNode($1,$3);};

IdentList : IdentList COMMA_TOKEN IDENTIFIER_TOKEN {$1->push_back($3); $$ = $1;}
          | IDENTIFIER_TOKEN                       {$$ = new std::vector<char*>(); $$->push_back($1);};

ArrayType : ARRAY_TOKEN LEFT_BRACKET_TOKEN Expression COLON_TOKEN Expression RIGHT_BRACKET_TOKEN OF_TOKEN Type {$$ = new ASTNamespace::ArrayTypeNode($3,$5,$8);};

VarDeclsList : VAR_TOKEN VarDecls {$$ = $2;}
             |                    {$$ = NULL;};

VarDecls    : VarDecls VarDecl {$1->push_back($2); $$ = $1;}
            | VarDecl          {$$ = new std::vector<ASTNamespace::VarDeclNode*>(); $$->push_back($1);};

VarDecl : IdentList COLON_TOKEN Type SEMICOLON_TOKEN {$$ = new ASTNamespace::VarDeclNode($1,$3);};

ActualProcedureAndFunctionList : ProcedureAndFunctionDeclsList {$$ = $1;}
                               |                               {$$ = NULL;};

ProcedureAndFunctionDeclsList : ProcedureAndFunctionDeclsList ProcedureDecl {$1->push_back($2); $$ = $1;}
                              | ProcedureAndFunctionDeclsList FunctionDecl  {$1->push_back($2); $$ = $1;}
                              | FirstProcedureOrFunctionDecl                {$$ = new std::vector<ASTNamespace::ProcedureAndFunctionDeclNode*>(); $$->push_back($1);};

FirstProcedureOrFunctionDecl : ProcedureDecl {$$ = $1;}
                             | FunctionDecl  {$$ = $1;};

ProcedureDecl : ProcedureSignature SEMICOLON_TOKEN FORWARD_TOKEN SEMICOLON_TOKEN {$$ = new ASTNamespace::ProcedureDeclNode($1);}
              | ProcedureSignature SEMICOLON_TOKEN Body SEMICOLON_TOKEN          {$$ = new ASTNamespace::ProcedureDeclNode($1,$3);};

ProcedureSignature : PROCEDURE_TOKEN IDENTIFIER_TOKEN LEFT_PARENS_TOKEN FormalParametersList RIGHT_PARENS_TOKEN {$$ = new ASTNamespace::ProcedureSignatureNode($2,$4);};

FunctionDecl : FunctionSignature SEMICOLON_TOKEN FORWARD_TOKEN SEMICOLON_TOKEN {$$ = new ASTNamespace::FunctionDeclNode($1);}
             | FunctionSignature SEMICOLON_TOKEN Body SEMICOLON_TOKEN          {$$ = new ASTNamespace::FunctionDeclNode($1,$3);};

FunctionSignature : FUNCTION_TOKEN IDENTIFIER_TOKEN LEFT_PARENS_TOKEN FormalParametersList RIGHT_PARENS_TOKEN COLON_TOKEN Type {$$ = new ASTNamespace::FunctionSignatureNode($2,$4,$7);};

FormalParametersList : FormalParameters {$$ = $1;}
                     |                  {$$ = NULL;};

FormalParameters : FormalParameters SEMICOLON_TOKEN FormalParameter {$1->push_back($3); $$ = $1;}
                 | FormalParameter                                  {$$ = new std::vector<ASTNamespace::FormalParametersListTypeNode*>(); $$->push_back($1);};

FormalParameter : VAR_TOKEN IdentList COLON_TOKEN Type {$$ = new ASTNamespace::FormalParametersListTypeNode(false,$2,$4);}
                | REF_TOKEN IdentList COLON_TOKEN Type {$$ = new ASTNamespace::FormalParametersListTypeNode(true,$2,$4);}
                | IdentList COLON_TOKEN Type           {$$ = new ASTNamespace::FormalParametersListTypeNode(false,$1,$3);};

Body : ConstantDeclsList TypeDeclsList VarDeclsList Block {$$ = new ASTNamespace::BodyNode($1,$2,$3,$4);};

Block : BEGIN_TOKEN StatementSequence END_TOKEN {$$ = new ASTNamespace::BlockNode($2);};

StatementSequence : StatementSequence SEMICOLON_TOKEN Statement {$1->push_back($3); $$ = $1;}
                  | Statement                                   {$$ = new std::vector<ASTNamespace::StatementNode*>(); $$->push_back($1);};

Statement : Assignment      {$$ = $1;}
          | IfStatement     {$$ = $1;}
          | WhileStatement  {$$ = $1;}
          | RepeatStatement {$$ = $1;}
          | ForStatement    {$$ = $1;}
          | StopStatement   {$$ = $1;}
          | ReturnStatement {$$ = $1;}
          | ReadStatement   {$$ = $1;}
          | WriteStatement  {$$ = $1;}
          | ProcedureCall   {$$ = $1;}
          | NullStatement   {$$ = $1;};

Assignment : LValue ASSIGNMENT_TOKEN Expression {$$ = new ASTNamespace::AssignmentNode($1,$3);};

IfStatement : IF_TOKEN Expression THEN_TOKEN StatementSequence ActualElseIfList ElseClause END_TOKEN {$$ = new ASTNamespace::IfStatementNode($2,$4,$5,$6);};

ActualElseIfList : ElseIfList {$$ = $1;}
                 |            {$$ = NULL;};

ElseIfList : ElseIfList ElseIfClause {$1->push_back($2); $$ = $1;}
           | ElseIfClause            {$$ = new std::vector<ASTNamespace::ElseIfClauseNode*>(); $$->push_back($1);};

ElseIfClause : ELSEIF_TOKEN Expression THEN_TOKEN StatementSequence {$$ = new ASTNamespace::ElseIfClauseNode($2,$4);};

ElseClause : ELSE_TOKEN StatementSequence {$$ = new ASTNamespace::ElseClauseNode($2);}
           |                              {$$ = NULL;};

WhileStatement : WHILE_TOKEN Expression DO_TOKEN StatementSequence END_TOKEN {$$ = new ASTNamespace::WhileStatementNode($2,$4);};

RepeatStatement : REPEAT_TOKEN StatementSequence UNTIL_TOKEN Expression {$$ = new ASTNamespace::RepeatStatementNode($2,$4);};

ForStatement : FOR_TOKEN StatementSequence TO_TOKEN Expression DO_TOKEN StatementSequence END_TOKEN     {$$ = new ASTNamespace::ForStatementNode(true,$2,$4,$6);}
             | FOR_TOKEN StatementSequence DOWNTO_TOKEN Expression DO_TOKEN StatementSequence END_TOKEN {$$ = new ASTNamespace::ForStatementNode(false,$2,$4,$6);};

StopStatement : STOP_TOKEN {$$ = new ASTNamespace::StopStatementNode();};

ReturnStatement : RETURN_TOKEN Expression {$$ = new ASTNamespace::ReturnStatementNode($2);}
                | RETURN_TOKEN            {$$ = new ASTNamespace::ReturnStatementNode();};

ReadStatement : READ_TOKEN LEFT_PARENS_TOKEN ReadArguments RIGHT_PARENS_TOKEN {$$ = new ASTNamespace::ReadStatementNode($3);};

ReadArguments : ReadArguments COMMA_TOKEN LValue {$1->push_back($3); $$ = $1;}
              | LValue                           {$$ = new std::vector<ASTNamespace::LValueNode*>(); $$->push_back($1);};

WriteStatement : WRITE_TOKEN LEFT_PARENS_TOKEN WriteArguments RIGHT_PARENS_TOKEN {$$ = new ASTNamespace::WriteStatementNode($3);};

WriteArguments : WriteArguments COMMA_TOKEN Expression {$1->push_back($3); $$ = $1;}
               | Expression                            {$$ = new std::vector<ASTNamespace::ExpressionNode*>(); $$->push_back($1);};

ProcedureCall : IDENTIFIER_TOKEN LEFT_PARENS_TOKEN ProcedureArguments RIGHT_PARENS_TOKEN {$$ = new ASTNamespace::ProcedureCallNode($1,$3);};

ProcedureArguments : Arguments {$$ = $1;}
                   |           {$$ = NULL;};

Arguments : Arguments COMMA_TOKEN Expression {$1->push_back($3); $$ = $1;}
          | Expression                       {$$ = new std::vector<ASTNamespace::ExpressionNode*>(); $$->push_back($1);};

NullStatement : {$$ = NULL;};

Expression : Expression OR_TOKEN Expression                             {$$ = new ASTNamespace::OrExpressionNode($1,$3);}
           | Expression AND_TOKEN Expression                            {$$ = new ASTNamespace::AndExpressionNode($1,$3);}
           | Expression EQUIVALENCE_TOKEN Expression                    {$$ = new ASTNamespace::EquivalenceExpressionNode($1,$3);}
           | Expression NOT_EQUAL_TOKEN Expression                      {$$ = new ASTNamespace::NotEqualExpressionNode($1,$3);}
           | Expression LESS_THAN_OR_EQUAL_TOKEN Expression             {$$ = new ASTNamespace::LessThanOrEqualExpressionNode($1,$3);}
           | Expression GREATER_THAN_OR_EQUAL_TOKEN Expression          {$$ = new ASTNamespace::GreaterThanOrEqualExpressionNode($1,$3);}
           | Expression LESS_THAN_TOKEN Expression                      {$$ = new ASTNamespace::LessThanExpressionNode($1,$3);}
           | Expression GREATER_THAN_TOKEN Expression                   {$$ = new ASTNamespace::GreaterThanExpressionNode($1,$3);}
           | Expression ADDITION_TOKEN Expression                       {$$ = new ASTNamespace::AdditionExpressionNode($1,$3);}
           | Expression SUBTRACTION_TOKEN Expression                    {$$ = new ASTNamespace::SubtractionExpressionNode($1,$3);}
           | Expression MULTIPLICATION_TOKEN Expression                 {$$ = new ASTNamespace::MultiplicationExpressionNode($1,$3);}
           | Expression DIVISION_TOKEN Expression                       {$$ = new ASTNamespace::DivisionExpressionNode($1,$3);}
           | Expression MODULUS_TOKEN Expression                        {$$ = new ASTNamespace::ModulusExpressionNode($1,$3);}
           | NOT_TOKEN Expression                                       {$$ = new ASTNamespace::NotExpressionNode($2);}
           | SUBTRACTION_TOKEN Expression %prec UNARY_MINUS_TOKEN       {$$ = new ASTNamespace::UnaryMinusExpressionNode($2);}
           | LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN            {$$ = new ASTNamespace::ParensExpressionNode($2);}
           | FunctionCall                                               {$$ = new ASTNamespace::FunctionCallExpressionNode($1);}
           | CHR_TOKEN LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN  {$$ = new ASTNamespace::CHR_ExpressionNode($3);}
           | ORD_TOKEN LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN  {$$ = new ASTNamespace::ORD_ExpressionNode($3);}
           | PRED_TOKEN LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN {$$ = new ASTNamespace::PRED_ExpressionNode($3);}
           | SUCC_TOKEN LEFT_PARENS_TOKEN Expression RIGHT_PARENS_TOKEN {$$ = new ASTNamespace::SUCC_ExpressionNode($3);}
           | LValue                                                     {$$ = new ASTNamespace::LvalExpressionNode($1);}
           | INTEGER_TOKEN                                              {$$ = new ASTNamespace::INTEGERExpressionNode($1);}
           | STRING_TOKEN                                               {$$ = new ASTNamespace::STRINGExpressionNode($1);}
           | CHARCONST_TOKEN                                            {$$ = new ASTNamespace::CHARCONSTExpressionNode($1);};

FunctionCall : IDENTIFIER_TOKEN LEFT_PARENS_TOKEN ProcedureArguments RIGHT_PARENS_TOKEN {$$ = new ASTNamespace::FunctionCallNode($1,$3);};

LValue : LValue DOT_TOKEN IDENTIFIER_TOKEN                        {$$ = new ASTNamespace::LvalDotIdNode($1,$3);}
       | LValue LEFT_BRACKET_TOKEN Expression RIGHT_BRACKET_TOKEN {$$ = new ASTNamespace::LvalBracketedExpressionNode($1,$3);}
       | IDENTIFIER_TOKEN                                         {$$ = new ASTNamespace::LvalIdNode($1);};

%%

void yyerror(const char* msg)
{
  std::cerr << msg << std::endl;
}

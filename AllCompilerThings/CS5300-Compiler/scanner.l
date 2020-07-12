%{
/**
Referenced and used code from https://github.com/ksundberg/CourseMaterials/blob/master/cs5300/examples/calc/scanner.l
and https://github.com/ksundberg/CS6300/blob/master/FrontEnd/scanner.l
for the creation of this file.
*/
#include <cstring>
#include <cstdlib>
#include <iostream>

#include "HeaderFiles/globals.hpp"

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

#include "parser.hpp"

%}

%option noyywrap
%option nounput

%%

array|ARRAY         {return ARRAY_TOKEN;}
begin|BEGIN         {return BEGIN_TOKEN;}
chr|CHR             {return CHR_TOKEN;}
const|CONST         {return CONST_TOKEN;} 
downto|DOWNTO       {return DOWNTO_TOKEN;} 
do|DO               {return DO_TOKEN;} 
else|ELSE           {return ELSE_TOKEN;}
elseif|ELSEIF       {return ELSEIF_TOKEN;}
end|END             {return END_TOKEN;} 
forward|FORWARD     {return FORWARD_TOKEN;} 
for|FOR             {return FOR_TOKEN;} 
function|FUNCTION   {return FUNCTION_TOKEN;} 
if|IF               {return IF_TOKEN;}
of|OF               {return OF_TOKEN;}
ord|ORD             {return ORD_TOKEN;} 
pred|PRED           {return PRED_TOKEN;} 
procedure|PROCEDURE {return PROCEDURE_TOKEN;}
read|READ           {return READ_TOKEN;} 
record|RECORD       {return RECORD_TOKEN;}
ref|REF             {return REF_TOKEN;}
repeat|REPEAT       {return REPEAT_TOKEN;}
return|RETURN       {return RETURN_TOKEN;} 
stop|STOP           {return STOP_TOKEN;}
succ|SUCC           {return SUCC_TOKEN;}
then|THEN           {return THEN_TOKEN;} 
to|TO               {return TO_TOKEN;}
type|TYPE           {return TYPE_TOKEN;}
until|UNTIL         {return UNTIL_TOKEN;}
var|VAR             {return VAR_TOKEN;}
while|WHILE         {return WHILE_TOKEN;}
write|WRITE         {return WRITE_TOKEN;} 

":=" {return ASSIGNMENT_TOKEN;}

":"  {return COLON_TOKEN;}
";"  {return SEMICOLON_TOKEN;} 
","  {return COMMA_TOKEN;}
"."  {return DOT_TOKEN;}

"["  {return LEFT_BRACKET_TOKEN;} 
"]"  {return RIGHT_BRACKET_TOKEN;}

"("  {return LEFT_PARENS_TOKEN;} 
")"  {return RIGHT_PARENS_TOKEN;} 
"*"  {return MULTIPLICATION_TOKEN;} 
"%"  {return MODULUS_TOKEN;}
"/"  {return DIVISION_TOKEN;}
"+"  {return ADDITION_TOKEN;}
"-"  {return SUBTRACTION_TOKEN;} 

"<"  {return LESS_THAN_TOKEN;} 
"<=" {return LESS_THAN_OR_EQUAL_TOKEN;} 
">"  {return GREATER_THAN_TOKEN;}
">=" {return GREATER_THAN_OR_EQUAL_TOKEN;} 
"<>" {return NOT_EQUAL_TOKEN;} 
"="  {return EQUIVALENCE_TOKEN;}

"&"  {return AND_TOKEN;}  
"|"  {return OR_TOKEN;}
"~"  {return NOT_TOKEN;}

[A-Za-z][A-Za-z0-9_]* {yylval.string_type = strdup(yytext); return IDENTIFIER_TOKEN;}

[0][0-7]+          {yylval.int_type = strtol(yytext,nullptr,0);return INTEGER_TOKEN;}
[0][x][0-9a-fA-F]+ {yylval.int_type = strtol(yytext,nullptr,0);return INTEGER_TOKEN;}
[0-9]+[0-9]*       {yylval.int_type = strtol(yytext,nullptr,0);return INTEGER_TOKEN;}

'\\n'               {yylval.char_type = '\n';return CHARCONST_TOKEN;}
'\\r'               {yylval.char_type = '\r';return CHARCONST_TOKEN;}
'\\b'               {yylval.char_type = '\b';return CHARCONST_TOKEN;}
'\\t'               {yylval.char_type = '\t';return CHARCONST_TOKEN;}
'\\f'               {yylval.char_type = '\f';return CHARCONST_TOKEN;}
'\\?.'              {yylval.char_type = yytext[1];return CHARCONST_TOKEN;}

\"[a-zA-Z0-9~`!@'#$%^&*()_+=\-\[\]{}\\\/><,.:;| ]*\" {yylval.string_type = strdup(yytext); return STRING_TOKEN;}

\$.*$ {lineNumber++;}
\n {lineNumber++;}
[ \t]+ {}
. {std::cerr << "Unexpected Token" << " --->" << yytext << "<--- " << std::endl;}
%%

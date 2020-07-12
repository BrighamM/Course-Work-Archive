%%

array|ARRAY {return ARRAY_TOKEN}
else|ELSE {return ELSE_TOKEN}
if|IF {return IF_TOKEN}
record|RECORD {return RECORD_TOKEN}
to|TO {return TO_TOKEN}
begin|BEGIN {return BEGIN_TOKEN}
elseif|ELSEIF {return ELSEIF_TOKEN}
of|OF {return OF_TOKEN}
repeat|REPEAT {return REPEAT_TOKEN}
type|TYPE {return TYPE_TOKEN}
chr|CHR {return CHR_TOKEN}
end|END {return END_TOKEN}
ord|ORD {return ORD_TOKEN}
return|RETURN {return RETURN_TOKEN}
until|UNTIL {return UNTIL_TOKEN}
const|CONST {return CONST_TOKEN}
for|FOR {return FOR_TOKEN}
pred|PRED {return PRED_TOKEN}
stop|STOP {return STOP_TOKEN}
var|VAR {return VAR_TOKEN}
do|DO {return DO_TOKEN}
forward|FORWARD {return FORWARD_TOKEN}
procedure|PROCEDURE {return PROCEDURE_TOKEN}
succ|SUCC {return SUCC_TOKEN}
while|WHILE {return WHILE_TOKEN}
downto|DOWNTO {return DOWNTO_TOKEN}
function|FUNCTION {return FUNCTION_TOKEN}
read|READ {return READ_TOKEN}
then|THEN {return THEN_TOKEN}
write|WRITE {return WRITE_TOKEN}
ref|REF {return REF_TOKEN}





[A-Za-z][A-Za-z0-9_]* {yylval.stuff = ;yytext return ID_TOKEN}

'+' {return PLUS_TOKEN}
'<>' {return NOTEQUAL_TOKEN}
';' {return SEMICOLON_TOKEN}
'-' {return MINUS_TOKEN}
'<' {return LT_TOKEN}
'(' {return LPARENS_TOKEN}
'*' {return MULTIPLICATION_TOKEN}
'<=' {return LTE_TOKEN}
')' {return RPARENS_TOKEN}
'/' {return DIVISION_TOKEN}
'>' {return GT_TOKEN}
'[' {return LBRACKET_TOKEN}
'&' {return AMPERSAND_TOKEN}
'>=' {return GTE_TOKEN}
']' {return RBRACKET_TOKEN}
'|' {return OR_TOKEN}
'.' {return DOT_TOKEN}
':=' {return ASSIGNMENT_TOKEN}
'~' {return NOT_TOKEN}
',' {return COMMA_TOKEN}
'%' {return MOD_TOKEN}
'=' {return EQUIVALENCE_TOKEN}
':' {return COLON_TOKEN}

%%
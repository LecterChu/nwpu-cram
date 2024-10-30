/*
 * Lexer rules
 */
lexer grammar MIDL_Lexer;

fragment LETTER : [a-z] | [A-Z] ; // 使用fragment，不会单独作为词法符号匹配

fragment DIGIT : [0-9] ;

fragment UNDERLINE : '_' ;

fragment INTEGER_TYPE_SUFFIX : 'l' | 'L' ;

fragment EXPONENT : ( 'e' | 'E' ) ( '+' | '-' )? [0-9]+ ;

fragment FLOAT_TYPE_SUFFIX :  'f' | 'F' | 'd' | 'D' ;

fragment ESCAPE_SEQUENCE :  '\\' ( 'b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\' ) ;

INTEGER : ('0' | [1-9] [0-9]*) INTEGER_TYPE_SUFFIX? ;

FLOATING_PT : [0-9]+ '.'[0-9]*  EXPONENT?  FLOAT_TYPE_SUFFIX?
   				|  '.'[0-9]+  EXPONENT?  FLOAT_TYPE_SUFFIX?
   				|  [0-9]+  EXPONENT  FLOAT_TYPE_SUFFIX?
   				|  [0-9]+  EXPONENT?  FLOAT_TYPE_SUFFIX ;

WS : [ \t\r\n]+ -> skip ; // 跳过空格、制表符、回车符和换行符

CHAR : '\''(ESCAPE_SEQUENCE |  (~'\\' | ~'\'') )'\'' ;

STRING : '"' (ESCAPE_SEQUENCE |  (~'\\' | ~'"') )* '"' ;

BOOLEAN : 'TRUE' | 'true' | 'FALSE' | 'false' ;

ID :  LETTER ( UNDERLINE ? ( LETTER | DIGIT ))* ; // ?代表重复零次或一次
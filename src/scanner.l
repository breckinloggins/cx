%{
#include <stdio.h>
#include "base.h"
#include "parser.tab.h"

#define uploc	{ yylloc->first_column = yylloc->last_column + 1; yylloc->last_column += yyleng; }

#define CAST_BOOLEAN(strb)	strcasecmp(strb, "False")? TRUE : FALSE
%}

%option yylineno
%option bison-bridge
%option bison-locations
%option noyywrap

%%
"/*"							{
								int c;
								while ((c = input()))	{
									if (c == '*')	{
										if ((c = input()) == '/')
											break;
										else unput(c);
									}
									else if (c == '\n')	{
										yylloc->first_line = yylloc->last_line = yylineno;
										yylloc->first_column = 1;
										yylloc->last_column = 0;
									} else if (c == EOF)	{
										fprintf(stderr, "Error: Unexpected end of input inside comment "
											"at line %d\n", yylineno);
										exit(1);
									}
								}
							}
"//"						{
								int c;
								while ((c = input()))	{
									if (c == '\n')
										break;
								}
							}
"namespace"					{ uploc; return T_NAMESPACE; }	
"var"						{ uploc; return T_VAR; }
"integer"|"boolean"|"char"|"double"|"float"			{ uploc;
							  						yylval->type = type_get_from_lexeme(yytext); 
							  						return TYPE_IDENTIFIER; 
													}

"return"					{ uploc; return T_RETURN; }

"printInt"					{ uploc; return T_PRINT_INT; }
"printBool"					{ uploc; return T_PRINT_BOOL; }
"printChar"					{ uploc; return T_PRINT_CHAR; }
"printLn"					{ uploc; return T_PRINT_LINE; }

"if"						{ uploc; return T_IF; }
"else"						{ uploc; return T_ELSE; }
"while"						{ uploc; return T_WHILE; }
"for"						{ uploc; return T_FOR; }
"to"						{ uploc; return T_TO; }
"do"						{ uploc; return T_DO; }

"="							{ uploc; return T_ASSIGNMENT; }
"("							{ uploc; return T_LPAR; }
")"							{ uploc; return T_RPAR; }
"{"							{ uploc; return T_LBRACK; }
"}"							{ uploc; return T_RBRACK; }
"+"							{ uploc; yylval->lexeme=strdup(yytext); return T_PLUS; }
"-"							{ uploc; yylval->lexeme=strdup(yytext); return T_MINUS; }
"*"							{ uploc; yylval->lexeme=strdup(yytext); return T_STAR; }
"/"							{ uploc; yylval->lexeme=strdup(yytext); return T_SLASH; }
"&&"						{ uploc; yylval->lexeme=strdup(yytext); return T_AND; }
"||"						{ uploc; yylval->lexeme=strdup(yytext); return T_OR; }
"!"							{ uploc; yylval->lexeme=strdup(yytext); return T_NOT; }
">"							{ uploc; yylval->lexeme=strdup(yytext); return T_GREATER; }
"<"							{ uploc; yylval->lexeme=strdup(yytext); return T_LESSER; }
"=="						{ uploc; yylval->lexeme=strdup(yytext);	return T_EQUAL; }
"!="						{ uploc; yylval->lexeme=strdup(yytext);	return T_NOTEQUAL; }
">="						{ uploc; yylval->lexeme=strdup(yytext); return T_GREATEREQUAL; }
"<="						{ uploc; yylval->lexeme=strdup(yytext); return T_LESSEREQUAL; }

";"							{ uploc; return T_SEMICOLON; }
":"							{ uploc; return T_COLON; }
"."							{ uploc; return T_DOT; }
","							{ uploc; return T_COMMA; }

"true"|"false"				{uploc; yylval->boolean=CAST_BOOLEAN(yytext); return BOOL_LITERAL; }
"'"\\n"'"					{uploc; yylval->character='\n'; return CHAR_LITERAL; }
"'"."'"						{uploc; yylval->character=yytext[1]; return CHAR_LITERAL; }
[0-9]+						{uploc; yylval->integer=atoi(yytext); return INT_LITERAL; }
[A-Za-z][A-Za-z0-9_]*		{uploc; yylval->lexeme=strdup(yytext); return IDENTIFIER; }
\-?[0-9]*\.[0-9]+f?			{uploc; yylval->flt=atof(yytext); return FLOAT_LITERAL; }
\-?[0-9]*\.[0-9]+d			{uploc; yylval->dbl=atof(yytext); return DOUBLE_LITERAL; }

[ \t]+						/* ignore whitespace */
[\n]						{ yylloc->first_line = yylloc->last_line = yylineno; 
							  yylloc->first_column = 1;
							  yylloc->last_column = 0;
							}

.							{ uploc;
							  fprintf(stderr, "Syntax Error: unexpected character '%s' at line %d\n", 
								yytext, yylloc->first_line);
							}

%%
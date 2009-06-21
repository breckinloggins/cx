%{
#include <stdio.h>
#include "base.h"
#include "parser.h"

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
"int"|"bool"|"char"|"double"|"float"|"void"			{ uploc;
							  						yylval->type = type_get_from_lexeme(yytext); 
							  						return TYPE_IDENTIFIER; 
													}

"public"					{ uploc; return T_PUBLIC; }
"return"					{ uploc; return T_RETURN; }

"printInt"					{ uploc; return T_PRINT_INT; }
"printBool"					{ uploc; return T_PRINT_BOOL; }
"printChar"					{ uploc; return T_PRINT_CHAR; }
"printLn"					{ uploc; return T_PRINT_LINE; }
"readChar"					{ uploc; return T_READ_CHAR; }

"_C_"[ \t\n]+\{				{ 
								int bracket_count = 1;
								char* content = (char*)malloc(4096*sizeof(char));
								memset(content, 0, 4096*sizeof(char));
								int char_count = 0;
								int in_single_quote = 0;
								int in_double_quote = 0;
								while (1)	{
									char c = input();
									if (c == '\'' && !in_double_quote)	{
										in_single_quote = !in_single_quote;
									}
									
									if (c == '"' && !in_single_quote)	{
										in_double_quote = !in_double_quote;
									}
									
									if (c == '}' && !in_single_quote && !in_double_quote)
										--bracket_count;
									else if (c == '{' && !in_single_quote && !in_double_quote)
										++bracket_count;
										
									if (!bracket_count)
										break;				// Brackets in balance.  Finished
									
									content[char_count++] = c;
									
									if (char_count > 0 && char_count % 4095 == 0)	{
										// Definitely time for more string space
										content = (char*)realloc(content, (char_count+4096)*sizeof(char));
										memset(content+char_count, 0, 4096+sizeof(char));
									}
								}
								
								// The parser will take ownership of the pointer
								yylval->literal_content = content;
								uploc; 
								return T_C_BLOCK; 
							}

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
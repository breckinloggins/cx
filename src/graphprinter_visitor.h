#ifndef GRAPHPRINTER_VISITOR_H
#define GRAPHPRINTER_VISITOR_H

#include "ast/ast.h"

#define COLOR_FILL_GLOBAL  "\"#EEEEEE\""
#define COLOR_FILL_LOCAL   "\"#CAE7FF\""
#define COLOR_FILL_COMMON  "\"#EEFFEE\""
#define COLOR_FILL_LITERAL "\"#FFFFCC\""
#define COLOR_FILL_SYMBOL  "\"#CCFF99\""
#define COLOR_FILL_ERROR   "\"#FFEEEE\""

#define COLOR_EDGE_GROUP   "\"#22DDAA\""
#define COLOR_EDGE_FUNCT   "\"#EEEEFF\""
#define COLOR_EDGE_ERROR   "\"#FF0000\""

Visitor *graphprinter_new(FILE*);

void graphprinter_visit_TranslationUnit (Visitor *, AstNode *);
void graphprinter_visit_NamespaceDecl (Visitor *, AstNode *);
void graphprinter_visit_vardecl_list (Visitor *, AstNode *);
void graphprinter_visit_function_list (Visitor *, AstNode *);
void graphprinter_visit_function (Visitor *, AstNode *);
void graphprinter_visit_param_list (Visitor *, AstNode *);
void graphprinter_visit_parameter (Visitor *, AstNode *);
void graphprinter_visit_statement_list (Visitor *, AstNode *);
void graphprinter_visit_binary_expr (Visitor *, AstNode *);
void graphprinter_visit_call (Visitor *, AstNode *);
void graphprinter_visit_callparam_list (Visitor *, AstNode *);
void graphprinter_visit_callparam (Visitor *, AstNode *);
void graphprinter_visit_identifier (Visitor *, AstNode *);
void graphprinter_visit_literal (Visitor *, AstNode *);

void graphprinter_visit_simplenode (Visitor *, AstNode *);

#endif // GRAPHPRINTER_VISITOR_H

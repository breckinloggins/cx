#ifndef CONTEXT_VISITOR_H
#define CONTEXT_VISITOR_H

/*
 *  AST Visitor that performs contextual analysis like type checking
 */

#include "ast.h"
#include "base.h"
#include "identifier_table.h"

#define	CTX_VISITOR(kind)		void context_visit_##kind(Visitor* visitor, AstNode* node)

Visitor* context_new();
void context_cleanup();

CTX_VISITOR(TranslationUnit);
CTX_VISITOR(NamespaceDecl);
CTX_VISITOR(NamespaceDecl_list);
CTX_VISITOR(function);
CTX_VISITOR(vardecl);
CTX_VISITOR(param_list);
CTX_VISITOR(parameter);
CTX_VISITOR(statement_list);
CTX_VISITOR(printint_stmt);
CTX_VISITOR(printchar_stmt);
CTX_VISITOR(printbool_stmt);
CTX_VISITOR(readchar_expr);
CTX_VISITOR(cblock_stmt);
CTX_VISITOR(return_stmt);
CTX_VISITOR(assignment_stmt);
CTX_VISITOR(if_stmt);
CTX_VISITOR(while_stmt);
CTX_VISITOR(for_stmt);
CTX_VISITOR(binary_expr);
CTX_VISITOR(notfactor);
CTX_VISITOR(call);
CTX_VISITOR(callparam_list);
CTX_VISITOR(callparam);
CTX_VISITOR(identifier);

#endif	// CONTEXT_VISITOR_H
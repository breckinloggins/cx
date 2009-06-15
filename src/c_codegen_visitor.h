#ifndef C_CODEGEN_VISITOR_H
#define C_CODEGEN_VISITOR_H

#include "ast/ast.h"

#define TAB			"    "
#define	C_VISITOR(kind)		void c_codegen_visit_##kind(Visitor* visitor, AstNode* node)

Visitor* c_codegen_new(FILE*);

C_VISITOR(program);
C_VISITOR(programdecl);
C_VISITOR(procfunc_list);
C_VISITOR(procfunc);
C_VISITOR(vardecl_list);
C_VISITOR(vardecl);
C_VISITOR(identifier_list);
C_VISITOR(param_list);
C_VISITOR(parameter);
C_VISITOR(statement_list);
C_VISITOR(printint_stmt);
C_VISITOR(printchar_stmt);
C_VISITOR(printbool_stmt);
C_VISITOR(printline_stmt);
C_VISITOR(assignment_stmt);
C_VISITOR(if_stmt);
C_VISITOR(while_stmt);
C_VISITOR(for_stmt);
C_VISITOR(binary_expr);
C_VISITOR(notfactor);
C_VISITOR(call);
C_VISITOR(callparam_list);
C_VISITOR(identifier);
C_VISITOR(literal);
C_VISITOR(binary_op);
C_VISITOR(not_op);

#endif	// C_CODEGEN_VISITOR_H
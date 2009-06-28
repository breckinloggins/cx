#ifndef CODENODE_HELPER_H
#define CODENODE_HELPER_H

#include "ast.h"

AstNode* function_get_identifier(AstNode* function);
AstNode* function_get_params(AstNode* function);
AstNode* function_get_statements(AstNode* function);

int paramlist_get_count(AstNode* params);

int callparamlist_get_count(AstNode* callparams);

#endif // CODENODE_HELPER_H
#ifndef CGEN_H
#define CGEN_H

/*
 * Functions for generating target code based on a Cx AST
 */

#include <stdio.h>
#include "../ast/ast.h"

void cgen_transunit(FILE* f, transunit_node* t);
void cgen_namespace(FILE* f, namespace_node* ns);
void cgen_function(FILE* f, function_node* fn);

#endif
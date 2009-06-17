#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common/memory.h"
#include "graphprinter_visitor.h"

static void _print_arrow(AstNode *node);
static void _print_symbol_table(AstNode *node);
static void _print_symbols(Symbol *symbol);

static FILE* out;

Visitor *
graphprinter_new(FILE* output)
{
	out = output;
	
    Visitor *visitor = (Visitor *) malloc (sizeof(Visitor));

    visitor->visit_TranslationUnit = &graphprinter_visit_TranslationUnit;
    visitor->visit_NamespaceDecl = &graphprinter_visit_NamespaceDecl;
    visitor->visit_vardecl_list = &graphprinter_visit_vardecl_list;
    visitor->visit_vardecl = &graphprinter_visit_simplenode;
    visitor->visit_identifier_list = &graphprinter_visit_identifier_list;
    visitor->visit_function_list = &graphprinter_visit_function_list;
    visitor->visit_function = &graphprinter_visit_function;
    visitor->visit_param_list = &graphprinter_visit_param_list;
    visitor->visit_parameter = &graphprinter_visit_parameter;
    visitor->visit_statement_list = &graphprinter_visit_statement_list;
    visitor->visit_printint_stmt = &graphprinter_visit_simplenode;
    visitor->visit_printchar_stmt = &graphprinter_visit_simplenode;
    visitor->visit_printbool_stmt = &graphprinter_visit_simplenode;
    visitor->visit_printline_stmt = &graphprinter_visit_simplenode;
    visitor->visit_assignment_stmt = &graphprinter_visit_simplenode;
    visitor->visit_if_stmt = &graphprinter_visit_simplenode;
    visitor->visit_while_stmt = &graphprinter_visit_simplenode;
    visitor->visit_for_stmt = &graphprinter_visit_simplenode;
    visitor->visit_rel_expr = &graphprinter_visit_binary_expr;
    visitor->visit_add_expr = &graphprinter_visit_binary_expr;
    visitor->visit_mul_expr = &graphprinter_visit_binary_expr;
    visitor->visit_notfactor = &graphprinter_visit_simplenode;
    visitor->visit_call = &graphprinter_visit_call;
    visitor->visit_callparam_list = &graphprinter_visit_callparam_list;
    visitor->visit_callparam = &graphprinter_visit_callparam;
    visitor->visit_identifier = &graphprinter_visit_identifier;
    visitor->visit_literal = &graphprinter_visit_literal;
    visitor->visit_add_op = NULL;
    visitor->visit_mul_op = NULL;
    visitor->visit_rel_op = NULL;
    visitor->visit_not_op = NULL;

    return visitor;
}

void
graphprinter_visit_TranslationUnit(Visitor *visitor, AstNode *node)
{
    fprintf(out,"/* Cx AST graph. */\n");
    fprintf(out,"digraph {\n");

    fprintf(out,"\tremincross=true;\n");
    fprintf(out,"\tordering=out;\n");
    fprintf(out,"\tcompound=true;\n");
    fprintf(out,"\tranksep=1.0;\n");
    fprintf(out,"\tnode [fontsize=11,fontname=Courier];\n");
    fprintf(out,"\tedge [color="COLOR_EDGE_GROUP"];\n\n");

    fprintf(out,"\tnode_%x [label=\"%s\",fontsize=16,fontname=Courier,",
           node, node->name);
    fprintf(out,"style=filled,color=black,fillcolor="COLOR_FILL_GLOBAL"];\n");

    _print_symbol_table(node);

    ast_node_accept_children(node->children, visitor);

    fprintf(out,"}\n");
}

void
graphprinter_visit_simplenode (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\\n[line: %d]\",style=filled,",
           node, node->name, node->linenum);
    fprintf(out,"fillcolor="COLOR_FILL_COMMON",color=%s];\n",
           (node->type == ERROR) ? COLOR_EDGE_ERROR : COLOR_FILL_COMMON);
    ast_node_accept_children(node->children, visitor);
}

void
graphprinter_visit_NamespaceDecl(Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\\n[line: %d]\",style=filled,",
           node, node->name, node->linenum);
    fprintf(out,"color="COLOR_EDGE_GROUP",fillcolor="COLOR_FILL_COMMON"];\n");
    ast_node_accept(node->children, visitor);
    fprintf(out,"\tnode_%x -> symbol_%x [color=lightgray];\n", node->children, node->children->symbol);

	ast_node_accept_children(node->children->sibling, visitor);
}

void
graphprinter_visit_vardecl_list (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\",style=filled,", node, node->name);
    fprintf(out,"color="COLOR_EDGE_GROUP",fillcolor="COLOR_FILL_COMMON"];\n");
    fprintf(out,"\nsubgraph cluster_%x {\n\tstyle=dotted;\n", node);
    ast_node_accept_children(node->children, visitor);
    fprintf(out,"}\n\n");
}

void
graphprinter_visit_identifier_list (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\",style=filled,", node, node->name);
    fprintf(out,"color="COLOR_EDGE_GROUP",fillcolor="COLOR_FILL_COMMON"];\n");
    fprintf(out,"\nsubgraph cluster_%x {\n\tstyle=dotted;\n", node);
    ast_node_accept_children(node->children, visitor);
    fprintf(out,"}\n\n");
}

void
graphprinter_visit_function_list (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\",style=filled,", node, node->name);
    fprintf(out,"color="COLOR_EDGE_GROUP",fillcolor="COLOR_FILL_COMMON"];\n");
    ast_node_accept_children(node->children, visitor);
}

void
graphprinter_visit_function (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\\n<%s>\\n[line: %d]\",style=filled,",
           node, node->name, type_get_lexeme(node->type), node->linenum);
    fprintf(out,"color=blue,fillcolor="COLOR_EDGE_FUNCT"];\n");
    fprintf(out,"\nsubgraph cluster_%x {\n\tstyle=dotted;\n", node);

    _print_symbol_table(node);
    ast_node_accept_children(node->children, visitor);
    fprintf(out,"}\n\n");
}

void
graphprinter_visit_param_list (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\",style=filled,", node, node->name);
    fprintf(out,"color="COLOR_EDGE_GROUP",fillcolor="COLOR_FILL_COMMON"];\n");
    fprintf(out,"\nsubgraph cluster_%x {\n\tstyle=dotted;\n", node);
    ast_node_accept_children(node->children, visitor);
    fprintf(out,"}\n\n");
}

void
graphprinter_visit_parameter (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\",style=filled,", node, node->name);
    fprintf(out,"fillcolor="COLOR_FILL_COMMON",color=%s];\n",
           (node->type == ERROR) ? COLOR_EDGE_ERROR : COLOR_FILL_COMMON);
    ast_node_accept_children(node->children, visitor);
}

void
graphprinter_visit_statement_list (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\",style=filled,", node, node->name);
    fprintf(out,"color="COLOR_EDGE_GROUP",fillcolor="COLOR_FILL_COMMON"];\n");
    fprintf(out,"\nsubgraph cluster_%x {\n\tstyle=dotted;\n", node);
    ast_node_accept_children(node->children, visitor);
    fprintf(out,"}\n\n");
}

void
graphprinter_visit_binary_expr (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\\n'%s'\",style=filled,",
           node, node->name, node->children->sibling->name);
    fprintf(out,"fillcolor="COLOR_FILL_COMMON",color=%s];\n",
           (node->type == ERROR) ? COLOR_EDGE_ERROR : COLOR_FILL_COMMON);
    ast_node_accept_children(node->children, visitor);
}

void
graphprinter_visit_call (Visitor *visitor, AstNode *node)
{
    AstNode *ident = node->children;
    AstNode *plist = ident->sibling;

    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\\n[line: %d]\",style=filled,",
           node, node->name, node->linenum);
    fprintf(out,"fillcolor="COLOR_FILL_COMMON",color=%s];\n",
           (node->type == ERROR) ? COLOR_EDGE_ERROR : COLOR_FILL_COMMON);
    fprintf(out,"\nsubgraph cluster_%x {\n\tstyle=dotted;\n", node);
    ast_node_accept(ident, visitor);
    ast_node_accept(plist, visitor);
    fprintf(out,"}\n\n");
}

void
graphprinter_visit_callparam_list (Visitor *visitor, AstNode *node)
{
    int i;

    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\\n<", node, node->name);

    for (i = 0; i < node->symbol->params; i++) {
        fprintf(out,"%s", type_get_lexeme(node->symbol->param_types[i]));
        if (i + 1 < node->symbol->params)
            fprintf(out,", ");
    }


    fprintf(out,">\",style=filled,fillcolor="COLOR_FILL_COMMON",color=%s];\n",
           (node->type == ERROR) ? COLOR_EDGE_ERROR : COLOR_EDGE_GROUP);

    ast_node_accept_children(node->children, visitor);
}

void
graphprinter_visit_callparam (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);
    fprintf(out,"\tnode_%x [label=\"%s\\n<%s>\",style=filled,",
           node, node->name, type_get_lexeme(node->type));
    fprintf(out,"fillcolor="COLOR_FILL_COMMON",color=%s];\n",
           (node->type == ERROR) ? COLOR_EDGE_ERROR : COLOR_FILL_COMMON);
    ast_node_accept_children(node->children, visitor);
}

void
graphprinter_visit_identifier (Visitor *visitor, AstNode *node)
{
    _print_arrow(node);

    fprintf(out,"\tnode_%x [label=\"", node);

    if (node->symbol->decl_linenum == 0)
        fprintf(out,"UNDECLARED\\n");

    fprintf(out,"%s\\n'%s'\\n<%s>\",style=filled,color=",
           node->name, node->symbol->name, type_get_lexeme(node->type));

    if (node->symbol->decl_linenum == 0)
        fprintf(out,COLOR_EDGE_ERROR);
    else if (node->symbol->is_global)
        fprintf(out,COLOR_FILL_GLOBAL);
    else
        fprintf(out,COLOR_FILL_LOCAL);

    fprintf(out,",fillcolor=");

    if (node->symbol->is_global)
        fprintf(out,COLOR_FILL_GLOBAL);
    else
        fprintf(out,COLOR_FILL_LOCAL);

    fprintf(out,"];\n");
}

void
graphprinter_visit_literal (Visitor *visitor, AstNode *node)
{
    fprintf(out,"\tnode_%x -> literal_%x;\n", node->parent, node);
    fprintf(out,"\tliteral_%x [label=\"", node);
    value_print(stdout, &node->value, node->type);
    fprintf(out,"\\n<%s>\",style=filled,color="COLOR_FILL_LITERAL"];\n",
           node->name, type_get_lexeme(node->type));
    ast_node_accept_children(node->children, visitor);
}

// Helper functions ----------------------------------------------------------

static void
_print_arrow(AstNode *node)
{
    fprintf(out,"\tnode_%x -> node_%x [label=\"%d\",",
           node->parent, node, ast_node_get_child_counter(node->parent));
    fprintf(out,"fontsize=11,fontname=Courier];\n");
}

static void
_print_symbol_table(AstNode *node)
{
	if (node->symbol == NULL || node->symbol->next == NULL)
        return;

    fprintf(out,"\tnode_%x -> symbol_%x [lhead=cluster_symtab_%x,color=",
           node, node->symbol->next, node);
    if (node->parent == NULL)
        fprintf(out,"black];\n");
    else
        fprintf(out,"blue];\n");

    fprintf(out,"\n\tsubgraph cluster_symtab_%x {\n", node);

    if (node->parent == NULL)
        fprintf(out,"\t\tcolor=black;\n");
    else
        fprintf(out,"\t\tcolor=blue;\n");

    fprintf(out,"\t\tstyle=filled;\n\t\tfillcolor="COLOR_FILL_GLOBAL";\n\t\tfontname=Courier;\n");
    fprintf(out,"\t\tnode [style=filled,color=white,fillcolor="COLOR_FILL_SYMBOL"];\n");

    _print_symbols(node->symbol->next);

    fprintf(out,"\t}\n\n");
}

static void
_print_symbols(Symbol *symbol)
{
    if (symbol == NULL)
        return;

    if (symbol->name != NULL) {
        fprintf(out,"\t\tsymbol_%x [shape=record,label=\"{", symbol);
        fprintf(out,"Symbol|Address: 0x%x\\l|lexeme: %s\\l|", symbol, symbol->name);
        fprintf(out,"type: %s\\l}\"", type_get_lexeme(symbol->type));
        fprintf(out,",style=filled,color=white,fillcolor="COLOR_FILL_SYMBOL"];\n");

        if (symbol->next != NULL)
            fprintf(out,"\tsymbol_%x -> symbol_%x;\n", symbol, symbol->next);

    }

    _print_symbols(symbol->next);
}

//
// Created by Yichen Xu on 2020/8/17.
//

#include "ulib.h"
#include "ast.h"

ast_val_t *ast_singleton(ast_val_type_t t) {
    ast_val_t *node = kmalloc(sizeof(ast_val_t));
    node->type = t;

    return node;
}

ast_val_t *ast_int(int val) {
    ast_val_t *node = kmalloc(sizeof(ast_val_t));
    node->type = VAL_INT;
    node->int_val = val;

    return node;
}

ast_val_t *ast_str(char *str) {
    ast_val_t *node = kmalloc(sizeof(ast_val_t));
    long len = strlen(str);

    node->type = VAL_STR;
    node->str_val = strdup(str);
    node->str_val[len] = '\0';

    return node;
}

ast_val_t *ast_bool(int val) {
    ast_val_t *node = kmalloc(sizeof(ast_val_t));
    node->type = VAL_BOOL;
    node->int_val = val;

    return node;
}

ast_val_t *ast_symb(char *str) {
    ast_val_t *node = kmalloc(sizeof(ast_val_t));
    long len = strlen(str);

    node->type = VAL_SYMB;
    node->str_val = strdup(str);
    node->str_val[len] = '\0';

    return node;
}

ast_val_t *ast_list(ast_val_t **list, int list_len) {
    ast_val_t *node = kmalloc(sizeof(ast_val_t));
    int len = list_len * sizeof(node);
    node->list_val = kmalloc(len);
    node->int_val = list_len;
    memcpy(node->list_val, list, len);
    node->type = VAL_LIST;

    return node;
}

ast_val_t *ast_func(char *name, char **arg_list, int arg_num, ast_val_t **body, int expr_num, void *env) {
    int psize = sizeof(void *);
    ast_val_t *node = kmalloc(sizeof(ast_val_t));
    node->type = VAL_FUNC;
    // func name
    node->str_val = strdup(name);
    // arg list
    node->func_args = kmalloc(arg_num * psize);
    for (int i = 0; i < arg_num; i++) {
        node->func_args[i] = strdup(arg_list[i]);
    }
    node->arg_num = arg_num;
    // func body
    node->list_val = kmalloc(expr_num * psize);
    memcpy(node->list_val, body, expr_num * psize);
    node->int_val = expr_num;
    // func lexical scope
    node->func_def_scope = env;

    return node;
}

void print_ast(ast_val_t *ast) {
    if (!ast) return; // sanity check
    if (ast->type == VAL_INT) {
        kprintf("%d", ast->int_val);
    }
    if (ast->type == VAL_BOOL) {
        kprintf("%s", ast->int_val ? "#t" : "#f");
    }
    if (ast->type == VAL_STR) {
        kprintf("%s", ast->str_val);
    }
    if (ast->type == VAL_SYMB) {
        kprintf("%s", ast->str_val);
    }
    if (ast->type == VAL_FUNC) {
        kprintf("<func %s>", ast->str_val);
    }
    if (ast->type == VAL_PLUS) {
        kprintf("+");
    }
    if (ast->type == VAL_MINUS) {
        kprintf("-");
    }
    if (ast->type == VAL_MULT) {
        kprintf("*");
    }
    if (ast->type == VAL_LT) {
        kprintf("<");
    }
    if (ast->type == VAL_LE) {
        kprintf("<=");
    }
    if (ast->type == VAL_GT) {
        kprintf(">");
    }
    if (ast->type == VAL_GE) {
        kprintf(">=");
    }
    if (ast->type == VAL_EQ) {
        kprintf("==");
    }
    if (ast->type == VAL_NEQ) {
        kprintf("!=");
    }
    if (ast->type == VAL_IF) {
        kprintf("if");
    }
    if (ast->type == VAL_DO) {
        kprintf("do");
    }
    if (ast->type == VAL_DEF) {
        kprintf("def");
    }
    if (ast->type == VAL_DEFUN) {
        kprintf("defun");
    }
    if (ast->type == VAL_QUOTE) {
        kprintf("quote");
    }
    if (ast->type == VAL_LIST) {
        kputchar('(');
        for (int i = 0; i < ast->int_val; i++) {
            if (i) kputchar(' ');
            print_ast(ast->list_val[i]);
        }
        kputchar(')');
    }
}


//
// Created by Yichen Xu on 2020/8/17.
//

#ifndef EASTER_LISP_AST_H
#define EASTER_LISP_AST_H

typedef enum {
    VAL_INT,
    VAL_STR,
    VAL_BOOL,
    VAL_SYMB,
    VAL_FUNC,
    VAL_LIST,
    VAL_PLUS, VAL_MINUS, VAL_MULT,
    VAL_LT, VAL_LE, VAL_GT, VAL_GE,
    VAL_EQ, VAL_NEQ,
    VAL_IF, VAL_DO, VAL_DEF, VAL_DEFUN,
    VAL_QUOTE
} ast_val_type_t;

struct ast_val_s {
    ast_val_type_t type;
    int int_val;
    char *str_val;
    struct ast_val_s **list_val;
    char **func_args;
    int arg_num;
    void *func_def_scope;
};
typedef struct ast_val_s ast_val_t;

ast_val_t *ast_singleton(ast_val_type_t t);

ast_val_t *ast_int(int val);

ast_val_t *ast_str(char *str);

ast_val_t *ast_bool(int val);

ast_val_t *ast_symb(char *str);

ast_val_t *ast_list(ast_val_t **list, int list_len);

ast_val_t *ast_func(char *name, char **arg_list, int arg_num, ast_val_t **body, int expr_num, void *env);

void print_ast(ast_val_t *ast);

#endif //EASTER_LISP_AST_H

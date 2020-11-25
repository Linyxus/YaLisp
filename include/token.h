//
// Created by Yichen Xu on 2020/8/17.
//

#ifndef EASTER_LISP_TOKEN_H
#define EASTER_LISP_TOKEN_H

typedef enum {
    LB, RB,
    PLUS, MINUS, MULT,
    GT, LT, GE, LE,
    EQ, NEQ,
    LIT_INT, LIT_STR, LIT_BOOL,
    IF, DO, DEF, DEFUN, SYMBOL,
    QUOTE
} token_type_t;

typedef struct {
    token_type_t type;
    int int_val;
    char *str_val;
} token_t;

void token_fail(char *msg);

void print_token(token_t *token);

token_t *token_singleton(token_type_t t);

token_t *token_int(int val);

token_t *token_str(const char *begin, const char *end);

token_t *token_bool(int val);

token_t *token_symb(const char *begin, const char *end);

token_t *next_token(char **buf, char *end);

#endif //EASTER_LISP_TOKEN_H

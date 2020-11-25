//
// Created by Yichen Xu on 2020/8/17.
//

#include "lex.h"
#include "ulib.h"

void lex_fail(char *msg) {
    kprintf("Lex error: %s\n", msg);
    exit(-1);
}

ast_val_t *next_expr(token_t **buf, token_t *end) {
    token_t *p = *buf;
    // end of token stream
    if (p == end) {
        return 0;
    }
    // direct lift token to ast
    if (p->type == LIT_INT) {
        *buf = p + 1;
        return ast_int(p->int_val);
    }
    if (p->type == LIT_BOOL) {
        *buf = p + 1;
        return ast_bool(p->int_val);
    }
    if (p->type == LIT_STR) {
        *buf = p + 1;
        return ast_str(p->str_val);
    }
    if (p->type == PLUS) {
        *buf = p + 1;
        return ast_singleton(VAL_PLUS);
    }
    if (p->type == MINUS) {
        *buf = p + 1;
        return ast_singleton(VAL_MINUS);
    }
    if (p->type == MULT) {
        *buf = p + 1;
        return ast_singleton(VAL_MULT);
    }
    if (p->type == LT) {
        *buf = p + 1;
        return ast_singleton(VAL_LT);
    }
    if (p->type == LE) {
        *buf = p + 1;
        return ast_singleton(VAL_LE);
    }
    if (p->type == GT) {
        *buf = p + 1;
        return ast_singleton(VAL_GT);
    }
    if (p->type == GE) {
        *buf = p + 1;
        return ast_singleton(VAL_GE);
    }
    if (p->type == EQ) {
        *buf = p + 1;
        return ast_singleton(VAL_EQ);
    }
    if (p->type == NEQ) {
        *buf = p + 1;
        return ast_singleton(VAL_NEQ);
    }
    if (p->type == IF) {
        *buf = p + 1;
        return ast_singleton(VAL_IF);
    }
    if (p->type == DO) {
        *buf = p + 1;
        return ast_singleton(VAL_DO);
    }
    if (p->type == DEF) {
        *buf = p + 1;
        return ast_singleton(VAL_DEF);
    }
    if (p->type == DEFUN) {
        *buf = p + 1;
        return ast_singleton(VAL_DEFUN);
    }
    if (p->type == SYMBOL) {
        *buf = p + 1;
        return ast_symb(p->str_val);
    }
    ast_val_t *val_buf[32];
    // parse quote
    if (p->type == QUOTE) {
        p = p + 1;
        val_buf[0] = ast_singleton(VAL_QUOTE);
        val_buf[1] = next_expr(&p, end);
        *buf = p;

        return ast_list(val_buf, 2);
    }
    // parse list
    if (p->type == LB) {
        p = p + 1;
        int num = 0;
        while (p != end && p->type != RB) {
            val_buf[num++] = next_expr(&p, end);
        }
        if (p == end) {
            lex_fail("Unexpected end of input. Lexing failed.");
        }
        *buf = p + 1;
        return ast_list(val_buf, num);
    }
    if (p->type == RB) {
        lex_fail("Unexpected `)`. Are you writing expressions like `' )`?");
    }

    lex_fail("Unexpected token. Lexing failed.");
    return 0;
}

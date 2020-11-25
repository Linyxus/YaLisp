//
// Created by Yichen Xu on 2020/8/17.
//

#include "token.h"
#include "ctypes.h"
#include "ulib.h"

void token_fail(char *msg) {
    kprintf("Tokenization error: %s\n", msg);
    exit(-1);
}

token_t *token_singleton(token_type_t t) {
    token_t *token = kmalloc(sizeof(token_type_t));
    token->type = t;

    return token;
}

token_t *token_int(int val) {
    token_t *token = kmalloc(sizeof(token_type_t));
    token->type = LIT_INT;
    token->int_val = val;

    return token;
}

token_t *token_str(const char *begin, const char *end) {
    token_t *token = kmalloc(sizeof(token_type_t));
    long len = end - begin;
    char *str = kmalloc(len + 1);
    memcpy(str, begin, len);
    str[len] = '\0';

    token->type = LIT_STR;
    token->str_val = str;

    return token;
}

token_t *token_bool(int val) {
    token_t *token = kmalloc(sizeof(token_type_t));
    token->type = LIT_BOOL;
    token->int_val = val;

    return token;
}

token_t *token_symb(const char *begin, const char *end) {
    token_t *token = kmalloc(sizeof(token_type_t));
    long len = end - begin;
    char *str = kmalloc(len + 1);
    memcpy(str, begin, len);
    str[len] = '\0';

    token->type = SYMBOL;
    token->str_val = str;

    return token;
}

int read_int_lit(char **buf, char *end) {
    char ch = **buf;
    int d = 0;
    while (is_num(ch) && *buf != end) {
        d = d * 10 + ch - '0';
        *buf = *buf + 1;
        ch = **buf;
    }
    if (*buf != end && !is_space(ch) && !is_paren(ch)) {
        token_fail("Invalid char while reading a int.");
    }

    return d;
}

char *read_str_lit(char **buf, char *end) {
    char *p = *buf;
    while (p != end && *p != '"') {
        *buf = *buf + 1;
        p = *buf;
    }
    if (p == end) {
        token_fail("Unexpected end of buffer.");
    }
    *buf = *buf + 1;
    return p;
}

char *maybe_read_symb(char **buf, char *end) {
    char *p = *buf;
    while (p != end && !is_space(*p) && !is_paren(*p)) {
        *buf = *buf + 1;
        p = *buf;
    }
    return p;
}

token_t *next_token(char **buf, char *end) {
    char *p = *buf;
    while (is_space(*p) && p != end) {
        p = p + 1;
    }
    if (p == end) { // end of buf
        return 0;
    }
    char ch = *p;
    // simple symbols
    if (ch == '\'') {
        *buf = p + 1;
        return token_singleton(QUOTE);
    }
    if (ch == '(') {
        *buf = p + 1;
        return token_singleton(LB);
    }
    if (ch == ')') {
        *buf = p + 1;
        return token_singleton(RB);
    }
    if (ch == '+') {
        *buf = p + 1;
        return token_singleton(PLUS);
    }
    if (ch == '-') {
        *buf = p + 1;
        return token_singleton(MINUS);
    }
    if (ch == '*') {
        *buf = p + 1;
        return token_singleton(MULT);
    }
    if (ch == '>' && *(p + 1) == '=') {
        *buf = p + 2;
        return token_singleton(GE);
    }
    if (ch == '>') {
        *buf = p + 1;
        return token_singleton(GT);
    }
    if (ch == '<' && *(p + 1) == '=') {
        *buf = p + 2;
        return token_singleton(LE);
    }
    if (ch == '<') {
        *buf = p + 1;
        return token_singleton(LT);
    }
    if (ch == '=' && *(p + 1) == '=') {
        *buf = p + 2;
        return token_singleton(EQ);
    }
    if (ch == '!' && *(p + 1) == '=') {
        *buf = p + 2;
        return token_singleton(NEQ);
    }
    // int literal
    if (is_num(ch)) {
        *buf = p;
        int val = read_int_lit(buf, end);
        return token_int(val);
    }
    // string literal
    if (ch == '"') {
        *buf = p + 1; // move carot next to `"`
        return token_str(p + 1, read_str_lit(buf, end));
    }
    // keyword or symbol or boolean
    *buf = p;
    token_t *token = token_symb(p, maybe_read_symb(buf, end));
    if (strcmp(token->str_val, "#t") == 0) {
        token->type = LIT_BOOL;
        token->int_val = 1;
    }
    if (strcmp(token->str_val, "#f") == 0) {
        token->type = LIT_BOOL;
        token->int_val = 0;
    }
    if (strcmp(token->str_val, "if") == 0) {
        token->type = IF;
    }
    if (strcmp(token->str_val, "do") == 0) {
        token->type = DO;
    }
    if (strcmp(token->str_val, "def") == 0) {
        token->type = DEF;
    }
    if (strcmp(token->str_val, "defun") == 0) {
        token->type = DEFUN;
    }
    return token;
}

void print_token(token_t *token) {
    switch (token->type) {
        case QUOTE: kprintf(" ' "); break;
        case LB: kprintf(" ( "); break;
        case RB: kprintf(" ) "); break;
        case PLUS: kprintf(" + "); break;
        case MINUS: kprintf(" - "); break;
        case MULT: kprintf(" * "); break;
        case LT: kprintf(" < "); break;
        case LE: kprintf(" <= "); break;
        case GT: kprintf(" > "); break;
        case GE: kprintf(" >= "); break;
        case EQ: kprintf(" == "); break;
        case NEQ: kprintf(" != "); break;
        case LIT_INT: kprintf(" %d ", token->int_val); break;
        case LIT_BOOL: kprintf(" %s ", (token->int_val ? "#t" : "#f")); break;
        case LIT_STR: kprintf(" \"%s\" ", token->str_val); break;
        default: kprintf(" %s ", token->str_val); break;
    }
}


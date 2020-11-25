//
// Created by Yichen Xu on 2020/8/17.
//

#ifndef EASTER_LISP_LEX_H
#define EASTER_LISP_LEX_H

#include "ast.h"
#include "token.h"


ast_val_t *next_expr(token_t **buf, token_t *end);

#endif //EASTER_LISP_LEX_H

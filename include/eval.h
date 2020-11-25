//
// Created by Yichen Xu on 2020/8/17.
//

#ifndef EASTER_LISP_EVAL_H
#define EASTER_LISP_EVAL_H

#include "ast.h"
#include "total_map.h"
#include "ulib.h"

ast_val_t *eval(ast_val_t *expr, tm_t *penv);

#endif //EASTER_LISP_EVAL_H

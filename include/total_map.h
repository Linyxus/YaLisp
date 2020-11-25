//
// Created by Yichen Xu on 2020/8/18.
//

#ifndef EASTER_LISP_TOTAL_MAP_H
#define EASTER_LISP_TOTAL_MAP_H

#include "ast.h"

struct tm_node_s {
    char *key;
    ast_val_t *val;
    struct tm_node_s *next;
};
typedef struct tm_node_s tm_node_t;

typedef tm_node_t *tm_t;

tm_t tm_init();

tm_t tm_insert(tm_t tm, const char *key, ast_val_t *val);

ast_val_t *tm_lookup(tm_t tm, const char *key);

#endif //EASTER_LISP_TOTAL_MAP_H

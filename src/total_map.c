//
// Created by Yichen Xu on 2020/8/18.
//

#include "total_map.h"
#include "ulib.h"

tm_t tm_init() {
    return 0;
}

tm_t tm_insert(tm_t tm, const char *key, ast_val_t *val) {
    tm_node_t *node = malloc(sizeof(tm_node_t));
    node->key = strdup(key);
    node->val = val;
    node->next = tm;
    return node;
}

ast_val_t *tm_lookup(tm_t tm, const char *key) {
    if (!tm) return 0;
    if (strcmp(tm->key, key) == 0) return tm->val;
    return tm_lookup(tm->next, key);
}


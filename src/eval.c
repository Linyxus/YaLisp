//
// Created by Yichen Xu on 2020/8/17.
//

#include "ulib.h"
#include "ast.h"
#include "eval.h"

void eval_fail(char *msg) {
    kprintf("Eval error: %s\n", msg);
    exit(-1);
}

int is_symb(const char *symb, ast_val_t *val) {
    if (val->type != VAL_SYMB) eval_fail("Unexpected ast node type in is_symb.");
    return strcmp(symb, val->str_val) == 0;
}

ast_val_t *eval(ast_val_t *expr, tm_t *env) {
    // normal form
    if (expr->type == VAL_INT) {
        return expr;
    }
    if (expr->type == VAL_STR) {
        return expr;
    }
    if (expr->type == VAL_BOOL) {
        return expr;
    }
    // symbol
    if (expr->type == VAL_SYMB) {
        ast_val_t *symb_val = tm_lookup(*env, expr->str_val);
        if (symb_val == 0) {
            eval_fail("Undefined symbol.");
        }
        return symb_val;
    }
    // LISt Processing!
    if (expr->type == VAL_LIST) {
        if (expr->int_val <= 0) { eval_fail("Zero-length list."); }
        ast_val_t *op = expr->list_val[0];
        if (op->type == VAL_PLUS) {
            if (expr->int_val < 2) { eval_fail("Plus have to be applied to at least one argument."); }
            int s = 0;
            for (int i = 1; i < expr->int_val; i++) {
                ast_val_t *node = eval(expr->list_val[i], env);
                if (node->type != VAL_INT) { eval_fail("Type error. Int is expected."); }
                s += node->int_val;
            }
            return ast_int(s);
        }
        if (op->type == VAL_MINUS) {
            if (expr->int_val < 2) { eval_fail("Minus have to be applied to at least one argument."); }
            int s = 0;

            if (expr->int_val == 2) {
                ast_val_t *node = eval(expr->list_val[1], env);
                if (node->type != VAL_INT) { eval_fail("Type error. Int is expected."); }
                return ast_int(-node->int_val);
            }

            for (int i = 1; i < expr->int_val; i++) {
                ast_val_t *node = eval(expr->list_val[i], env);
                if (node->type != VAL_INT) { eval_fail("Type error. Int is expected."); }
                if (i == 1) s = node->int_val;
                else s -= node->int_val;
            }
            return ast_int(s);
        }
        if (op->type == VAL_MULT) {
            if (expr->int_val < 2) { eval_fail("Mult have to be applied to at least one argument."); }
            int s = 1;
            for (int i = 1; i < expr->int_val; i++) {
                ast_val_t *node = eval(expr->list_val[i], env);
                if (node->type != VAL_INT) { eval_fail("Type error. Int is expected."); }
                s *= node->int_val;
            }
            return ast_int(s);
        }
        if (op->type == VAL_LT) {
            if (expr->int_val != 3) { eval_fail("< have to be applied to exact two argument."); }
            ast_val_t *l = eval(expr->list_val[1], env);
            ast_val_t *r = eval(expr->list_val[2], env);
            if (l->type != r->type) {
                eval_fail("Left and right side type mismatch.");
            }
            if (l->type == VAL_BOOL || l->type == VAL_INT) {
                return ast_bool(l->int_val < r->int_val ? 1 : 0);
            }
            if (l->type == VAL_STR) {
                return ast_bool(strcmp(l->str_val, r->str_val) < 0);
            }
            eval_fail("Unsupported operand type.");
        }
        if (op->type == VAL_LE) {
            if (expr->int_val != 3) { eval_fail("<= have to be applied to exact two argument."); }
            ast_val_t *l = eval(expr->list_val[1], env);
            ast_val_t *r = eval(expr->list_val[2], env);
            if (l->type != r->type) {
                eval_fail("Left and right side type mismatch.");
            }
            if (l->type == VAL_BOOL || l->type == VAL_INT) {
                return ast_bool(l->int_val <= r->int_val ? 1 : 0);
            }
            if (l->type == VAL_STR) {
                return ast_bool(strcmp(l->str_val, r->str_val) <= 0);
            }
            eval_fail("Unsupported operand type.");
        }
        if (op->type == VAL_GT) {
            if (expr->int_val != 3) { eval_fail("> have to be applied to exact two argument."); }
            ast_val_t *l = eval(expr->list_val[1], env);
            ast_val_t *r = eval(expr->list_val[2], env);
            if (l->type != r->type) {
                eval_fail("Left and right side type mismatch.");
            }
            if (l->type == VAL_BOOL || l->type == VAL_INT) {
                return ast_bool(l->int_val > r->int_val ? 1 : 0);
            }
            if (l->type == VAL_STR) {
                return ast_bool(strcmp(l->str_val, r->str_val) > 0);
            }
            eval_fail("Unsupported operand type.");
        }
        if (op->type == VAL_GE) {
            if (expr->int_val != 3) { eval_fail(">= have to be applied to exact two argument."); }
            ast_val_t *l = eval(expr->list_val[1], env);
            ast_val_t *r = eval(expr->list_val[2], env);
            if (l->type != r->type) {
                eval_fail("Left and right side type mismatch.");
            }
            if (l->type == VAL_BOOL || l->type == VAL_INT) {
                return ast_bool(l->int_val >= r->int_val ? 1 : 0);
            }
            if (l->type == VAL_STR) {
                return ast_bool(strcmp(l->str_val, r->str_val) >= 0);
            }
            eval_fail("Unsupported operand type.");
        }
        if (op->type == VAL_EQ) {
            if (expr->int_val != 3) { eval_fail("== have to be applied to exact two argument."); }
            ast_val_t *l = eval(expr->list_val[1], env);
            ast_val_t *r = eval(expr->list_val[2], env);
            if (l->type != r->type) {
                eval_fail("Left and right side type mismatch.");
            }
            if (l->type == VAL_BOOL || l->type == VAL_INT) {
                return ast_bool(l->int_val == r->int_val ? 1 : 0);
            }
            if (l->type == VAL_STR) {
                return ast_bool(strcmp(l->str_val, r->str_val) == 0);
            }
            eval_fail("Unsupported operand type.");
        }
        if (op->type == VAL_NEQ) {
            if (expr->int_val != 3) { eval_fail("!= have to be applied to exact two argument."); }
            ast_val_t *l = eval(expr->list_val[1], env);
            ast_val_t *r = eval(expr->list_val[2], env);
            if (l->type != r->type) {
                eval_fail("Left and right side type mismatch.");
            }
            if (l->type == VAL_BOOL || l->type == VAL_INT) {
                return ast_bool(l->int_val != r->int_val ? 1 : 0);
            }
            if (l->type == VAL_STR) {
                return ast_bool(strcmp(l->str_val, r->str_val) != 0);
            }
            eval_fail("Unsupported operand type.");
        }

        if (op->type == VAL_IF) {
            if (!(expr->int_val == 3 || expr->int_val == 4)) { eval_fail("if have to be applied to exact 3 or 4 argument."); }
            ast_val_t *cond = eval(expr->list_val[1], env);
            if (cond->type != VAL_BOOL) {
                eval_fail("Type error. Condition must be bool.");
            }
            if (cond->int_val) {
                return eval(expr->list_val[2], env);
            } else if (expr->int_val == 4) {
                return eval(expr->list_val[3], env);
            }
        }

        if (op->type == VAL_DO) {
            if (expr->int_val < 2) { eval_fail("do have to be applied to more than one argument."); }
            ast_val_t *ret = 0;
            for (int i = 1; i < expr->int_val; i++) {
                ret = eval(expr->list_val[i], env);
            }
            return ret;
        }

        if (op->type == VAL_DEF) {
            if (expr->int_val != 3) { eval_fail("def have to be applied to exactly two arguments."); }
            if (expr->list_val[1]->type != VAL_SYMB) {
                eval_fail("Symbol is expected in def name.");
            }
            ast_val_t *res = eval(expr->list_val[2], env);
            *env = tm_insert(*env, expr->list_val[1]->str_val, res);
            return res;
        }

        char *name_buf[32];
        if (op->type == VAL_DEFUN) {
            if (expr->int_val < 3) { eval_fail("defun have to be applied to at least two arguments."); }
            ast_val_t *func_def = expr->list_val[1];
            if (func_def->type == VAL_SYMB) {
                ast_val_t *func = ast_func(func_def->str_val,
                                           0, 0,
                                           expr->list_val + 2, expr->int_val - 2,
                                           *env);
                *env = tm_insert(*env, func->str_val, func);
                return func;
            } else if (func_def->type == VAL_LIST) {
                if (func_def->int_val < 2) { eval_fail("defun def should be a list of length more than one."); }
                for (int i = 0; i < func_def->int_val; i++) {
                    if (func_def->list_val[i]->type != VAL_SYMB) {
                        eval_fail("defun def should be a list of symbols.");
                    }
                    name_buf[i] = func_def->list_val[i]->str_val;
                }
                ast_val_t *func = ast_func(name_buf[0],
                                           name_buf + 1, func_def->int_val - 1,
                                           expr->list_val + 2, expr->int_val - 2,
                                           *env);
                *env = tm_insert(*env, func->str_val, func);
                func->func_def_scope = *env;
                return func;
            } else {
                eval_fail("defun name must be a symbol or a list of symbols");
            }
        }

        if (op->type == VAL_QUOTE) {
            if (expr->int_val != 2) { eval_fail("car have to be applied to exactly one arguments."); }
            return expr->list_val[1];
        }

        ast_val_t *arg_buf[32];
        tm_t func_env;
        if (op->type == VAL_FUNC) {
            if (expr->int_val != op->arg_num + 1) {
                eval_fail("Func applied to wrong num of args.");
            }
            func_env = op->func_def_scope;
            for (int i = 0; i < op->arg_num; i++) {
                arg_buf[i] = eval(expr->list_val[i + 1], env);
                func_env = tm_insert(func_env, op->func_args[i], arg_buf[i]);
            }
            ast_val_t *res = 0;
            for (int i = 0; i < op->int_val; i++) {
                res = eval(op->list_val[i], &func_env);
            }
            return res;
        }

        if (op->type == VAL_SYMB) {
            // built in functions
            if (is_symb("car", op)) {
                if (expr->int_val != 2) { eval_fail("car have to be applied to exactly one arguments."); }
                ast_val_t *l = eval(expr->list_val[1], env);
                if (l->type != VAL_LIST) { eval_fail("car have to be applied to list."); }
                if (l->int_val <= 0) { eval_fail("car on a empty list."); }
                return l->list_val[0];
            }
            if (is_symb("cdr", op)) {
                if (expr->int_val != 2) { eval_fail("cdr have to be applied to exactly one arguments."); }
                ast_val_t *l = eval(expr->list_val[1], env);
                if (l->type != VAL_LIST) { eval_fail("cdr have to be applied to list."); }
                if (l->int_val <= 0) { eval_fail("cdr on a empty list."); }
                return ast_list(l->list_val + 1, l->int_val - 1);
            }
            ast_val_t *list_buf[128];
            if (is_symb("cons", op)) {
                if (expr->int_val != 3) { eval_fail("cons have to be applied to exactly two arguments."); }
                ast_val_t *h = eval(expr->list_val[1], env);
                ast_val_t *l = eval(expr->list_val[2], env);
                if (l->type != VAL_LIST) { eval_fail("cons have to be applied to list."); }
                list_buf[0] = h;
                memcpy(list_buf + 1, l->list_val, l->int_val * sizeof(l));
                return ast_list(list_buf, l->int_val + 1);
            }
            if (is_symb("empty?", op)) {
                if (expr->int_val != 2) { eval_fail("car have to be applied to exactly one arguments."); }
                ast_val_t *l = eval(expr->list_val[1], env);
                if (l->type != VAL_LIST) { eval_fail("car have to be applied to list."); }
                return ast_bool(l->int_val == 0 ? 1 : 0);
            }
            if (is_symb("print", op)) {
                if (expr->int_val != 2) { eval_fail("print have to be applied to exactly one arguments."); }
                ast_val_t *v = eval(expr->list_val[1], env);
                print_ast(v);
                return ast_list(0, 0);
            }

            // fall back: defined symbols
            ast_val_t *eval_op = eval(op, env);
            expr->list_val[0] = eval_op;
            return eval(expr, env);
        }
    }
    // unsupported or should never be evaluated
    eval_fail("Undefined ast node type.");
    return 0;
}


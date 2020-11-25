#include "ulib.h"
#include "token.h"
#include "lex.h"
#include "eval.h"

static char *read_buf;
static token_t tokens[128];
static ast_val_t *ast;

int main() {
    // a simple REPL
    int exit_flag = 0;
    tm_t env = tm_init();
    tm_t *penv = &env;

    printf("Welcome to YaLisp\n");
    while (!exit_flag) {
        read_buf = readline(">>");
        int read_len = strlen(read_buf);

        char *end = read_buf + read_len;
        char *p = read_buf;
        char **buf = &p;
        token_t *t;
        int n_tokens = 0;
        while ((t = next_token(buf, end))) {
            tokens[n_tokens++] = *t;
            kfree(t);
        }

//        kprintf("Token: ");
//        for (int i = 0; i < n_tokens; i++) {
//            print_token(tokens + i);
//        }
//        putchar('\n');

        t = tokens;
        token_t *t_end = tokens + n_tokens;
        ast = next_expr(&t, t_end);

//        kprintf("Ast: ");
//        print_ast(ast);
//        putchar('\n');

        ast_val_t *val = eval(ast, penv);
//        putchar('\n');
//        kprintf("Result: ");
        print_ast(val);
        putchar('\n');
    }
}

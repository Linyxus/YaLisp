//
// Created by Yichen Xu on 2020/8/17.
//

#include "ulib.h"

char *readline(const char *prompt) {
    kprintf("%s ", prompt);
    char *buf = malloc(512);
    char *p = buf;
    char ch;
    while ((ch = getchar()) != '\n') {
        *p = ch;
        p++;
    }
    *p = '\0';

    return buf;
}

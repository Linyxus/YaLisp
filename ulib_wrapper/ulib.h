//
// Created by Yichen Xu on 2020/8/17.
//

#ifndef EASTER_LISP_ULIB_H
#define EASTER_LISP_ULIB_H

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "string.h"

#define kmalloc malloc
#define kfree free
#define kprintf printf
#define kputchar putchar
#define kputs puts

char *readline(const char *prompt);

#endif //EASTER_LISP_ULIB_H

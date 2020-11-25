//
// Created by Yichen Xu on 2020/8/17.
//

#ifndef EASTER_LISP_CTYPES_H
#define EASTER_LISP_CTYPES_H

#define is_alpha(ch) ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
#define is_num(ch) (ch >= '0' && ch <= '9')
#define is_alphanum(ch) (is_alpha(ch) || is_num(ch))
#define is_space(ch) (ch == ' ' || ch == '\n')
#define is_paren(ch) (ch == '(' || ch == ')')

#endif //EASTER_LISP_CTYPES_H

#ifndef RMD_LEXER_H
#define RMD_LEXER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

typedef enum {
    TOKEN_INVALID,
    TOKEN_SYMBOL,
    TOKEN_HEADER,
    TOKEN_ITALIC,
    TOKEN_LIST,
    TOKEN_END,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_COMMENT
} Rmd_Token_Type;

typedef struct {
    Rmd_Token_Type type;
    const char *text;
    size_t text_len;
    size_t row;
    size_t col;
} Rmd_Token;

typedef struct {
    char *content;
    size_t content_len;
    size_t cursor;
    size_t line;
    size_t bol;
} Rmd_Lexer;

Rmd_Lexer _Rmd_lexer_init(char *content, size_t content_len);
Rmd_Token _Rmd_lexer_next(Rmd_Lexer *l);

#endif

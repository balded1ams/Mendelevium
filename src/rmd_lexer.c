#include "rmd_lexer.h"

typedef struct {
    char text;
    Rmd_Token_Type token;
} Literal_Token;

Literal_Token literal_tokens[] = {
    {.text = '#', .token = TOKEN_HEADER},
    {.text = '\n', .token = TOKEN_END},
};
#define literal_tokens_count (sizeof(literal_tokens)/sizeof(literal_tokens[0]))

Rmd_Lexer _Rmd_lexer_init(char *content, size_t content_len) {
    Rmd_Lexer l = {0};
    l.content = content;
    l.content_len = content_len;
    return l;
}

int is_symbol(char c) {
    return isalnum(c) || c == '-' || c == '_' || c == '.';
}

void lexer_chop_char(Rmd_Lexer *l, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        ASSERT(l->cursor < l->content_len, "Unexpected EOF");
        char x = l->content[l->cursor];
        l->cursor++;
        if (x == '\n') {
            l->line++;
            l->bol = l->cursor;
        }
    }
}


Rmd_Token _Rmd_lexer_next(Rmd_Lexer *l) {
    Rmd_Token token = {
        .text = &l->content[l->cursor],
        .row = l->line,
        .col = l->cursor - l->bol,
    };
    if (l->cursor >= l->content_len) return token;

    if (l->content[l->cursor] == '*') {
        token.type = TOKEN_STRING;
        lexer_chop_char(l, 1);
        while (l->cursor < l->content_len && l->content[l->cursor] != '"' && l->content[l->cursor] != '\n') {
            lexer_chop_char(l, 1);
        }
        if (l->cursor < l->content_len) {
            lexer_chop_char(l, 1);
        }
        token.text_len = &l->content[l->cursor] - token.text - 2;
        token.text++;
        return token;
    }

    if (l->content[l->cursor] == '#') {
        token.type = TOKEN_HEADER;
        while (l->cursor < l->content_len && l->content[l->cursor] != '\n') {
            lexer_chop_char(l, 1);
        }
        if (l->cursor < l->content_len) {
            lexer_chop_char(l, 1);
        }
        token.text_len = &l->content[l->cursor] - token.text;
        return token;
    }
    
    for (size_t i = 0; i < literal_tokens_count; ++i) {
        if (l->content[l->cursor] == literal_tokens[i].text) {
            token.type = literal_tokens[i].token;
            token.text_len = 1;
            lexer_chop_char(l, 1);
            return token;
        }
    }

    if (isalpha(l->content[l->cursor])) {
        token.type = TOKEN_SYMBOL;
        while (l->cursor < l->content_len && is_symbol(l->content[l->cursor])) {
            lexer_chop_char(l, 1);
            token.text_len++;
        }
        return token;
    }

    if (isdigit(l->content[l->cursor])) {
        token.type = TOKEN_NUMBER;
        while (l->cursor < l->content_len && isdigit(l->content[l->cursor])) {
            lexer_chop_char(l, 1);
            token.text_len++;
        }
        return token;
    }

    lexer_chop_char(l, 1);
    token.type = TOKEN_INVALID;
    token.text_len = 1;
    return token;
}

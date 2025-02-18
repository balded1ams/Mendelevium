#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rmd_lexer.h"
#include "common.h"
#include "provider.h"

int main(void) {
    Rmd_Lexer lexer = provide_lexer("test.rmd");
    Rmd_Token token;
    int is_header = 0;

    while (lexer.cursor < lexer.content_len) {
        token = _Rmd_lexer_next(&lexer);
        if (token.text_len == 0)
            continue;

        if (token.type == TOKEN_HEADER) {
            printf("\033[1;34m");
            is_header = 1;
        } else {
            if (is_header) {
                printf("\033[0m\n"); // Reset after header
                is_header = 0;
            }
        }

        if (token.type == TOKEN_END) {
            printf("\n");
            continue;
        }

        printf("%.*s", (int)token.text_len, token.text);
    }
    printf("\033[0m\n");
    
    free(lexer.content);

    return EXIT_SUCCESS;
}


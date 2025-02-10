#include <stdio.h>
#include <stdlib.h>
#include "include/rmd_lexer.h"

int main(void) {
    FILE *file = fopen("test.rmd", "r");

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *input = malloc(file_size + 1);

    fread(input, 1, file_size, file);
    input[file_size] = '\0';
    fclose(file);

    Rmd_Lexer lexer = _Rmd_lexer_init(input, file_size);
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
                printf("\033[0m\n"); // Reset après un header
                is_header = 0;
            }
        }

        if (token.type == TOKEN_END) {
            printf("\n");
            continue;
        }

        printf("%.*s", (int)token.text_len, token.text);

        if (token.type != TOKEN_HEADER) {
            printf(" ");
        }
    }

    printf("\033[0m\n");
    free(input);
    return EXIT_SUCCESS;
}


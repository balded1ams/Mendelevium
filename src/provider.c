#include "provider.h"

Rmd_Lexer provide_lexer(char* file_name){
    FILE *file = fopen(file_name, "r");

    if(!file){
        fprintf(stderr, "can't open the file %s", file_name); 
    }
    
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *input = malloc(file_size + 1);

    fread(input, 1, file_size, file);
    input[file_size] = '\0';
    fclose(file);
    Rmd_Lexer lexed = _Rmd_lexer_init(input, file_size);
    return lexed;
}

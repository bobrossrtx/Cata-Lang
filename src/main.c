#include <libgen.h>
#include <stdio.h>
#include <cata.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        char* exec = basename(argv[0]);
        fprintf(stderr, "\033[1m\033[37m%s: \033[1m\033[31mfatal error:\033[0m no input files\n\r", exec);
        fprintf(stderr, "compilation terminated.\n\r");
        return 1;
    }

    cata_compile_file(argv[1]);

    return 0;
}
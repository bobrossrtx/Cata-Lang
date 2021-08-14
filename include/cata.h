#ifndef CATA_H
#define CATA_H

#include "token.h"

void cata_compile(char* src);
void cata_compile_file(const char* filename);

#endif // CATA_H
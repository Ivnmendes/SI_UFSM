/*
 * testes.cpp
 * Exercício sobre cadeias de caracteres.
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2024 João Vicente, UFSM
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* NÃO MUDAR ESSSE ARQUIVO!!!*/

#include "catch_amalgamated.hpp"

#include <cstring>
#include <cstdlib>

extern "C" {
    #include "cadeias.h"
}

TEST_CASE("Concatena 1") {
    char *const s = concatena("abc", "def");
    REQUIRE( strcmp(s, "abcdef") == 0 );
    free(s);
}

TEST_CASE("Concatena 2") {
    char *const s = concatena("abc", "");
    REQUIRE( strcmp(s, "abc") == 0 );
    free(s);
}


TEST_CASE("Quebra 1") {
    char **s = quebra_palavras("um dois tres quatro", ' ');
    REQUIRE( s[0] != NULL );
    REQUIRE( s[1] != NULL );
    REQUIRE( s[2] != NULL );
    REQUIRE( s[3] != NULL );
    REQUIRE( strcmp(s[0], "um") == 0 );
    REQUIRE( strcmp(s[1], "dois") == 0 );
    REQUIRE( strcmp(s[2], "tres") == 0 );
    REQUIRE( strcmp(s[3], "quatro") == 0 );
    for(int i=0; i < 4; i++)
        free(s[i]);
    free(s);
}

TEST_CASE("Quebra 2") {
    char **s = quebra_palavras("aaaaazbzcccz", ' ');
    REQUIRE( s[0] != NULL );
    REQUIRE( s[1] != NULL );
    REQUIRE( s[2] != NULL );
    REQUIRE( strcmp(s[0], "aaaaa") == 0 );
    REQUIRE( strcmp(s[1], "b") == 0 );
    REQUIRE( strcmp(s[2], "ccc") == 0 );
    for(int i=0; i < 3; i++)
        free(s[i]);
    free(s);
}
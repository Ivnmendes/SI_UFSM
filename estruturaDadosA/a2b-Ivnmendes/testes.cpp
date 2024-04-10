/*
 * testes.cpp
 * Exercício sobre TAD matriz.
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
    #include "matriz.h"
}

TEST_CASE("teste inicial 1") {
    int n = 20; 
    int** A = matriz_aloca(n);
    REQUIRE( A != NULL );
    matriz_libera(A, n);
}

TEST_CASE("teste inicial 2") {
    int n = 20; 
    int** A = matriz_aloca(n);
    REQUIRE( A != NULL );
    matriz_inicia(A, n);
    REQUIRE( A[0][0] != 0 );
    REQUIRE( A[10][10] != 0 );
    matriz_libera(A, n);
}


TEST_CASE("teste multiplicacao 1") {
    int n = 20; 
    int** A = matriz_aloca(n);
    int** B = matriz_aloca(n);
    int** C = matriz_aloca(n);
    REQUIRE( A != NULL );
    REQUIRE( B != NULL );
    REQUIRE( C != NULL );
    matriz_inicia(A, n);
    matriz_inicia(B, n);
    matriz_inicia(C, n);
    matriz_multiplica(A, B, C, n);
    REQUIRE( C[0][0] != 0 );
    REQUIRE( C[10][10] != 0 );
    matriz_libera(A, n);
    matriz_libera(B, n);
    matriz_libera(C, n);
}


TEST_CASE("teste multiplicacao 2") {
    int n = 20; 
    int** A = matriz_aloca(n);
    int** B = matriz_aloca(n);
    int** C = matriz_aloca(n);
    int** Ccopia = matriz_aloca(n);
    REQUIRE( A != NULL );
    REQUIRE( B != NULL );
    REQUIRE( C != NULL );
    REQUIRE( Ccopia != NULL );
    matriz_inicia(A, n);
    matriz_inicia(B, n);
    matriz_inicia(C, n);
    matriz_copia(Ccopia, C, n);
    REQUIRE( Ccopia[0][0] != 0 );
    matriz_multiplica(A, B, C, n);
    REQUIRE(matriz_compara(C, Ccopia, n) == 0);
    matriz_libera(A, n);
    matriz_libera(B, n);
    matriz_libera(C, n);
    matriz_libera(Ccopia, n);
}

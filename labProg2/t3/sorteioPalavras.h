#include <stdbool.h>

bool leArquivoSilabas(char* silabas[185]);  //Le o arquivo de silabas e salva no vetor passado como parametro, retorna true casa a leitura tenha sucesso e false caso nao;

void sorteiaPalavra(char **palavra, char* silabas[185]); //Sorteia uma palavra de n silabas e retorna por meio da variavel passada como parametro. É necessário o uso de ponteiro para ponteiro pois há realocação de memória dentro da função original

void liberaSilabas(char* silabas[185]); //Libera as silabas anteriormente alocadas na leitura do arquivo
#ifndef _manipula_historico_h_
#define _manipula_historico_h_

#include <stdbool.h>

bool leHistorico(int pontosHistorico[10]); //Le arquivo do historico e armazena a pontuação e o nome nos vetores passados como parametro. Retorna false se não conseguir abrir o arquivo

bool escreveHistorico(int pontosHistorico[10]); //Atualiza o arquivo do histórico com os valores dos vetores. Retorna false se não conseguir abrir o arquivo.

int verificaHistorico(int pontos, int pontosHistorico[10]); //Verifica se a pontuação é maior que alguma das 10 no histórico, se sim, retorna o indice do vetor onde vai ser inserido. Caso não seja, retorna -1

void atualizaHistorico(int posVetor, int pontos, int pontosHistorico[10]); //Atualiza vetor de histórico, posVetor é o indice onde a atualização vai começar

#endif
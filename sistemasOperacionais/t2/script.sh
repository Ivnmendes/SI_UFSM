#!/bin/bash

# Script para executar ./a.out 20 vezes com diferentes parâmetros
# e salvar os resultados em arquivos distintos

# Executar para estrutura de árvore (altura 2)
echo "Executando ./a.out 2 tree 20 vezes..."
for i in $(seq 1 20); do
    echo "Execução $i:" >> resultados_tree.txt
    ./a.out 2 tree >> resultados_tree.txt
    echo -e "\n-----------------------------\n" >> resultados_tree.txt
done

# Executar para estrutura em cadeia (altura 6)
echo "Executando ./a.out 6 chain 20 vezes..."
for i in $(seq 1 20); do
    echo "Execução $i:" >> resultados_chain.txt
    ./a.out 2 chain >> resultados_chain.txt
    echo -e "\n-----------------------------\n" >> resultados_chain.txt
done

echo "Execuções finalizadas. Resultados salvos em resultados_tree.txt e resultados_chain.txt."

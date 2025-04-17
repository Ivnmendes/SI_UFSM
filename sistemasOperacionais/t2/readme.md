# Processos em Árvore x Processos em Cadeia

O trabalho consiste na comparação da criação de processos através da chamada de sistema `fork` (ambiente Linux) formando estruturas de árvore binária cheia e cadeia de processos.

O programa recebe como parâmetro pela linha de comando (usar `argc` e `argv`) um número inteiro positivo não nulo (deve ser feito o teste de consistência da entrada fornecida). Este número corresponde à altura (h) da árvore de processos a ser gerada e ao tamanho da cadeia de processos a ser criada. A quantidade de processos que compõem as estruturas de árvore e cadeia pode ser calculada com base na fórmula `2^h + 1 – 1`.

## Exemplo

Para a entrada do valor 2 como altura, deve-se ter um total de 7 processos formando as estruturas de árvore e cadeia. Neste caso, deverão ser criados 6 processos, uma vez que o processo `aluno-t2-SO.c` é o “processo pai” da árvore ou cadeia.

A figura abaixo mostra uma árvore binária de altura 2, formada pelo processo `aluno-t2-SO.c` (ex.: `maria-t2-SO.c`) e os 6 processos que compõem a árvore.

~~~
                 P (aluno-t2-SO.c)
                / \
              F1   F2
             / \   / \
           F3  F4 F5  F6

~~~

A figura abaixo mostra uma cadeia de processos contendo 6 processos a partir do processo `t2-SO.c`. Para a criação dos processos em cadeia, garanta que a informação exibida na tela ocorra na ordem inversa à da criação dos processos, ou seja, inicialmente aparecem as informações do último processo criado, depois do penúltimo, depois do antepenúltimo, e assim por diante.

~~~
    aluno-t2-SO.c -> F1 -> F2 -> F3 -> F4 -> F5 -> F6
~~~

Cada processo deve mostrar PID e PPID do processo (id do processo e id do seu pai). Cada processo deve informar quando terminar, através de uma mensagem.

Os processos pais devem esperar os processos filhos terminarem. O programa deve evitar a ocorrência de processos zombies.

## Análise de desempenho

O programa deve realizar a análise de desempenho da criação dos processos em cada uma das estruturas, usando a chamada de sistema `clock` ou `clock_gettime` (pertencentes à biblioteca `time.h`), diretamente no código. Sendo assim, o tempo gasto na criação dos processos em árvore deverá ser medido por meio da chamada de sistema `clock`. Uma outra tomada de tempo (via chamada `clock`) deve medir o tempo de criação dos processos em cadeia. O uso da chamada de sistema `sleep`, se for o caso, não deve interferir nos tempos medidos.

Com base nos dados obtidos, realize uma avaliação comparativa, descrevendo sua percepção sobre os resultados dos experimentos. Deverão ser realizadas, pelo menos, 20 execuções do experimento para que se obtenha uma amostra aceitável e fiel.

A avaliação de desempenho deve ser enviada juntamente com o programa.

## Observações

- Trabalho individual.
- As dúvidas devem ser encaminhadas aos monitores da disciplina (contato disponível no Moodle).
- A implementação deve ser realizada em linguagem C, ambiente Linux.
- O arquivo `aluno-t2-SO.c` e o arquivo com a avaliação de desempenho devem ser enviados via Moodle até a data especificada. Não serão aceitos trabalhos enviados fora do ambiente Moodle, tampouco fora do prazo estabelecido, mesmo com desconto de nota.
- A apresentação do trabalho será agendada posteriormente.

# Análise desempenho

## Sem executar nenhuma operação

| Execução |    Árvore      |    Cadeia     |
|----------|----------------|---------------|
| 1        | 0.000748       | 0.001679      |
| 2        | 0.000730       | 0.001490      |
| 3        | 0.000653       | 0.001535      |
| 4        | 0.000574       | 0.001533      |
| 5        | 0.000662       | 0.001536      |
| 6        | 0.000655       | 0.001631      |
| 7        | 0.000695       | 0.001493      |
| 8        | 0.000626       | 0.001658      |
| 9        | 0.000624       | 0.001534      |
| 10       | 0.000636       | 0.001542      |
| 11       | 0.000699       | 0.001444      |
| 12       | 0.000701       | 0.001517      |
| 13       | 0.000649       | 0.001501      |
| 14       | 0.000629       | 0.001413      |
| 15       | 0.000581       | 0.001526      |
| 16       | 0.000698       | 0.001315      |
| 17       | 0.000814       | 0.001452      |
| 18       | 0.000644       | 0.001596      |
| 19       | 0.000635       | 0.001762      |
| 20       | 0.000577       | 0.001683      |
|**Média** |**0.0006465**   | **0.0015068** |

## Avaliação

Devido ao paralelismo, a execução por árvore acabou apresentando um melhor desempenho geral, pois a execução em cadeia ocorre de forma paralela, executando um processo por vez. O processador utilizado na execução foi um Intel i7-3770, com 4 cores e 8 threads. Foi utilizada a função `clock_gettime()` para medir o desempenho.
Por curiosidade resolvi testar medir o desempenho com a função `clock()`, e o resultado apresentado foi interessante:

| Execução |    Árvore      |    Cadeia     |
|----------|----------------|---------------|
| 1        | 0.000164       | 0.000074      |
| 2        | 0.000130       | 0.000073      |
| 3        | 0.000119       | 0.000063      |
| 4        | 0.000141       | 0.000062      |
| 5        | 0.000132       | 0.000067      |
| 6        | 0.000118       | 0.000070      |
| 7        | 0.000125       | 0.000089      |
| 8        | 0.000124       | 0.000078      |
| 9        | 0.000137       | 0.000068      |
| 10       | 0.000127       | 0.000075      |
| 11       | 0.000128       | 0.000067      |
| 12       | 0.000139       | 0.000081      |
| 13       | 0.000116       | 0.000061      |
| 14       | 0.000120       | 0.000065      |
| 15       | 0.000119       | 0.000067      |
| 16       | 0.000122       | 0.000062      |
| 17       | 0.000109       | 0.000067      |
| 18       | 0.000124       | 0.000072      |
| 19       | 0.000126       | 0.000070      |
| 20       | 0.000120       | 0.000071      |
| **Média**| **0.000126**   | **0.000070**  |

O resultado apresentado foi o inverso do primeiro teste, com a implementação em cadeia apresentando um desempenho melhor. A explicação para a diferença entre os dois meios de medição é que `clock()` mede o número de "clocks" de CPU consumidos (ou seja, mede diretamente o poder computacional utilizado, não considera o tempo gasto durante chamadas `wait()`), enquanto `clock_gettime()` mede o tempo real de execução, considerando inclusive o tempo em que o sistema está "em espera", seja devido a uma chamada `sleep()` ou `wait()`.
Conclui-se então que o uso de árvore binária de processos é mais recomendado em casos onde o uso de recursos computacionais não é um problema grande, entregando mais rapidamente resultados. Para casos de uso limitado de recursos computacionais, a implementação em cadeia é mais recomendada, com o custo de mais tempo de execução.

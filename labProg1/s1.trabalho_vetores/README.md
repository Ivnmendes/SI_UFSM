# Trabalho vetores

Faça um programa que obedeça o seguinte enunciado. Leia um valor inteiro t e faça o teste de
consistência para garantir que t ≥ 0 (solicite novos valores até que seja informado um valor válido).
Leia um vetor v1, de números reais e com t elementos distintos (se um valor repetido for informado,
deve ser solicitado um novo valor até um elemento único ser fornecido). Em seguida, leia um vetor v2,
também de números reais e com t elementos distintos. Leia um valor real n e faça o teste de
consistência para garantir que n ≥ 0.
Crie um vetor v3 de tamanho t * 2 e o preencha de forma que os elementos nas posições pares de v3
sejam equivalentes, em ordem, aos valores nas posições pares de v1 intercalados com os elementos nas
posições ímpares de v2. Os elementos nas posições ímpares de v3, por sua vez, devem equivaler, em
ordem, aos elementos nas posições pares de v2 intercalados com os elementos nas posições ímpares de
v1.
Crie e preencha um vetor v4 de tamanho t * 2 de forma que o seu primeiro elemento seja equivalente
ao último elemento de v3 acrescido de:
    - n, se a parte inteira do número em v3 for par; ou
    - n * 2, se a parte inteira do número em v3 for ímpar. 
O segundo elemento de v4 deve ser equivalente ao penúltimo de v3, também acrescido do valor em
função da parte inteira do elemento, e assim sucessivamente até o vetor estar totalmente preenchido.
Exiba v1, v2, v3 e v4. Por fim, com base em v4, t e n (desse ponto do código em diante é
expressamente vetado o acesso aos vetores v1, v2 e v3 ou a cópias temporárias de seus valores em
outras variáveis), implemente a lógica para criar e computar v5 e v6 com valores idênticos aos vetores
originais v1 e v2 (um vetor intermediário, contendo os valores que foram acrescidos à v3 para gerar v4
-- n ou n * 2 -- pode ser utilizado se preciso). Exiba v5 e v6.
Exemplo de um trace de execução:

~~~c
$ ./nomeAluno
> Digite t: 4
> Digite v1: 1.1 2.2 3.3 4.4
> Digite v2: 5.5 6.6 7.7 8.8
> Digite n: 0.5
< v1 : | 1.1 | 2.2 | 3.3 | 4.4 |
< v2 : | 5.5 | 6.6 | 7.7 | 8.8 |
< v3 : | 1.1 | 5.5 | 6.6 | 2.2 | 3.3 | 7.7 | 8.8 | 4.4 |
< v4 : | 4.9 | 9.3 | 8.7 | 4.3 | 2.7 | 7.1 | 6.5 | 2.1 |
< v5 : | 1.1 | 2.2 | 3.3 | 4.4 |
< v6 : | 5.5 | 6.6 | 7.7 | 8.8 |
~~~

**Orientações:**
    - Trabalho individual.
    - A interpretação da especificação do trabalho faz parte da avaliação.
    - Apenas podem ser utilizados os conteúdos abordados na disciplina de Laboratório de Programação I até a data de 03/10/2023.
    - O código do programa deve estar organizado, indentado e obedecer criteriosamente à especificação.
    - Sempre que possível, devem ser utilizadas funções com passagem de parâmetros por valor.
    - O nome do arquivo a ser entregue deve ser nomeAluno.c, como por exemplo mariana.c. Os trabalhos que não obedecerem essa especificação serão desconsiderados.
    - Certifique-se de compilar e testar exaustivamente seu programa antes do envio. Programas que não compilam receberão nota zero.
    - Trabalhos total ou parcialmente copiados receberão nota zero.
    - Não serão aceitos trabalhos enviados fora da plataforma Moodle.
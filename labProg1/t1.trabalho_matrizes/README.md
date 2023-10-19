# Trabalho Matrizes

Dada uma sequência de n (n > 0) números inteiros, definimos a mediana inteira da seguinte forma:
    - se n é ímpar, a mediana inteira é o valor que ocupa a posição central na sequência quando
ordenada;
    - se n é par, a mediana inteira é a parte inteira da média entre os valores que ocupam as posições
mais centrais na sequência quando ordenada.
Exemplos:
    - Sequência: 7 -3 7 1 3
    - Sequência ordenada: -3 1 3 7 7
    - Mediana inteira: 3
    - Sequência: 11 10 6 3 1 0
    - Sequência ordenada: 0 1 3 6 10 11
    - Mediana inteira: 4 (pois os dois elementos mais centrais são 3 e 6, resultando em média 4.5, cuja parte
inteira é 4). 
Neste trabalho, considere que os vizinhos de uma posição qualquer de uma matriz são aqueles
definidos pela vizinhança do tipo rei (isto é, as 8 posições adjacentes).
Seja M uma matriz de inteiros. O objetivo é calcular uma matriz Med, também inteira, de mesma
dimensão da matriz M, na qual o elemento Med[i][j] é exatamente igual à mediana inteira dos valores
de M na vizinhança de [i][j] mais o valor em M[i][j]. 
Faça um programa que leia uma matriz M de inteiros com L linhas e C colunas (onde L e C são
maiores que zero e menores ou iguais a 100) e a imprima de modo formatado (impressão formatada
como matriz, obedecendo linhas e colunas, sem necessidade da grade que envolve os valores). A
seguir, para cada valor da matriz, o programa deve:
    - imprimir a sequência de valores a serem considerados no cálculo da mediana (incluindo o próprio valor).
    - em seguida, ordenar crescentemente os valores impressos na etapa anterior, exibindo a sequência ordenada;
    - no próximo passo, deve ser identificada e exibida a mediana inteira da sequência;
    - por fim, o programa deve gerar e exibir a matriz Med (formatada como explicado anteriormente). 
As etapas anteriormente descritas devem ser realizadas em ordem. 
**Orientações:**
    - Trabalho individual.
    - A interpretação da especificação do trabalho faz parte da avaliação.
    - Apenas podem ser utilizados os conteúdos abordados na disciplina de Laboratório de Programação I até a data de 05/10/2023.
    - O código do programa deve estar organizado, indentado e obedecer criteriosamente à especificação.
    - Sempre que possível, devem ser utilizadas funções com passagem de parâmetros por valor.
    - O nome do arquivo a ser entregue deve ser nomeAluno.c, como por exemplo mariana.c. Os trabalhos que não obedecerem essa especificação serão desconsiderados.
    - Certifique-se de compilar e testar exaustivamente seu programa antes do envio. Programas que não compilam receberão nota zero.
    - Trabalhos total ou parcialmente copiados receberão nota zero.
    - Não serão aceitos trabalhos enviados fora da plataforma Moodle.
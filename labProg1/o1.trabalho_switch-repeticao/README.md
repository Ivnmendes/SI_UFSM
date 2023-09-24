# Programa com seleção e repetição

- Faça um programa que leia os 5 últimos dígitos do número de matrícula de um aluno (os
dígitos devem ser lidos em uma única variável – não usar vetor!). A seguir, o programa deve
calcular o dígito verificador (DV) do número lido da seguinte maneira:

    - Multiplica-se o número lido, com 5 dígitos, pelos multiplicadores 9, 8, 7, 6, 5, em ordem;
    - Soma-se os resultados das multiplicações parciais. Veja um exemplo dos passos a e b:

    ```
    Matricula:  2 0 1 2 3
                9 8 7 6 5
              18 0 7 12 15 = 52

    ```
    - Multiplica-se o resultado da soma realizada no passo b por 10. No exemplo, 52 * 10 = 520;
    - Aplica-se o resto inteiro da divisão no resultado do passo c. No exemplo, 520 % 11 = 3.

- O resto obtido no passo d é o DV do número de matrícula lido. Se o resto possuir dois dígitos,
apenas o último dígito deve ser considerado. Por exemplo, se o resultado do passo d for 10, o
DV será 0. Após calculado o DV, o programa deve exibir o número de matrícula formatado
como xxxxx-x, onde o último ‘x’ refere-se ao DV.
- Na sequência, o programa deve solicitar as médias obtidas em disciplinas e as respectivas
cargas horárias do aluno, bem como os valores necessários conforme cada cálculo descrito a
seguir. Caso o usuário informe um valor de nota fora do intervalo de 0 a 10 ou um valor de
carga horária menor ou igual a zero, o programa deve exibir uma mensagem adequada e
repetir a solicitação até que o usuário informe corretamente o valor. A entrada de dados deve
ser efetuada até que o usuário informe um valor negativo (como média, carga horária ou
quantidade de disciplinas), para cada um dos cálculos abaixo solicitados.
- Os cálculos seguintes referem-se a MGA (Média Geral Acumulada), ao IDA (Índice de
Desempenho Acadêmico), a MTD (Média Total de Disciplinas) e o PAA (percentual de
Aproveitamento do Aluno), os quais devem, repetidamente, ser oferecidos sob a forma de um
menu ao usuário (utilizar o comando switch). Além das 4 opções de cálculos, o menu deve
oferecer a opção de Sair, a qual viabiliza abandonar o programa.
- A **Média Geral Acumulada (MGA)** é um indicador de desempenho acadêmico que reflete a
média aritmética das médias finais das disciplinas aprovadas com nota. Estão excluídas do
cálculo da MGA as reprovações e aprovações sem nota final, tal como dispensas e
aproveitamentos sem nota. O programa deve ler os valores necessários para o cálculo da
MGA, conforme a fórmula:

    - *MGA = (MFD! + MFD2 + ... + MFDn) / n*
    - Onde:
        - MFDi = Média final da disciplina i;
        - n = Número de disciplinas aprovadas com nota.


- O **Índice de desempenho Acadêmico (IDA)** é o resultado do somatório do produto da média
final pela carga horária total das disciplinas em que aluno foi aprovado, mais o somatório do
produto da média das médias das disciplinas aprovadas com nota pelo total da carga horária
das disciplinas em que o aluno foi aprovado sem nota, menos o somatório do produto da
diferença entre a nota mínima para aprovação e a média final do aluno pela carga horária total
da disciplina em que ele foi reprovado com nota, menos o produto da nota mínima para
aprovação pela carga horária total das disciplinas com reprovação sem nota. O programa deve
ler os valores necessários para o cálculo do IDA, conforme a fórmula:

    - *IDA = SOMA(M1 * C.H. TOTAL) + SOMA(M2 * C.H. TOTAL) - SOMA((M3 - Média Final) * C.H TOTAL) - SOMA(M4 * C.H TOTAL)*
    - Onde:
        - M1 = Média final das disciplinas aprovadas com nota;
        - M2 = Média das médias das disciplinas aprovadas sem nota;
        - M3 = Nota mínima para aprovação para as disciplinas reprovadas com nota;
        - M4 = Nota mínima para aprovação para as disciplinas reprovadas sem nota


- A **Média Total de Disciplinas (MTD)** é o resultado do somatório do produto da média final
das disciplinas aprovadas com nota pela carga horária das disciplinas em que aluno foi
aprovado, menos o produto da média final das disciplinas reprovadas com nota pela carga
horária das disciplinas em que aluno foi reprovado. O programa deve ler os valores
necessários para o cálculo da MTD, conforme a fórmula:

    - MTD = *(MDA1 * ChDA1 + MDA2 * ChDA2 + … + MDAn * ChDAn) - (MDR1 * ChDR1 + MDR2 * ChDR2 + … + MDRm * ChDRj)*
    - Onde:
        - MDAi = Média da Disciplina Aprovada i;
        - ChDAi = Carga horária da Disciplina Aprovada i;
        - n = Número de disciplinas aprovadas com nota;
        - MDRj = Média da Disciplina Reprovada j;
        - ChDRj = Carga horária da Disciplina Reprovada j;
        - m = Número de disciplinas reprovadas com nota.
    - Caso o aluno apresente reprovações, as notas e o desempenho do mesmo permanecerão no histórico, mesmo cursando a disciplina novamente e tendo aprovação. Dessa forma, a MTD será afetada e terá de contemplar a mesma disciplina mais de uma vez, incluindo todas as vezes que o aluno cursou.


- O **Percentual de Aproveitamento do Aluno (PAA)** é calculado com base na quantidade de disciplinas em que o aluno obteve aprovação em relação à quantidade total de disciplinas cursadas. O programa deve ler os valores necessários para o cálculo do PAA, conforme a fórmula:
    - *PAA = (QDA * 100) / QTC*
    - Onde:
        - QDA = quantidade de disciplinas cursadas com aprovação;
        - QTC = quantidade total de disciplinas cursadas.
    - Caso o aluno não tenha nenhuma reprovação, o programa deve exibir o percentual de aproveitamento de 100% acompanhado de uma mensagem de felicitação.


- **Orientações:**
    - Trabalho individual.
    - A interpretação da especificação do trabalho faz parte da avaliação.
    - Apenas podem ser utilizados os conteúdos abordados na disciplina de Laboratório de Programação I até a data de 21/09/2023.
    - O código do programa deve estar organizado, indentado e obedecer criteriosamente à especificação.
    - Sempre que possível, devem ser utilizadas funções com passagem de parâmetros por valor.
    - O nome do arquivo a ser entregue deve ser nomeAluno.c, como por exemplo mariana.c. Os trabalhos que não obedecerem essa especificação serão desconsiderados.
    - Certifique-se de compilar e testar exaustivamente seu programa antes do envio. Programas que não compilam receberão nota zero.
    - Trabalhos total ou parcialmente copiados receberão nota zero.
    - Não serão aceitos trabalhos enviados fora da plataforma Moodle.

# Exercícios aula 24/08

1. Leia 2 valores a e b, verifique se os valores são múltiplos e escreva a mensagem “são múltiplos” ou “não são múltiplos”.
2. Leia um número e verifique se o número é positivo, negativo ou nulo, imprimindo mensagem adequada.
3. Leia um número e, se ele for positivo, imprima seu inverso (o inverso do número n é dado por 1/n). Caso contrário, imprima o valor absoluto do número (função `fabs`, `math.h`).
4. Leia um número e informe se ele é divisível por 3 e por 7, simultaneamente.
5. Calcule as raízes de uma equação de segundo grau. Lembre-se que quando A for nulo, a equação é de primeiro grau (só tem uma raiz), e também que quando delta é negativo a equação não tem raízes.
6. Supondo uma tabela médica, o peso ideal está relacionado com a altura e o sexo. Faça um programa que receba a altura e o sexo de uma pessoa, calcula e imprime o seu peso ideal, utilizando as seguintes fórmulas:
    Para mulheres: (62.1 * altura) - 44.7
    Para homens: (72.7 * altura) – 58
7. Leia 2 números e um caractere, representando as operações +,-, * e /. O programa deve imprimir o resultado da operação efetuada. Teste seu programa com a entrada: 3.6, 4 e ‘/’. A seguir, teste com 3.2, 0.0 e ‘/’ e corrija seu programa para imprimir uma mensagem caso não seja possível efetuar um cálculo.
8. Leia três valores correspondentes às medidas dos lados (a, b e c) de uma figura geométrica, e verifique se eles formam ou não um triângulo. Caso os valores formem triângulo calcule e exiba a sua área. Caso contrário, informe que eles “Não formam um triângulo”. Obs.: Para construir um triângulo é necessário que a medida de qualquer um dos lados seja menor que a soma das medidas dos outros dois e maior que o valor absoluto da diferença entre essas medidas. A área de um triângulo pode ser calculada em função de seus lados:
    * A = $\sqrt{s \cdot (s - a) \cdot (s - b) \cdot (s - c)}$
    * s = $\dfrac{(a+ b + c)}{2}$

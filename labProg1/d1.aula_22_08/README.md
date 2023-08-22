# Exercícios aula 22/08

1. Faça um programa que leia o valor da velocidade em m/s, transforme e imprima este valor em km/h.
2. Faça um programa que declare 3 variáveis inteiras a, b e c e uma variável float d. Atribua 5 para a e 2 para b. A seguir, calcule a divisão de a por b, atribuindo essa expressão a c, imprimindo o valor da variável inteira c. Na sequência, o programadeve calcular a divisão de a por b, atribuindo essa expressão a d, utilizando o recurso de cast.Observe o trecho de código abaixo: 
    ```c
    int x, y;
    x = 1.23; // conversão implícita
    printf("valor de x = %d\n", x); // imprime 1
    y = (int) 5.67; // conversão explícita - cast
    printf("valor de y = %d\n", y); // imprime 5
    ```
3. Faça um programa que leia a base e a altura de um triângulo. A seguir, calcule e imprima a sua área.
4. Faça um programa que leia o valor da hora de trabalho de um funcionário e a quantidade de horas trabalhadas no mês. A seguir, calcule o seu salário bruto, o qual corresponde ao produto da quantidade de horas trabalhadas pelo valor da hora de trabalho. Na sequência, calcule o salário líquido, o qual deve descontar 11% de IR, 8% de INSS e 5% de contribuição sindical. Todos os descontos são aplicados ao valor do salário bruto. Ao final, imprima o salário bruto, o salário líquido e o valor de cada desconto aplicado. Exibir todos os valores com 2 casas decimais.
5. Faça um programa que leia 2 valores inteiros e os armazene nas variáveis a e b, imprimindo-as. A seguir, realize a troca dos valores de modo que o valor contido em a passe para b e o valor de b passe para a. Ao final, imprima os valores de a e b.
6. Realize a troca dos valores das variáveis do exercício anterior usando apenas duas variáveis.
7. Faça um programa que leia as dimensões (em m) de um terreno retangular e de uma casa (também retangular) sobre este terreno. A seguir, calcule e exiba a área livre do terreno, em m2 e em percentual.
8. Um motorista de táxi deseja calcular o rendimento de seu carro. Sabendo-se que o preço do combustível é de R\$6,99, faça um programa que leia a marcação do odômetro (em km) no início do dia, a marcação (em km) no final do dia, o número de litros de combustível gastos e o valor total (R\$) recebido dos passageiros. A seguir, calcule e escreva a média do consumo em km/l e o lucro (líquido) do dia.
9. Pedrinho tem um cofrinho com muitas moedas e deseja saber quantos reais conseguiu poupar. Faça um programa que leia a quantidade de moedas de cada tipo e imprima o valor total economizado, em reais. Considere que existem moedas de 1, 5, 10, 25 e 50 centavos, e ainda moedas de 1 real. Não havendo moeda de um tipo, a quantidade lida deve ser zero.
10. Faça um programa que leia a quantidade de carros que uma locadora possui e o valor que ela cobra por diária, mostrando as informações pedidas a seguir:
    * Sabendo que um terço dos carros são alugados por mês, exiba o faturamento anual da locadora;
    * Quando o cliente atrasa o horário de devolução do carro, é cobrada uma multa de 10% sobre o valor da diária. Sabendo que um décimo dos carros alugados no mês são devolvidos com atraso, calcule o valor ganho com multas por mês;
    * Sabendo ainda que 5% dos carros sofrem desgaste ao longo do ano e são retirados do catálogo de carros ofertados, e 1/8 do total de carros é renovado, exiba a quantidade de carros que a locadora terá no final do ano.
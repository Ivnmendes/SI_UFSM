# Programa usando String

Faça um programa que obedeça o seguinte enunciado. Leia uma string **s1**. Essa string não conterá
nenhum espaço em branco.
Leia um caractere **dir** representando uma direção (esquerda ou direita). Faça o teste de consistência
para garantir que **dir** tenha valor ‘e’ ou ‘d’ (solicite novos valores até um caractere válido ser
informado).
Leia um inteiro **n** e faça o teste de consistência para garantir que **n > 0** (solicite novos valores até um
valor válido ser informado).
Seu objetivo neste trabalho é implementar uma função denominada **string_circular**, que deve receber
como parâmetro os valores informados pelo usuário, ou seja, uma string (**s1**), uma direção em forma
de caractere (**dir**) e um número inteiro positivo (**n**). Veja o protótipo da função string_circular abaixo:
~~~c 
void string_circular(char str[], char dir, int n); 
~~~
Essa função deve deslocar os caracteres de **s1** *circularmente* **n** posições para a direção representada
por **dir**. Após exibir a string resultante do deslocamento, a função main deve solicitar se o usuário
deseja informar novas strings, repetindo o processo até que o usuário solicite para encerrar o
programa. Tome cuidado para manipular corretamente o terminador de strings **‘\0’** (i.e., colocar
exatamente na última posição válida da sequência de caracteres).

Veja um exemplo de um trace de execução abaixo:

~~~c 
$ ./nomeAluno
> String: abcd
> Direção (‘d’ ou ‘e’): d
> Deslocamentos (> 0): 1
< String final: dabc
> Continuar (‘s’ ou ‘n’) ? s
> String: abcd
> Direção (‘d’ ou ‘e’): e
> Deslocamentos (> 0): 2
< String final: cdab
> Continuar (‘s’ ou ‘n’) ? s
> String: abcd
> Direção (‘d’ ou ‘e’): d
> Deslocamentos (> 0): 8
< String final: abcd
> Continuar (‘s’ ou ‘n’) ? n
* fim *
~~~

**Orientações:**
    - Trabalho individual.
    - A interpretação da especificação do trabalho faz parte da avaliação.
    - Apenas podem ser utilizados os conteúdos abordados na disciplina de Laboratório de Programação I até a data de 19/10/2023.
    - O código do programa deve estar organizado, indentado e obedecer criteriosamente à especificação.
    - Sempre que possível, devem ser utilizadas funções com passagem de parâmetros por valor.
    - O nome do arquivo a ser entregue deve ser nomeAluno.c, como por exemplo mariana.c. Os trabalhos que não obedecerem essa especificação serão desconsiderados.
    - Certifique-se de compilar e testar exaustivamente seu programa antes do envio. Programas que não compilam receberão nota zero.
    - Trabalhos total ou parcialmente copiados receberão nota zero.
    - Não serão aceitos trabalhos enviados fora da plataforma Moodle.
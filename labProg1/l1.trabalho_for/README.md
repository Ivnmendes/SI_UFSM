# Desafio com cartas

Um amigo seu lhe propôs um desafio. Esse desafio envolve um jogo de cartas bastante
peculiar. Neste jogo, seu amigo coloca três cartas viradas para baixo em uma mesa. Essas
cartas são, em uma ordem qualquer, o **ás de espadas**, o ás de bastos e o sete de espadas.
Seu amigo sabe a posição das cartas em cima da mesa, porém você não. Para vencer o jogo
você deve encontrar o ás de espadas. Qualquer uma das outras duas cartas (ás de bastos ou
sete de espadas) fará você perder o jogo.
Inicialmente, seu amigo pede para você escolher uma das cartas. Como você não tem
ideia de qual carta é qual, você faz sua escolha de forma aleatória. Após fazer sua seleção, seu
amigo separa a carta escolhida (ainda virada para baixo) das outras duas. Em seguida, ele lhe
revela uma das cartas **não** escolhidas e que **não** é o ás de espadas. Isso quer dizer que se
você tiver escolhido o às de bastos, ele lhe revelará o sete de espadas. De forma similar, se
você tiver escolhido sete espadas, ele lhe revelará o ás de bastos. Se você tiver escolhido o ás
de espadas, por sua vez, ele lhe revelará ou o às de bastos ou o sete de espadas (indiferente).
Assim, após a revelação, duas cartas permanecem viradas para baixo (a que você escolheu e
a que não foi revelada dentre as duas cartas remanescentes).
Surge então o momento de maior tensão do jogo: seu amigo lhe oferece a opção de
mudar a carta escolhida. Se você não tiver escolhido o ás de espadas no início, essa mudança
fará você vencer o jogo, porém se a carta que você escolheu inicialmente foi o ás de espadas,
fazer a mudança significa perder o jogo.
Como um bom aluno de computação que você é, você decide embasar sua decisão em
dados, para assim aumentar sua chance de vencer o jogo. Para tal, você opta por fazer um
experimento abrangendo as duas estratégias possíveis de serem seguidas no jogo: continuar
com a carta escolhida no início da partida ou aceitar a mudança sugerida por seu amigo.
Seu objetivo neste trabalho é criar um programa que simule **um milhão de partidas**
com cada estratégia. Ao final do programa, você terá em mãos as estatísticas de vitórias e
derrotas com cada estratégia, podendo assim calcular a porcentagem de vitórias e de derrotas,
além de recomendar a estratégia de jogo a ser adotada. Veja abaixo um exemplo de *output*
esperado. As marcações ***xx*** correspondem aos **valores resultantes da simulação** (quando
porcentagem, deverá ser arredondado para duas casas decimais) e ***XX*** corresponde a
recomendação para obter a melhor chance de vitória (se existir), sendo: **“Estratégia 1”**,
**“Estratégia 2”** ou **“Indiferente”** (isso é, mesmas chances de vitória, independente da estratégia).
~~~c

    $ ./nomeAluno_cartas
    >Estratégia 1 (sem mudança de carta):
        Partidas jogadas: 1000000
        Partidas ganhas: xx
        Partidas perdidas: xx
        % de derrotas xx.xx%
        % de vitórias xx.xx%

    >Estratégia 2 (com mudança de carta):
        Partidas jogadas: 1000000
        Partidas ganhas: xx
        Partidas perdidas: xx
        % de derrotas xx.xx%
        % de vitórias xx.xx%

    >Recomendação: XX

~~~

- **Orientações:**

    - Uma forma de gerar valores pseudo-aleatórios em seu programa é:

        - Incluir a biblioteca time.h, com: ```#include <time.h>```;

        - Especificar a semente (primeira linha do ```main```) com: ```srand(time(NULL))```;

        - Gerar um valor randômico, entre 0 (incluso) e MAX (não incluso), usando a função ```rand()```;

        - Você deve pesquisar sobre o uso das funções ```srand()``` e ```rand()```, a fim de utilizá-las no seu programa.

    - Deve ser entregue um arquivo .zip, denominado ***nomeAluno.zip***, contendo:

        - ***arquivo .c***, cujo nome deve ser: nomeAluno_cartas.c (ex. mariana.c);

        - ***arquivo .txt***, contendo um output de execução do programa e um comentário pessoal sobre o resultado (se foi o que você esperava ou se lhe surpreendeu, alguma explicação complementar que você julgue necessária, etc.);

        - Trabalhos que não obedecerem essas regras serão desconsiderados.

    - A interpretação da especificação do trabalho faz parte da avaliação.

    - Apenas podem ser utilizados os conteúdos abordados na disciplina de Laboratório de Programação I até a data de 12/09/2023.

    - Sempre que possível, devem ser utilizadas funções com passagem de parâmetro por valor.

    - O código deve estar organizado, indentado e obedecer criteriosamente à especificação.

    - O trabalho é individual.

    - Certifique-se de compilar e testar exaustivamente o programa antes do envio. Programas que não compilarem serão desconsiderados.

    - Não serão aceitos trabalhos entregues fora da plataforma Moodle.

    - Trabalhos total ou parcialmente copiados receberão nota zero.

# **Relatório trabalho Pesquisa e Ordenação de Dados "A"**

- **Aluno:** Ivan Mendes Martignago

- **Curso:** Sistemas de informação

## Sumário

- [**Relatório trabalho Pesquisa e Ordenação de Dados "A"**](#relatório-trabalho-pesquisa-e-ordenação-de-dados-a)
  - [Sumário](#sumário)
  - [Algoritmos](#algoritmos)
    - [Bucket Sort](#bucket-sort)
    - [QuickSort](#quicksort)
    - [CocktailSort](#cocktailsort)
    - [InsertionSort](#insertionsort)
    - [ShellSort](#shellsort)
  - [Motivos para escolha dos algoritmos](#motivos-para-escolha-dos-algoritmos)
    - [QuickSort](#quicksort-1)
    - [CocktailSort](#cocktailsort-1)
    - [ShellSort](#shellsort-1)
  - [Desempenho dos algortimos](#desempenho-dos-algortimos)
    - [Números aleatórios](#números-aleatórios)
    - [Números parcialmente ordenados](#números-parcialmente-ordenados)
    - [Números aleatórios de 0 a 10000](#números-aleatórios-de-0-a-10000)
    - [Análise dos resultados](#análise-dos-resultados)

## Algoritmos

### Bucket Sort

~~~c
void BucketSort(int arr[], int t, void (*sortFunc)(int[], int));
int getBucketIndex(int value, int interval, int minValue, **int** nBuckets);
~~~

- ```BucketSort```: Função principal de ordenação por baldes, dividindo os elementos do array em baldes de intervalo x, ordenando individualmente eles e mesclando no fim. Usa um algoritmo de ordenação (normalmente ```insertion sort```) para ordenar os baldes.
  - Os parâmetros são: O array contendo os elementos, tamanho do array, número de baldes, intervalo de números contidos em cada balde, menor valor contido no vetor e a função responsável por ordenar os baldes.
- ```getBucketIndex```: Encontra o balde certo para guardar determinado valor a partir do menor valor contido no array e do intervalo entre baldes.
  - Os parâmetros são: O próximo valor a ser inserido, o intervalo entre baldes, o menor valor contido no array e o número total de baldes.

- Calculo do número de baldes e do intervalo entre eles:

    ~~~c
        void configureBuckets(int tamVet, int minValue, int maxValue,nt *nBuckets, int *interval) {
        int targetPerBucket = (int)sqrt(tamVet);
        int range = maxValue - minValue + 1;

        *nBuckets = (tamVet / targetPerBucket);
        if (*nBuckets > range) {
            *nBuckets = range;
        }

        *interval = (int)ceil((double)range / *nBuckets);
    }
    ~~~

  - Primeiramente define um objetivo de elementos por balde, depois calcula o a distância entre o menor e o maior número, soma 1 para garantir que não é zero (improvável). Calcula o número de baldes necessários para guardar ```targetPerBucket``` por balde. Se for maior que range entre os números, limita o número de baldes. Define o intervalo como o range entre o maior e menor número dividido pelo número de baldes.

~~~c
int **buckets = malloc(nBuckets * sizeof(int *));
int *bucketSizes = calloc(nBuckets, sizeof(int)); 
int *bucketCapacities = calloc(nBuckets, sizeof(int)); 
~~~

- ```buckets```: Matriz de baldes, onde a linha define o balde e a coluna os elementos.
- ```bucketSizes```: Guarda o número de elementos contidos em cada balde.
- ```bucketCapacities```: Capacidade total de cada balde.

Enquanto os baldes são preenchidos, se necessário realoca memória para eles para garantir que possuam espaço para armazenar todos os elementos necessários. O cálculo consiste no tamanho atual somado como intervalo inicial definido.

Após preencher os baldes, ordena eles com a função de ordenação fornecida. Depois, Coloca os elementos ordenados no array original.

### QuickSort

Algoritmo que divide um vetor em pedaços menores e os ordena recursivamente. Consiste na escolha de um pivô, que representa o elemento a partir de onde a ordenação vai ocorrer. Depois, posiciona todos os elementos menores que ele na esquerda e maiores que ele na direita. No fim desse processo, o pivô estará na posição final da ordenação. Em seguida, executa o mesmo processo nos elementos da esquerda e direita de maneira recursiva. Termina quando a partição tem um elemento, significando que o vetor está ordenado.

~~~c
    static void quick_sort(int arr[], int left, int right) {
        if(left < right) {
            int indexPivot = partition(arr, left, right);
            quick_sort(arr, left, indexPivot - 1);
            quick_sort(arr, indexPivot + 1, right);
        }
    }

    static int partition(int arr[], int left, int right) {
        int pivot = arr[left];
        int i = left;
        int j;

        for(j = left + 1; j <= right; j++) {
            if (arr[j] <= pivot) {
            i += 1;
            swap(arr, i, j);
            }
        }

        swap(arr, left, i);

        return i;
    }

    static void swap(int arr[], int x, int y) {
        int aux = arr[x];
        arr[x] = arr[y];
        arr[y] = aux;
    }
~~~

- Parametros:
  - ```arr```: Array a ser ordenado.
  - ```left```: Indice inicial da partição (na primeira volta é 0);
  - ```right```: Indice final da partição (na primeira volta é vetTam - 1);
- Se ```left``` >= ```right```, significa que a ordenção terminou, pois o tamnho do subarray vai ser menor ou igual a 1;
- ```partition```: Escolhe um pivô e particiona o array em duas partes. O critério de escolha do pivô foi mantido da implementação original, que é sempre o primeiro elemento do subarray, o que pode não ser performático em alguns casos (números parcialmente ordenados, por exemplo). Uma melhor implementação seria defini-lo como a mediana entre o o primeiro, o médio e o último elemento, garantindo um particionamento mais balanceado. Preferi manter essa opção por ser mais simples.
- ```swap```: Recebe o array e dois indices, troca as posições deles.

### CocktailSort

Algoritmo de ordenação que consiste em uma modificação da implementação do buuble sort. O bubble sort consiste em comparar elementos dois a dois a partir e troca-los caso o primeiro seja maior que o segundo. Repete o processo até chegar no fim, garantindo que o maior elemento esteja na posição correta. Repete o processo até o vetor estar ordenado (quando não ocorreu nenhuma troca na volta).

A diferença do cocktail sort é que ele percorre o vetor da esquerda para a direita e depois da direita para esquerda, solucionando alguns casos como um número pequeno posicionado no final do vetor.

~~~c
    void CocktailSort(int arr[], int t) {
        int i, bottom, top, swapped, aux;
        bottom = 0;
        top = t - 1;
        swapped = 0;
        while(!swapped && bottom < top) {
            swapped = 1;
            for (i = bottom; i < top; i++) {
                if (arr[i] > arr[i+1]) {
                    swap(arr, i, i + 1);
                    swapped = 0;
                }  
            }

            top--;
            
            for (i = top; i > bottom; i--) {
                if (arr[i] < arr[i - 1]) {
                    swap(arr, i, i - 1);
                    swapped = 0;
                }
            }

            bottom++;
        }
    }
~~~

### InsertionSort

Algoritmo simples e eficiente para ordenação de listas pequenas ou parcialmente ordenadas. É o algoritmo padrão usado para ordenar os baldes no bucket sort.

Consiste em pegar um elemento de cada vez e posiciona-lo na posição correta. Começa do segundo elemento e compara-o com os da sua esquerda, movendo-os para direita até achar a posição correta para o elemento atual. Repete o processo até que a lista inteira esteja ordenada.

~~~c
    void InsertionSort(int arr[], int t) {
        int i;
        for (i = 1; i < t; ++i) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
~~~

### ShellSort

Esse algoritmo baseia-se na ideia proposta pelo insertion sort, diferenciando-se porque, em vez de aplicar a troca de maneira sequencial, usa "gaps" para comparar elementos distantes. A cada volta os "gaps" são diminuidos até chegar a um, quando o shell sort roda pela última vez para terminar de ordenar o array.

A escolha dos gaps é uma parte importante para o desempenho desse algoritmo. Para esse trabalho foi usada a sequência de knuth, que é a mesma implementação usada na referência que usei para o algoritmo.

~~~c
    void ShellSort(int arr[], int t) {
        int gap = 1;
        int i;

        /* Find initial gap in Knuth's sequence (3^k - 1) / 2 */
        while (gap < t) {
            gap = 3 * gap + 1;
        }

        while (gap > 0) {
            for (i = gap; i < t; i += gap) {
            int j = i;
            int temp = arr[i];

            while ((j >= gap) && (temp < arr[j - gap])) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
            }

            gap /= 3;
        }
    }
~~~

## Motivos para escolha dos algoritmos

### QuickSort

Escolhi porque queria testar o bucket com um algoritmo eficiente em grandes vetores.

### CocktailSort

Como planejava testar com números parcialmente ordenados, escolhi esse algoritmos pois queria ver o contraste dele no uso com números aleatórios e parcialmente ordenados.

### ShellSort

Estava curioso em como ele ia se sair em relação ao quick sort e ao insertion sort.

## Desempenho dos algortimos

O método para medir desempenho usado foi o número de segundos que programa levou para executar.

### Números aleatórios

|Algoritmo|100000 elementos|1000000 elementos|10000000 elementos| 10000000 elementos|
|-|-|-|-|-|
|InsertionSort|0.028271s|0.609261s|16.371044s|498.198622s|
|ShellSort|0.029486s|0.628780s|16.803243s|499.845034s|
|CocktailSort|0.066917s|1.725780s|51.475220s|1820.235966s\*|
|QuickSort|0.018061s|0.199769s|2.195495s|23.988953s|

- \* **obs**: Deixei os testes rodando por mais ou menos 8 horas. Como não estava em casa durante a execução, não tenho certeza se esse tempo exibido pelo programa foi o tempo que ele levou.

### Números parcialmente ordenados

|Algoritmo|100000 elementos|1000000 elementos|10000000 elementos| 10000000 elementos|
|-|-|-|-|-|
|InsertionSort|0.013655s|0.139124s|1.465611s|13.831454s|
|ShellSort|0.013782s|0.140227s|1.465443s|13.714257s|
|CocktailSort|0.014412s|0.149534s|1.580787s|14.745930s|
|QuickSort|0.021823s|0.371489s|8.528898s|xxx\*|

- \* **obs**: Assim como no caso anterior, o resultado desse caso foi inconclusivo, pois, a partir do tempo que os outros casos geraram, é possível chegar a duas conclusões, ou a execução do código foi comprometida ou a ordenação de 100 milhões de elementos parcialmente ordenados levou mais de 6 horas, já que quando finalizei os testes o algoritmo ainda estava travado nessa etapa.

### Números aleatórios de 0 a 10000

|Algoritmo|100000 elementos|1000000 elementos|10000000 elementos|
|-|-|-|-|
|InsertionSort|0.028096s|0.617154s|17.292353s|
|ShellSort|0.030610s|0.627418s|17.010757s|
|CocktailSort|0.066577s|1.766394s|58.346611s|
|QuickSort|0.020016s|0.424564s|27.658516s|

### Análise dos resultados

Em todos os casos os algoritmos se comportaram perto do esperado.

Nos números aleatórios
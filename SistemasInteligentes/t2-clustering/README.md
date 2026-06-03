# Trabalho Prático: Algoritmos de Clustering

Este projeto realiza a análise e agrupamento (clustering) de um dataset de predição de falha cardíaca (Heart Failure Prediction) como parte do trabalho prático da disciplina. 

## Como Rodar o Projeto

### 1. Pré-requisitos
Certifique-se de ter o Python instalado. É necessário instalar as seguintes bibliotecas para rodar o script:
```bash
pip install pandas numpy matplotlib seaborn scikit-learn
```

### 2. Gerando os Resultados e Gráficos
Para executar o script de agrupamento, que fará todo o pré-processamento, rodará os algoritmos (K-Means, Agglomerative e DBSCAN), calculará as métricas e gerará as imagens:
```bash
python clustering.py
```
*Após rodar este comando, os gráficos e tabelas de resultados serão gerados automaticamente dentro da pasta `images/`.*

---

A pasta `images/` é criada automaticamente ao rodar o script Python e contém todos os resultados exportados:

- **`desc_stats.csv`**: Tabela contendo a análise univariada (média, mediana, desvio padrão, mínimo, máximo, etc.) de todas as variáveis numéricas do dataset original.
- **`histograms.png`**: Gráficos de histograma criados para visualizar a distribuição dos dados antes do pré-processamento.
- **`correlation.png`**: Matriz de correlação (*Heatmap*) que mostra a relação linear entre as variáveis já pré-processadas (incluindo as categóricas após o *OneHot Encoding*).
- **`kmeans_pca.png`**: Gráfico de dispersão mostrando o resultado da divisão em clusters feita pelo algoritmo K-Means ($k=2$), reduzido a duas dimensões utilizando PCA para facilitar a visualização.
- **`clustering_results.csv`**: Tabela com o resumo das métricas (*Silhouette Score*, *Davies-Bouldin* e *Calinski-Harabasz*) calculadas para cada hiperparâmetro testado nos 3 algoritmos.
- **`ground_truth_pca.png`**: Gráfico de dispersão idêntico ao do K-Means, mas as cores representam os rótulos originais de Doença Cardíaca (*HeartDisease*), servindo de base de comparação (gabarito) para ver o quão bem o K-Means funcionou de forma cega.

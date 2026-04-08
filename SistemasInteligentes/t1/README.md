# Sistemas Inteligentes: Case-Based Reasoning (CBR)

## Trabalho Prático

**Professor:** Luís Alvaro  
**Data:** Abril 2026

---

### 1. Objetivo

Desenvolver um sistema de Raciocínio Baseado em Casos (CBR) em Python utilizando a biblioteca **CBRkit**. O sistema deve ser capaz de:

* Representar casos.
* Recuperar casos similares.
* Adaptar soluções para novos problemas.

---

### 2. Requisitos

* **Participação:** Trabalho individual ou em duplas.
* **Linguagem:** Python.
* **Biblioteca Obrigatória:** [CBRkit](https://github.com/wi2trier/cbrkit).

---

### 3. Descrição do Problema

O sistema deve atuar na área de **psicologia**, realizando as seguintes tarefas:

1. Receber um novo caso.
2. Recuperar casos similares a partir de uma base de casos.
3. Gerar uma recomendação adaptada com base nos casos recuperados.

O projeto utilizará um dataset estruturado especificamente para CBR, com separação explícita entre a **descrição do problema** e a **solução associada**.

---

### 4. Dataset

O trabalho utiliza o arquivo `cbr_psychology_110_cases_clinical.csv`, que contém 110 casos sintéticos na área de psicologia.

**Características:**

* Variáveis heterogêneas (numéricas, categóricas e textuais).
* Representação explícita de problema e solução.
* Casos distintos com similaridades estruturais.

#### 4.1 Features do Problema (Estado do Indivíduo)

| Tipo | Feature |
| :--- | :--- |
| Numérica | age, anxiety_score, depression_score, stress_level, sleep_quality, sleep_hours, symptom_duration_months, gad7_estimate, phq9_estimate, irritability_level, work_or_study_impairment, bmi_estimate |
| Categórica | gender, social_support, physical_activity, panic_symptoms, concentration_difficulty, appetite_change, prior_treatment, current_medication, trauma_history, substance_use_risk, comorbid_profile, clinical_severity |
| String | main_issue |

#### 4.2 Features da Solução (Recomendação)

| Tipo | Feature |
| :--- | :--- |
| Categórica | intervention_type |
| Numérica | intensity, weekly_frequency |
| String | recommendation_text |

---

### 5. Componentes do Sistema CBR

#### 5.1 Similaridade

É obrigatório implementar medidas de similaridade local específicas para cada tipo de feature. **Não é permitido utilizar apenas uma função genérica.**

* **Atributos Numéricos:** Ex: distância normalizada.
* **Atributos Categóricos:** Ex: igualdade ou matriz de similaridade.
* **Atributos Textuais:** Ex: Similaridade Coseno ou Jaccard.

#### 5.2 Recuperação

* Utilizar o algoritmo de **k-vizinhos mais próximos (k-NN)**.
* Retornar os casos mais similares com seus respectivos **scores de similaridade**.

#### 5.3 Adaptação

A adaptação deve modificar a solução recuperada com base no novo problema usando regras ou heurísticas. **Não é permitido apenas copiar a solução do caso mais similar.**

* **Exemplos:** Ajustar a intensidade com base na severidade clínica ou combinar múltiplos casos.

---

### 6. Avaliação do Sistema

Os alunos devem reportar a qualidade da recuperação e adaptação utilizando o próprio dataset através de métricas como:

* **Acurácia (Accuracy)**, **Precisão (Precision)**, **Recall** e **F1-score**.
* **Erro de adaptação:** Diferença entre a solução adaptada e a original esperada.

**Métodos de Validação (mínimo um):**

* **Leave-One-Out:** Remover um caso, usá-lo como consulta e repetir para toda a base.
* **K-Fold Cross-Validation:** Dividir a base em $k$ partes para treino e teste sucessivos.

---

### 7. Entregáveis

1. **Código:** Organizado e documentado.
2. **Relatório:** Análise do dataset, descrição das features, funções de similaridade, estratégia de adaptação e resultados experimentais.
3. **Vídeo:** Máximo de 10 minutos explicando o trabalho.
4. **Apresentação Oral:** Defesa obrigatória com o professor sobre o funcionamento interno e decisões de modelagem.

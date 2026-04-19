import pandas as pd
import numpy as np
import cbrkit
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, mean_absolute_error

def carregar_dados(caminho_arquivo):
    """
    Carrega o dataset e calcula as diferenças máximas para features numéricas.

    Args:
        caminho_arquivo (str): Caminho para o arquivo CSV.

    Returns:
        tuple: (casos, max_diffs)
            - casos (dict): Dicionário de casos indexados pelo ID.
            - max_diffs (dict): Diferença máxima calculada para cada feature numérica.
    """
    df = pd.read_csv(caminho_arquivo)
    
    num_features = [
        'age', 'anxiety_score', 'depression_score', 'stress_level', 
        'sleep_quality', 'sleep_hours', 'symptom_duration_months', 
        'gad7_estimate', 'phq9_estimate', 'irritability_level', 
        'bmi_estimate'
    ]
    max_diffs = {f: df[f].max() - df[f].min() for f in num_features if df[f].max() != df[f].min()}
    
    casos = df.to_dict(orient='index')
    return casos, max_diffs

def sim_numerica(val1, val2, max_diff):
    """
    Calcula a similaridade entre valores numéricos utilizando distância normalizada.

    Args:
        val1 (float): Valor do caso base.
        val2 (float): Valor do caso de consulta.
        max_diff (float): Diferença máxima permitida para a feature.

    Returns:
        float: Similaridade calculada entre 0.0 e 1.0.
    """
    if pd.isna(val1) or pd.isna(val2) or max_diff == 0:
        return 0.0
    return max(0.0, 1.0 - (abs(val1 - val2) / max_diff))

def sim_categorica(val1, val2):
    """
    Calcula a similaridade entre valores categóricos por correspondência exata.

    Args:
        val1 (str): Valor do caso base.
        val2 (str): Valor do caso de consulta.

    Returns:
        float: 1.0 para valores iguais, 0.0 para diferentes.
    """
    if pd.isna(val1) or pd.isna(val2):
        return 0.0
    return 1.0 if val1 == val2 else 0.0

def sim_textual_jaccard(str1, str2):
    """
    Calcula a similaridade entre campos de texto usando o Índice de Jaccard.

    Args:
        str1 (str): Texto do caso base.
        str2 (str): Texto do caso de consulta.

    Returns:
        float: Proporção de sobreposição de palavras entre os dois textos.
    """
    if pd.isna(str1) or pd.isna(str2):
        return 0.0
    set1 = set(str(str1).lower().split())
    set2 = set(str(str2).lower().split())
    inter = set1.intersection(set2)
    union = set1.union(set2)
    return len(inter) / len(union) if union else 0.0

def criar_sim_global(max_diffs):
    """
    Retorna a função de similaridade global que agrega as funções locais.

    Args:
        max_diffs (dict): Dicionário de diferenças máximas para features numéricas.

    Returns:
        function: Função que calcula a média aritmética das similaridades locais.
    """
    def global_sim(case, query):
        sim_num = [sim_numerica(case.get(f), query.get(f), max_diffs.get(f, 1)) 
                   for f in max_diffs.keys()]
        
        cat_features = [
            'gender', 'social_support', 'physical_activity', 'panic_symptoms', 
            'concentration_difficulty', 'appetite_change', 'prior_treatment', 
            'current_medication', 'trauma_history', 'substance_use_risk', 
            'comorbid_profile', 'clinical_severity', 'work_or_study_impairment'
        ]
        sim_cat = [sim_categorica(case.get(f), query.get(f)) for f in cat_features]
        
        sim_text = [sim_textual_jaccard(case.get('main_issue'), query.get('main_issue'))]
        
        todas_sim = sim_num + sim_cat + sim_text
        return float(np.mean(todas_sim)) if todas_sim else 0.0
    return global_sim

def adaptar_solucao(solucao_recuperada, problema_novo):
    """
    Adapta a solução do caso recuperado com base nas características do novo problema.

    Args:
        solucao_recuperada (dict): Dicionário contendo a solução base.
        problema_novo (dict): Dicionário contendo as features da consulta.

    Returns:
        dict: Solução adaptada através de regras heurísticas.
    """
    solucao_adaptada = solucao_recuperada.copy()
    
    if problema_novo.get('clinical_severity') == 'High':
        solucao_adaptada['intensity'] = min(10, solucao_adaptada['intensity'] + 2)
        
    if problema_novo.get('age', 0) > 60 and solucao_adaptada['weekly_frequency'] > 2:
        solucao_adaptada['weekly_frequency'] -= 1
        
    if problema_novo.get('substance_use_risk') == 'High' and 'Substance' not in str(solucao_adaptada.get('intervention_type', '')):
        solucao_adaptada['intervention_type'] = 'Dual Diagnosis Therapy'
        
    solucao_adaptada['recommendation_text'] = str(solucao_adaptada.get('recommendation_text', '')) + " [Adaptado]"
    return solucao_adaptada

def avaliar_sistema(casos_completos, max_diffs, k=3):
    """
    Executa a avaliação do sistema por validação Leave-One-Out e imprime as métricas.

    Args:
        casos_completos (dict): Base contendo todos os casos.
        max_diffs (dict): Dicionário de diferenças máximas.
        k (int, optional): Limite para vizinhos mais próximos. Padrão é 3.
    """
    y_true_intencao = []
    y_pred_intencao = []
    y_true_intensidade = []
    y_pred_intensidade = []
    
    sim_func = criar_sim_global(max_diffs)
    ids_casos = list(casos_completos.keys())
    
    for id_teste in ids_casos:
        query = casos_completos[id_teste]
        casebase = {chave: valor for chave, valor in casos_completos.items() if chave != id_teste}
        
        retriever = cbrkit.retrieval.build(sim_func)
        resultado = cbrkit.retrieval.apply_query(casebase, query, retriever)
        
        if not resultado.ranking:
            continue
            
        id_mais_similar = resultado.ranking[0]
        # Atribuição duplicada de caso_recuperado foi removida
        caso_recuperado = casebase[id_mais_similar]
        
        solucao_adaptada = adaptar_solucao(caso_recuperado, query)
        
        y_true_intencao.append(query['intervention_type'])
        y_pred_intencao.append(solucao_adaptada['intervention_type'])
        y_true_intensidade.append(query['intensity'])
        y_pred_intensidade.append(solucao_adaptada['intensity'])
        
    print("--- Resultados da Avaliação ---")
    print(f"Acurácia (Intervention Type): {accuracy_score(y_true_intencao, y_pred_intencao):.2f}")
    print(f"Precisão Ponderada: {precision_score(y_true_intencao, y_pred_intencao, average='weighted', zero_division=0):.2f}")
    print(f"Recall Ponderado: {recall_score(y_true_intencao, y_pred_intencao, average='weighted', zero_division=0):.2f}")
    print(f"F1-Score Ponderado: {f1_score(y_true_intencao, y_pred_intencao, average='weighted', zero_division=0):.2f}")
    
    mae_intensidade = mean_absolute_error(y_true_intensidade, y_pred_intensidade)
    print(f"Erro de Adaptação (MAE - Intensity): {mae_intensidade:.2f}")
    
if __name__ == "__main__":
    caminho = "./base_de_casos/cbr_psychology_110_cases_clinical.csv"
    try:
        casos, max_diffs = carregar_dados(caminho)
        avaliar_sistema(casos, max_diffs, k=3)
    except FileNotFoundError:
        print(f"Erro: Arquivo '{caminho}' não encontrado.")
import pandas as pd
import cbrkit
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, mean_absolute_error


def sim_numerica(val_base, val_novo, diferenca_maxima):
    """Calcula similaridade numérica (distância normalizada)."""
    if pd.isna(val_base) or pd.isna(val_novo): 
        return 0.0
    distancia = abs(val_base - val_novo)
    similaridade = 1.0 - (distancia / diferenca_maxima)
    return max(0.0, similaridade)

def sim_categorica(val_base, val_novo):
    """Calcula similaridade categórica (igualdade exata)."""
    return 1.0 if str(val_base).lower() == str(val_novo).lower() else 0.0

def sim_textual(texto_base, texto_novo):
    """Calcula similaridade de strings (Índice de Jaccard)."""
    palavras_base = set(str(texto_base).lower().split())
    palavras_novo = set(str(texto_novo).lower().split())
    
    if len(palavras_base) == 0 and len(palavras_novo) == 0:
        return 0.0
        
    intersecao = palavras_base.intersection(palavras_novo)
    uniao = palavras_base.union(palavras_novo)
    return len(intersecao) / len(uniao)


def calcular_similaridade_global(caso_base, caso_novo):
    """Agrega as similaridades locais comparando TODOS os atributos do problema."""
    notas = []
    
    notas.append(sim_numerica(caso_base.get('age'), caso_novo.get('age'), diferenca_maxima=25))
    notas.append(sim_numerica(caso_base.get('anxiety_score'), caso_novo.get('anxiety_score'), diferenca_maxima=8))
    notas.append(sim_numerica(caso_base.get('depression_score'), caso_novo.get('depression_score'), diferenca_maxima=7))
    notas.append(sim_numerica(caso_base.get('stress_level'), caso_novo.get('stress_level'), diferenca_maxima=8))
    notas.append(sim_numerica(caso_base.get('sleep_quality'), caso_novo.get('sleep_quality'), diferenca_maxima=9))
    notas.append(sim_numerica(caso_base.get('sleep_hours'), caso_novo.get('sleep_hours'), diferenca_maxima=3.9))
    notas.append(sim_numerica(caso_base.get('symptom_duration_months'), caso_novo.get('symptom_duration_months'), diferenca_maxima=9))
    notas.append(sim_numerica(caso_base.get('gad7_estimate'), caso_novo.get('gad7_estimate'), diferenca_maxima=21))
    notas.append(sim_numerica(caso_base.get('phq9_estimate'), caso_novo.get('phq9_estimate'), diferenca_maxima=27))
    notas.append(sim_numerica(caso_base.get('irritability_level'), caso_novo.get('irritability_level'), diferenca_maxima=8))
    notas.append(sim_numerica(caso_base.get('bmi_estimate'), caso_novo.get('bmi_estimate'), diferenca_maxima=11))
    
    notas.append(sim_categorica(caso_base.get('gender'), caso_novo.get('gender')))
    notas.append(sim_categorica(caso_base.get('social_support'), caso_novo.get('social_support')))
    notas.append(sim_categorica(caso_base.get('physical_activity'), caso_novo.get('physical_activity')))
    notas.append(sim_categorica(caso_base.get('panic_symptoms'), caso_novo.get('panic_symptoms')))
    notas.append(sim_categorica(caso_base.get('concentration_difficulty'), caso_novo.get('concentration_difficulty')))
    notas.append(sim_categorica(caso_base.get('appetite_change'), caso_novo.get('appetite_change')))
    notas.append(sim_categorica(caso_base.get('prior_treatment'), caso_novo.get('prior_treatment')))
    notas.append(sim_categorica(caso_base.get('current_medication'), caso_novo.get('current_medication')))
    notas.append(sim_categorica(caso_base.get('trauma_history'), caso_novo.get('trauma_history')))
    notas.append(sim_categorica(caso_base.get('substance_use_risk'), caso_novo.get('substance_use_risk')))
    notas.append(sim_categorica(caso_base.get('comorbid_profile'), caso_novo.get('comorbid_profile')))
    notas.append(sim_categorica(caso_base.get('clinical_severity'), caso_novo.get('clinical_severity')))
    notas.append(sim_categorica(caso_base.get('work_or_study_impairment'), caso_novo.get('work_or_study_impairment')))

    notas.append(sim_textual(caso_base.get('main_issue'), caso_novo.get('main_issue')))
    
    # Retorna a média de todas as 25 notas
    return sum(notas) / len(notas)


def adaptar_solucao(caso_recuperado, problema_novo):
    """
    Modifica a solução do caso histórico com base no novo problema.
    Recebe as 4 features da solução e aplica regras de domínio.
    """
    # 1. Herda a solução original do caso mais similar
    solucao = {
        'intervention_type': caso_recuperado.get('intervention_type'),
        'intensity': caso_recuperado.get('intensity', 0),
        'weekly_frequency': caso_recuperado.get('weekly_frequency', 0),
        'recommendation_text': str(caso_recuperado.get('recommendation_text', ''))
    }
    
    houve_adaptacao = False

    # Regra 1 (Adaptação Numérica): Aumenta a intensidade se o caso for grave
    if problema_novo.get('clinical_severity') == 'High':
        solucao['intensity'] = min(10, solucao['intensity'] + 2)
        houve_adaptacao = True
        
    # Regra 2 (Adaptação Numérica restritiva): Reduz frequência para idosos
    if problema_novo.get('age', 0) > 60 and solucao['weekly_frequency'] > 2:
        solucao['weekly_frequency'] = 2
        houve_adaptacao = True
        
    # Regra 3 (Adaptação Categórica): Substitui o tratamento se houver risco de vício
    if problema_novo.get('substance_use_risk') == 'High' and 'Substance' not in str(solucao['intervention_type']):
        solucao['intervention_type'] = 'therapy'
        houve_adaptacao = True
        
    # Regra 4 (Adaptação de String): Garante a rastreabilidade da decisão
    if houve_adaptacao:
        solucao['recommendation_text'] += " [Nota: Solução modificada por heurísticas]"

    return solucao


def main():
    df = pd.read_csv("./base_de_casos/cbr_psychology_110_cases_clinical.csv")
    base_completa = df.to_dict(orient='index')
    
    resultados_reais_tipo = []
    resultados_previstos_tipo = []
    resultados_reais_intensidade = []
    resultados_previstos_intensidade = []
    
    buscador = cbrkit.retrieval.build(calcular_similaridade_global)
    
    print("Iniciando Validação Leave-One-Out...")
    
    for id_teste in base_completa.keys():
        novo_caso = base_completa[id_teste]
        
        base_conhecimento = {k: v for k, v in base_completa.items() if k != id_teste}
        
        resultado_busca = cbrkit.retrieval.apply_query(base_conhecimento, novo_caso, buscador)
        
        if not resultado_busca.ranking:
            continue
            
        # Pega o ID do caso mais similar (k=1)
        id_mais_similar = resultado_busca.ranking[0]
        caso_recuperado = base_conhecimento[id_mais_similar]
        
        solucao_final = adaptar_solucao(caso_recuperado, novo_caso)
        
        # Guarda os dados para gerar o relatório final
        resultados_reais_tipo.append(novo_caso['intervention_type'])
        resultados_previstos_tipo.append(solucao_final['intervention_type'])
        
        resultados_reais_intensidade.append(novo_caso['intensity'])
        resultados_previstos_intensidade.append(solucao_final['intensity'])

    print("\n--- Resultados Finais ---")
    print(f"Acurácia (Accuracy): {accuracy_score(resultados_reais_tipo, resultados_previstos_tipo):.2f}")
    print(f"Precisão Ponderada (Precision): {precision_score(resultados_reais_tipo, resultados_previstos_tipo, average='weighted', zero_division=0):.2f}")
    print(f"Recall Ponderado: {recall_score(resultados_reais_tipo, resultados_previstos_tipo, average='weighted', zero_division=0):.2f}")
    print(f"F1-Score Ponderado: {f1_score(resultados_reais_tipo, resultados_previstos_tipo, average='weighted', zero_division=0):.2f}")
    
    erro_adaptacao = mean_absolute_error(resultados_reais_intensidade, resultados_previstos_intensidade)
    print(f"Erro de Adaptação (Intensidade MAE): {erro_adaptacao:.2f}")

if __name__ == "__main__":
    main()
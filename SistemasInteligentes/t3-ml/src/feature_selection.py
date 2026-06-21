import pandas as pd
from sklearn.ensemble import RandomForestClassifier

def selecionar_features(X_train_processado, y_train, nomes_features, top_n=10):
    """Treina um RandomForest para identificar e selecionar as features mais importantes."""
    seletor_rf = RandomForestClassifier(n_estimators=100, random_state=42)
    seletor_rf.fit(X_train_processado, y_train)

    importancias = pd.DataFrame({
        'Feature': nomes_features,
        'Importancia': seletor_rf.feature_importances_
    }).sort_values(by='Importancia', ascending=False)

    print("\n--- RANKING DE IMPORTÂNCIA DAS FEATURES ---")
    print(importancias.to_string(index=False))

    indices_selecionados = importancias.head(top_n).index
    return indices_selecionados

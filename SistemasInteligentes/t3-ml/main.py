import warnings
from sklearn.model_selection import train_test_split

from src.preprocessing import carregar_dados, carregar_dados_regressao, obter_preprocessor, obter_preprocessor_regressao
from src.feature_selection import selecionar_features
from src.modeling import treinar_e_avaliar_mlp, treinar_e_avaliar_regressao, avaliar_regularizacao
from src.optimization import otimizar_hiperparametros
from src.visualization import plotar_curvas_regularizacao

def main():
    print("--- INICIANDO PROCESSAMENTO DE CLASSIFICAÇÃO ---")
    df = carregar_dados('data/heart.csv')

    X = df.drop('HeartDisease', axis=1)
    y = df['HeartDisease']

    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42, stratify=y
    )

    colunas_numericas = ['Age', 'RestingBP', 'Cholesterol', 'MaxHR', 'Oldpeak']
    colunas_categoricas = ['Sex', 'ChestPainType', 'RestingECG', 'ExerciseAngina', 'ST_Slope']
    colunas_pass_through = ['FastingBS']

    preprocessor = obter_preprocessor(colunas_numericas, colunas_categoricas, colunas_pass_through)

    X_train_processado = preprocessor.fit_transform(X_train)
    X_test_processado = preprocessor.transform(X_test)

    print(f"Formato original de X_train: {X_train.shape}")
    print(f"Formato de X_train após pré-processamento: {X_train_processado.shape}")

    nomes_features = preprocessor.get_feature_names_out()

    print("\n--- INICIANDO ETAPA DE SELEÇÃO DE FEATURES ---")
    indices_selecionados = selecionar_features(X_train_processado, y_train, nomes_features, top_n=10)

    X_train_selecionado = X_train_processado[:, indices_selecionados]
    X_test_selecionado = X_test_processado[:, indices_selecionados]

    print(f"\nQuantidade inicial de atributos (após processamento): {X_train_processado.shape[1]}")
    print(f"Quantidade final de atributos selecionados: {X_train_selecionado.shape[1]}")

    print("\n--- TREINANDO MODELOS MLP DE CLASSIFICAÇÃO ---")
    mlp_todas = treinar_e_avaliar_mlp(
        X_train_processado, X_test_processado, y_train, y_test, "MLP com TODAS as Features (15)"
    )

    mlp_selecionadas = treinar_e_avaliar_mlp(
        X_train_selecionado, X_test_selecionado, y_train, y_test, "MLP com Features SELECIONADAS (10)"
    )

    print("\n--- INICIANDO ETAPA 5: REGRESSÃO ---")
    df_reg = carregar_dados_regressao('data/heart.csv')
    X_reg = df_reg.drop('MaxHR', axis=1)
    y_reg = df_reg['MaxHR']

    X_train_reg, X_test_reg, y_train_reg, y_test_reg = train_test_split(
        X_reg, y_reg, test_size=0.2, random_state=42
    )

    colunas_numericas_reg = ['Age', 'RestingBP', 'Cholesterol', 'Oldpeak']
    colunas_categoricas_reg = ['Sex', 'ChestPainType', 'RestingECG', 'ExerciseAngina', 'ST_Slope']
    colunas_pass_through_reg = ['FastingBS', 'HeartDisease']

    preprocessor_reg = obter_preprocessor_regressao(
        colunas_numericas_reg, colunas_categoricas_reg, colunas_pass_through_reg
    )

    X_train_reg_processado = preprocessor_reg.fit_transform(X_train_reg)
    X_test_reg_processado = preprocessor_reg.transform(X_test_reg)

    treinar_e_avaliar_regressao(X_train_reg_processado, X_test_reg_processado, y_train_reg, y_test_reg)

    print("\n--- INICIANDO ETAPA 6: OPTUNA ---")
    otimizar_hiperparametros(X_train_processado, X_test_processado, y_train, y_test)

    print("\n--- INICIANDO ETAPA 7: REGULARIZAÇÃO L2 ---")
    mlp_sem_reg, mlp_com_reg = avaliar_regularizacao(X_train_processado, X_test_processado, y_train, y_test)

    plotar_curvas_regularizacao(mlp_sem_reg, mlp_com_reg, 'grafico_regularizacao.png')

if __name__ == '__main__':
    main()
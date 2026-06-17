import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.ensemble import RandomForestClassifier
import matplotlib.pyplot as plt

df = pd.read_csv('data/heart.csv')

df['Cholesterol'] = df['Cholesterol'].replace(0, np.nan)

X = df.drop('HeartDisease', axis=1)
y = df['HeartDisease']

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

colunas_numericas = ['Age', 'RestingBP', 'Cholesterol', 'MaxHR', 'Oldpeak']
colunas_categoricas = ['Sex', 'ChestPainType', 'RestingECG', 'ExerciseAngina', 'ST_Slope']
colunas_pass_through = ['FastingBS']

pipeline_numerico = Pipeline(steps=[
    ('imputer', SimpleImputer(strategy='median')), 
    ('scaler', StandardScaler())                   
])

pipeline_categorico = Pipeline(steps=[
    ('onehot', OneHotEncoder(drop='first', sparse_output=False))
])

preprocessor = ColumnTransformer(
    transformers=[
        ('num', pipeline_numerico, colunas_numericas),
        ('cat', pipeline_categorico, colunas_categoricas),
        ('passthrough', 'passthrough', colunas_pass_through)
    ])

X_train_processado = preprocessor.fit_transform(X_train)
X_test_processado = preprocessor.transform(X_test)

print(f"Formato original de X_train: {X_train.shape}")
print(f"Formato de X_train após pré-processamento: {X_train_processado.shape}")

nomes_features = preprocessor.get_feature_names_out()

seletor_rf = RandomForestClassifier(n_estimators=100, random_state=42)
seletor_rf.fit(X_train_processado, y_train)

importancias = pd.DataFrame({
    'Feature': nomes_features,
    'Importancia': seletor_rf.feature_importances_
}).sort_values(by='Importancia', ascending=False)

print("\n--- RANKING DE IMPORTÂNCIA DAS FEATURES ---")
print(importancias.to_string(index=False))

top_n = 10
indices_selecionados = importancias.head(top_n).index

X_train_selecionado = X_train_processado[:, indices_selecionados]
X_test_selecionado = X_test_processado[:, indices_selecionados]

print(f"\nQuantidade inicial de atributos (após processamento): {X_train_processado.shape[1]}")
print(f"Quantidade final de atributos selecionados: {X_train_selecionado.shape[1]}")
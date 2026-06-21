import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.impute import KNNImputer
from sklearn.preprocessing import StandardScaler, RobustScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline

def carregar_dados(caminho='data/heart.csv'):
    """Carrega os dados e realiza o pré-processamento inicial para classificação."""
    df = pd.read_csv(caminho)
    # Remover outlier impossível (Pressão arterial zero)
    df = df[df['RestingBP'] > 0]
    # Substituir zeros por NaN para imputação posterior
    df['Cholesterol'] = df['Cholesterol'].replace(0, np.nan)
    return df

def carregar_dados_regressao(caminho='data/heart.csv'):
    """Carrega os dados e realiza o pré-processamento inicial para regressão."""
    df = pd.read_csv(caminho)
    df = df[df['RestingBP'] > 0]
    # Substituir zeros pela mediana
    df['Cholesterol'] = df['Cholesterol'].replace(0, df['Cholesterol'].median())
    return df

def obter_preprocessor(colunas_numericas, colunas_categoricas, colunas_pass_through):
    """Cria e retorna o ColumnTransformer para o pré-processamento (classificação)."""
    pipeline_numerico = Pipeline(steps=[
        ('imputer', KNNImputer(n_neighbors=5)), 
        ('scaler', RobustScaler())                   
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
    return preprocessor

def obter_preprocessor_regressao(colunas_numericas, colunas_categoricas, colunas_pass_through):
    """Cria e retorna o ColumnTransformer para o pré-processamento (regressão)."""
    pipeline_numerico = Pipeline(steps=[
        ('scaler', RobustScaler())
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
    return preprocessor

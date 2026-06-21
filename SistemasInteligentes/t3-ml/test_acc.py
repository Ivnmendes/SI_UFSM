import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.impute import KNNImputer
from sklearn.preprocessing import MinMaxScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score

df = pd.read_csv('data/heart.csv')
df = df[df['RestingBP'] > 0]
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
    ('imputer', KNNImputer(n_neighbors=5)), 
    ('scaler', MinMaxScaler())                   
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

X_train_proc = preprocessor.fit_transform(X_train)
X_test_proc = preprocessor.transform(X_test)

mlp = MLPClassifier(
    hidden_layer_sizes=(64, 32), 
    activation='relu',           
    solver='adam',               
    learning_rate_init=0.001,    
    max_iter=500,                
    batch_size=32,               
    random_state=42,
    early_stopping=True
)

mlp.fit(X_train_proc, y_train)
y_pred = mlp.predict(X_test_proc)
print("New Accuracy:", accuracy_score(y_test, y_pred))

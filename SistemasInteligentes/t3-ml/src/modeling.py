import numpy as np
from sklearn.neural_network import MLPClassifier, MLPRegressor
from sklearn.metrics import (accuracy_score, precision_score, recall_score, 
                             f1_score, roc_auc_score, confusion_matrix, 
                             mean_absolute_error, mean_squared_error, r2_score)

def treinar_e_avaliar_mlp(X_train, X_test, y_train, y_test, nome_modelo):
    """Treina e avalia um classificador MLP com os dados fornecidos."""
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
    
    mlp.fit(X_train, y_train)
    
    y_pred = mlp.predict(X_test)
    y_prob = mlp.predict_proba(X_test)[:, 1]
    
    acc = accuracy_score(y_test, y_pred)
    prec = precision_score(y_test, y_pred)
    rec = recall_score(y_test, y_pred)
    f1 = f1_score(y_test, y_pred)
    roc_auc = roc_auc_score(y_test, y_prob)
    cm = confusion_matrix(y_test, y_pred)
    
    print(f"\n--- RESULTADOS: {nome_modelo} ---")
    print(f"Accuracy:  {acc:.4f}")
    print(f"Precision: {prec:.4f}")
    print(f"Recall:    {rec:.4f}")
    print(f"F1-Score:  {f1:.4f}")
    print(f"ROC-AUC:   {roc_auc:.4f}")
    print("Matriz de Confusão:")
    print(cm)
    
    return mlp

def treinar_e_avaliar_regressao(X_train, X_test, y_train, y_test):
    """Treina e avalia um regressor MLP com os dados fornecidos."""
    mlp_reg = MLPRegressor(
        hidden_layer_sizes=(64, 32), 
        activation='relu',
        solver='adam',
        learning_rate_init=0.01, 
        max_iter=1000,
        batch_size=32,
        random_state=42,
        early_stopping=True
    )

    mlp_reg.fit(X_train, y_train)
    y_pred = mlp_reg.predict(X_test)

    mae = mean_absolute_error(y_test, y_pred)
    mse = mean_squared_error(y_test, y_pred)
    rmse = np.sqrt(mse)
    r2 = r2_score(y_test, y_pred)

    print(f"\n--- RESULTADOS REGRESSÃO (Alvo: MaxHR) ---")
    print(f"MAE:  {mae:.2f}")
    print(f"MSE:  {mse:.2f}")
    print(f"RMSE: {rmse:.2f}")
    print(f"R²:   {r2:.4f}")
    
    return mlp_reg

def avaliar_regularizacao(X_train, X_test, y_train, y_test):
    """Avalia o impacto da regularização L2 num modelo MLPClassifier."""
    mlp_sem_reg = MLPClassifier(
        hidden_layer_sizes=(113,),
        activation='relu',
        solver='adam',
        learning_rate_init=0.00377,
        batch_size=16,
        max_iter=500,
        alpha=0.0001, # L2 fraco
        random_state=42
    )
    mlp_sem_reg.fit(X_train, y_train)
    acc_sem_reg = accuracy_score(y_test, mlp_sem_reg.predict(X_test))

    mlp_com_reg = MLPClassifier(
        hidden_layer_sizes=(113,),
        activation='relu',
        solver='adam',
        learning_rate_init=0.00377,
        batch_size=16,
        max_iter=500,
        alpha=0.5, # L2 forte
        random_state=42
    )
    mlp_com_reg.fit(X_train, y_train)
    acc_com_reg = accuracy_score(y_test, mlp_com_reg.predict(X_test))

    print(f"\nAcurácia SEM Regularização L2: {acc_sem_reg:.4f}")
    print(f"Acurácia COM Regularização L2: {acc_com_reg:.4f}")
    
    return mlp_sem_reg, mlp_com_reg

import optuna
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score

def otimizar_hiperparametros(X_train, X_test, y_train, y_test, n_trials=50):
    """Utiliza o Optuna para encontrar os melhores hiperparâmetros para o MLPClassifier."""
    def objective(trial):
        n_camadas = trial.suggest_int('n_camadas', 1, 3)
        camadas = []
        for i in range(n_camadas):
            n_neuronios = trial.suggest_int(f'n_neuronios_c{i}', 16, 128)
            camadas.append(n_neuronios)
            
        learning_rate = trial.suggest_float('learning_rate', 1e-4, 1e-2, log=True)
        batch_size = trial.suggest_categorical('batch_size', [16, 32, 64])
        
        mlp_opt = MLPClassifier(
            hidden_layer_sizes=tuple(camadas),
            activation='relu',
            solver='adam',
            learning_rate_init=learning_rate,
            batch_size=batch_size,
            max_iter=500,
            random_state=42,
            early_stopping=True
        )
        
        mlp_opt.fit(X_train, y_train)
        y_pred_opt = mlp_opt.predict(X_test)
        return accuracy_score(y_test, y_pred_opt)

    optuna.logging.set_verbosity(optuna.logging.WARNING)
    estudo = optuna.create_study(direction='maximize')
    print(f"Executando {n_trials} testes de otimização (trials)...")
    estudo.optimize(objective, n_trials=n_trials)

    print("\n--- RESULTADOS DA OTIMIZAÇÃO ---")
    print(f"Melhor Acurácia encontrada: {estudo.best_value:.4f}")
    print("Melhores Hiperparâmetros:")
    for key, value in estudo.best_params.items():
        print(f"  {key}: {value}")

    print(f"\nAcurácia Original (Etapa 4): 0.8370")
    print(f"Acurácia Otimizada:        {estudo.best_value:.4f}")
    
    return estudo

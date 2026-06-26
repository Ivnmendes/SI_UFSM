import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error, mean_absolute_error
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, LSTM, Dropout
import yfinance as yf
import datetime

def create_dataset(dataset, look_back=1):
    X, Y = [], []
    for i in range(len(dataset)-look_back-1):
        a = dataset[i:(i+look_back), 0]
        X.append(a)
        Y.append(dataset[i + look_back, 0])
    return np.array(X), np.array(Y)

def main():
    print("Baixando dados das ações da Apple (AAPL)...")
    end_date = datetime.date.today()
    start_date = end_date - datetime.timedelta(days=5*365)
    
    df = yf.download('AAPL', start=start_date, end=end_date)
    
    data = df['Close'].values
    
    scaler = MinMaxScaler(feature_range=(0, 1))
    scaled_data = scaler.fit_transform(data)
    
    training_data_len = int(np.ceil(len(data) * .8))
    train_data = scaled_data[0:int(training_data_len), :]
    
    look_back = 60
    
    x_train, y_train = create_dataset(train_data, look_back)
    x_train = np.reshape(x_train, (x_train.shape[0], x_train.shape[1], 1))
    
    print("Construindo o modelo LSTM...")
    model = Sequential()
    model.add(LSTM(50, return_sequences=True, input_shape=(x_train.shape[1], 1)))
    model.add(Dropout(0.2))
    model.add(LSTM(50, return_sequences=False))
    model.add(Dropout(0.2))
    model.add(Dense(25))
    model.add(Dense(1))
    
    model.compile(optimizer='adam', loss='mean_squared_error')
    
    print("Treinando o modelo...")
    model.fit(x_train, y_train, batch_size=32, epochs=10)
    
    test_data = scaled_data[training_data_len - look_back: , :]
    x_test, y_test_scaled = create_dataset(test_data, look_back)
    x_test = np.reshape(x_test, (x_test.shape[0], x_test.shape[1], 1))
    
    y_test = data[training_data_len+1:len(data)]
    
    print("Realizando previsões...")
    predictions = model.predict(x_test)
    predictions = scaler.inverse_transform(predictions)
    
    rmse = np.sqrt(mean_squared_error(y_test, predictions))
    mse = mean_squared_error(y_test, predictions)
    mae = mean_absolute_error(y_test, predictions)
    
    print(f"Resultados da Avaliação:")
    print(f"MSE: {mse:.4f}")
    print(f"RMSE: {rmse:.4f}")
    print(f"MAE: {mae:.4f}")
    
    train = df[:training_data_len].copy()
    valid = df[training_data_len+1:].copy()
    valid['Predictions'] = predictions
    
    plt.figure(figsize=(16,8))
    plt.title('Previsão de Preço das Ações da Apple (AAPL) usando LSTM')
    plt.xlabel('Data', fontsize=12)
    plt.ylabel('Preço de Fechamento (USD)', fontsize=12)
    plt.plot(train['Close'], label='Dados de Treino')
    plt.plot(valid['Close'], label='Preço Real (Teste)')
    plt.plot(valid['Predictions'], label='Previsões (LSTM)')
    plt.legend(loc='lower right')
    plt.grid(True, linestyle='--', alpha=0.6)
    
    plt.savefig('previsao_lstm.png', bbox_inches='tight', dpi=300)
    print("Gráfico salvo como 'previsao_lstm.png'")
    
if __name__ == "__main__":
    main()

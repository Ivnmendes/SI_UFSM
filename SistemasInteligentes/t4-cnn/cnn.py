import numpy as np
import tensorflow as tf
from tensorflow.keras.datasets import cifar10
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout, BatchNormalization
from tensorflow.keras.utils import to_categorical
from sklearn.metrics import classification_report, accuracy_score
import matplotlib.pyplot as plt

print("Carregando dataset CIFAR-10...")
(x_train, y_train), (x_test, y_test) = cifar10.load_data()

classes_desejadas = [0, 1, 8, 9]

def filter_classes(x, y, classes):
    mask = np.isin(y, classes).flatten()
    return x[mask], y[mask]

x_train_filtered, y_train_filtered = filter_classes(x_train, y_train, classes_desejadas)
x_test_filtered, y_test_filtered = filter_classes(x_test, y_test, classes_desejadas)

mapeamento = {0: 0, 1: 1, 8: 2, 9: 3}
y_train_mapped = np.vectorize(mapeamento.get)(y_train_filtered)
y_test_mapped = np.vectorize(mapeamento.get)(y_test_filtered)

x_train_norm = x_train_filtered.astype('float32') / 255.0
x_test_norm = x_test_filtered.astype('float32') / 255.0

y_train_categorical = to_categorical(y_train_mapped, num_classes=4)
y_test_categorical = to_categorical(y_test_mapped, num_classes=4)

def criar_modelo_1():
    model = Sequential([
        Conv2D(32, (3, 3), activation='relu', input_shape=(32, 32, 3)),
        MaxPooling2D((2, 2)),
        Flatten(),
        Dense(64, activation='relu'),
        Dense(4, activation='softmax')
    ])
    model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
    return model

def criar_modelo_2():
    model = Sequential([
        Conv2D(32, (3, 3), activation='relu', input_shape=(32, 32, 3)),
        MaxPooling2D((2, 2)),
        Conv2D(64, (3, 3), activation='relu'),
        MaxPooling2D((2, 2)),
        Flatten(),
        Dense(128, activation='relu'),
        Dropout(0.5),
        Dense(4, activation='softmax')
    ])
    model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
    return model

def criar_modelo_3():
    model = Sequential([
        Conv2D(32, (3, 3), activation='relu', padding='same', input_shape=(32, 32, 3)),
        BatchNormalization(),
        Conv2D(32, (3, 3), activation='relu'),
        MaxPooling2D((2, 2)),
        Dropout(0.25),
        
        Conv2D(64, (3, 3), activation='relu', padding='same'),
        BatchNormalization(),
        Conv2D(64, (3, 3), activation='relu'),
        MaxPooling2D((2, 2)),
        Dropout(0.25),
        
        Flatten(),
        Dense(256, activation='relu'),
        Dropout(0.5),
        Dense(4, activation='softmax')
    ])
    model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
    return model

nomes_modelos = ['CNN Simples', 'CNN Intermediária (com Dropout)', 'CNN Profunda (com Batch Normalization)']
modelos = [criar_modelo_1(), criar_modelo_2(), criar_modelo_3()]
historicos = []

for i, model in enumerate(modelos):
    print(f"\n{'='*50}")
    print(f"--- Treinando {nomes_modelos[i]} ---")
    print(f"{'='*50}")
    
    history = model.fit(
        x_train_norm, y_train_categorical,
        epochs=15, 
        batch_size=64,
        validation_split=0.2,
        verbose=1
    )
    historicos.append(history)
    
    y_pred = model.predict(x_test_norm)
    y_pred_classes = np.argmax(y_pred, axis=1)
    
    print(f"\nResultados para {nomes_modelos[i]}:")
    target_names = ['Avião (0)', 'Automóvel (1)', 'Navio (8)', 'Caminhão (9)']
    report = classification_report(y_test_mapped, y_pred_classes, target_names=target_names)
    print(report)

plt.figure(figsize=(15, 5))
for i, history in enumerate(historicos):
    plt.subplot(1, 3, i+1)
    plt.plot(history.history['accuracy'], label='Treino Acc')
    plt.plot(history.history['val_accuracy'], label='Val Acc')
    plt.title(nomes_modelos[i])
    plt.xlabel('Época')
    plt.ylabel('Acurácia')
    plt.legend()
plt.tight_layout()
plt.savefig('graficos_modelos.png')
print("\nGráficos de treinamento salvos em 'graficos_modelos.png'")

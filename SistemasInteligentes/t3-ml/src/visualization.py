import matplotlib.pyplot as plt

def plotar_curvas_regularizacao(mlp_sem_reg, mlp_com_reg, caminho_salvar='grafico_regularizacao.png'):
    """Gera e salva um gráfico comparando as curvas de aprendizado com e sem regularização L2."""
    plt.figure(figsize=(10, 5))
    plt.plot(mlp_sem_reg.loss_curve_, label='Sem Regularização (L2 = 0.0001)', color='red')
    plt.plot(mlp_com_reg.loss_curve_, label='Com Regularização (L2 = 0.5)', color='blue')
    plt.title('Curvas de Aprendizado: Impacto da Regularização L2 (Weight Decay)')
    plt.xlabel('Épocas')
    plt.ylabel('Loss (Erro de Treinamento)')
    plt.legend()
    plt.grid(True)
    plt.savefig(caminho_salvar, dpi=300, bbox_inches='tight')
    print(f"\nGráfico salvo como {caminho_salvar}")

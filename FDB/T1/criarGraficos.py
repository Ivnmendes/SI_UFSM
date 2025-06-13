import pandas as pd
import mysql.connector
from mysql.connector import Error
import seaborn as sns
import matplotlib.pyplot as plt
from pathlib import Path

def gerar_grafico_gols_paises(conn, out):
    query_gols_paises = """
        SELECT p.nome as Pais, sum(j.totalGols) as totalGols FROM Pais p
            JOIN Jogador j on p.idPais = j.idPais
            GROUP BY p.nome
            ORDER BY totalGols DESC
            LIMIT 5;
    """

    df_gols = pd.read_sql_query(query_gols_paises, conn)

    plt.figure(figsize=(12, 7))
    grafico = sns.barplot(
        y='totalGols', 
        x='Pais', 
        data=df_gols, 
        palette='viridis',
    )

    for container in grafico.containers:
        grafico.bar_label(
            container, 
            fmt='%.0f',        
            fontsize=10, 
            color='black', 
            padding=3
        )
    
    grafico.set_title('Top 5 Países por Total de Gols', fontsize=16)
    grafico.set_ylabel('Total de Gols', fontsize=12)
    grafico.set_xlabel('País', fontsize=12)
    grafico.set_ylim(0, df_gols['totalGols'].max() * 1.1)

    plt.tight_layout()
    nome_arquivo = 'gols_por_pais.png'
    plt.savefig(out / nome_arquivo)

def gerar_grafico_media_gols(conn, out):
    query_media_gols = """
        SELECT j.nome, (j.totalGols / j.totalPartidas) as mediaGols FROM Jogador j
            WHERE j.totalPartidas > 10
            ORDER BY mediaGols DESC
            LIMIT 10;
    """

    df_gols = pd.read_sql_query(query_media_gols, conn)

    plt.figure(figsize=(12, 7))
    grafico = sns.barplot(
        y='mediaGols', 
        x='nome', 
        data=df_gols, 
        palette='viridis',
    )

    for container in grafico.containers:
        grafico.bar_label(
            container, 
            fmt='%.2f',        
            fontsize=10, 
            color='black', 
            padding=3
        )

    grafico.set_title('Top 10 jogadores com maior média de gols (Disputaram mais que 10 partidas)', fontsize=16)
    grafico.set_ylabel('Media de Gols', fontsize=12)
    grafico.set_xlabel('País', fontsize=12)
    grafico.set_ylim(0, df_gols['mediaGols'].max() * 1.1)

    plt.tight_layout()
    nome_arquivo = out / 'media_gols.png'
    plt.savefig(nome_arquivo)
    
def gerar_grafico_titulos_paises(conn, out):
    query_titulos_paises = """
        SELECT P.nome AS Pais, COUNT(PA.idPartida) AS Titulos FROM Partida AS PA
            JOIN Pais AS P ON PA.idGanhador = P.idPais
            WHERE PA.fase = 'Final'
            GROUP BY P.nome
            ORDER BY Titulos DESC;
    """

    df_paises = pd.read_sql_query(query_titulos_paises, conn)

    plt.figure(figsize=(12, 7))
    grafico = sns.barplot(
        y='Titulos', 
        x='Pais', 
        data=df_paises, 
        palette='viridis',
    )

    for container in grafico.containers:
        grafico.bar_label(
            container, 
            fmt='%.0f',        
            fontsize=10, 
            color='black', 
            padding=3
        )

    grafico.set_title('Titulos por pais', fontsize=16)
    grafico.set_ylabel('Titulos', fontsize=12)
    grafico.set_xlabel('Pais', fontsize=12)
    grafico.set_ylim(0, df_paises['Titulos'].max() * 1.1)

    plt.tight_layout()
    nome_arquivo = out / 'titulos_pais.png'
    plt.savefig(nome_arquivo)

def gerar_grafico_vices_paises(conn, out):
    query_titulos_paises = """
        SELECT P.nome AS Pais, COUNT(PA.idPartida) AS Vices FROM Partida AS PA
            JOIN Pais AS P ON PA.idPerdedor = P.idPais
            WHERE PA.fase = 'Final'
            GROUP BY P.nome
            ORDER BY Vices DESC;
    """

    df_paises = pd.read_sql_query(query_titulos_paises, conn)

    plt.figure(figsize=(12, 7))
    grafico = sns.barplot(
        y='Vices', 
        x='Pais', 
        data=df_paises, 
        palette='viridis',
    )

    for container in grafico.containers:
        grafico.bar_label(
            container, 
            fmt='%.0f',        
            fontsize=10, 
            color='black', 
            padding=3
        )

    grafico.set_title('Vices por pais', fontsize=16)
    grafico.set_ylabel('Vices', fontsize=12)
    grafico.set_xlabel('Pais', fontsize=12)
    grafico.set_ylim(0, df_paises['Vices'].max() * 1.1)

    plt.tight_layout()
    nome_arquivo = out / 'vices_pais.png'
    plt.savefig(nome_arquivo)


if __name__ == "__main__":
    output_dir = Path('./graficos/')
    output_dir.mkdir(parents=True, exist_ok=True)
    try:
        conexao_db = mysql.connector.connect(
            host='localhost',
            user='copa_user',
            password='Senha12345678#',
            database='CopaDoMundo'
        )

        gerar_grafico_gols_paises(conexao_db, output_dir)
        gerar_grafico_media_gols(conexao_db, output_dir)
        gerar_grafico_titulos_paises(conexao_db, output_dir)
        gerar_grafico_vices_paises(conexao_db, output_dir)

    except Error as e:
        print(f"Erro na conexão com o MySQL: {e}")
    finally:
        if 'conexao_db' in locals() and conexao_db.is_connected():
            conexao_db.close()
            print("\nConexão com o MySQL foi fechada.")
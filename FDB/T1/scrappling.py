import pandas as pd
# import re
import requests
import os
from io import StringIO
from pathlib import Path
import mysql.connector
from mysql.connector import Error

DATA_DIR = Path("./dados")

PAGINAS = {
    'artilheiros': {
        'url': 'https://pt.wikipedia.org/wiki/Lista_de_artilheiros_da_Copa_do_Mundo_FIFA',
        'arquivo': DATA_DIR / 'artilheiros.html'
    },
    'edicoes': {
        'url': 'https://pt.wikipedia.org/wiki/Copa_do_Mundo_FIFA',
        'arquivo': DATA_DIR / 'edicoes.html'
    }
}

MAPA_CORRECOES = {
    'Polónia': 'Polônia',
    'Alemanha Ocidental': 'Alemanha',
    'União Soviética': 'Rússia'
}
def get_html(url: str, local_path: Path) -> str | None:
    """
    Busca o HTML de um arquivo local se ele existir.
    Caso contrário, baixa da URL e salva localmente.
    """
    if local_path.exists():
        return local_path.read_text(encoding='utf-8')
    else:
        try:
            headers = {'User-Agent': 'Mozilla/5.0'}
            response = requests.get(url, headers=headers, timeout=10)
            response.raise_for_status()
            html_content = response.text
            
            local_path.write_text(html_content, encoding='utf-8')
            return html_content
            
        except requests.exceptions.RequestException as e:
            print(f" Erro ao tentar acessar a URL: {e}")
            return None

def scrap_artilheiros(html_content: str) -> pd.DataFrame | None:
    """Extrai e limpa a tabela de artilheiros do conteúdo HTML."""
    if not html_content:
        return None
    
    try:
        lista_de_tabelas = pd.read_html(StringIO(html_content))
        df = lista_de_tabelas[1]

        if 'Pos.' in df.columns:
            df = df.drop(columns=['Pos.'])

        for col in ['Gols', 'Jogos', 'Média']:
            df[col] = pd.to_numeric(df[col], errors='coerce')
        
        df['Média'] = df['Média'] / 100

        return df
    except (IndexError, ValueError) as e:
        print(f"Não foi possível encontrar ou processar a tabela de artilheiros: {e}")
        return None

def scrap_edicoes(html_content: str) -> pd.DataFrame | None:
    """Extrai e limpa a tabela de edições da Copa do Mundo do conteúdo HTML."""
    if not html_content:
        return None
        
    try:
        lista_de_tabelas = pd.read_html(StringIO(html_content))
        df = lista_de_tabelas[3]
        
        df_limpo = df[[0, 1, 3, 4, 5, 7, 8, 9]]
        
        colunas_corretas = [
            'Ano', 'Sede', 'Campeao', 'Placar_Final', 'Vice_Campeao',
            'Terceiro_Lugar', 'Placar_Disputa_Terceiro', 'Quarto_Lugar'
        ]
        df_limpo.columns = colunas_corretas

        df_limpo = df_limpo.iloc[2:].copy()

        df_limpo = df_limpo[~df_limpo['Sede'].str.contains("Edições canceladas", na=False)]

        df_limpo['Ano'] = df_limpo['Ano'].str.extract(r'(\d{4})')

        df_limpo = df_limpo.dropna(subset=['Ano'])
        
        df_limpo['Ano'] = pd.to_numeric(df_limpo['Ano']).astype(int)
        df_limpo = df_limpo[df_limpo['Ano'] <= 2022]

        df_limpo = df_limpo.reset_index(drop=True)
        
        return df_limpo
        
    except (IndexError, ValueError) as e:
        print(f"Não foi possível encontrar ou processar a tabela de edições: {e}")
        return None

def popular_banco(conn, df_artilheiros, df_edicoes):
    """
    Usa os DataFrames para popular as tabelas do banco de dados MySQL.
    """
    if conn is None or not conn.is_connected():
        print("Conexão com o banco de dados falhou. Abortando.")
        return
        
    cursor = conn.cursor()

    # etapa usada só no debug
    cursor.execute("DELETE FROM ParticipacaoJogador")
    cursor.execute("DELETE FROM Jogador")
    cursor.execute("DELETE FROM EdicaoSedes")
    cursor.execute("DELETE FROM Edicoes")
    cursor.execute("DELETE FROM Paises")

    print("\n--- COLETANDO PAÍSES ---")
    paises_set = set()
    
    paises_set.update(df_artilheiros['Seleção'].dropna().unique())
    
    for coluna in ['Sede', 'Campeao', 'Vice_Campeao', 'Terceiro_Lugar', 'Quarto_Lugar']:
        paises_split = df_edicoes[coluna].str.split(' / ', expand=True).stack()
        paises_set.update(paises_split.dropna().unique())
    
    paises_set.discard('')
    
    print("\n--- INSERINDO PAÍSES NO BANCO ---")
    sql_insert_pais = "INSERT IGNORE INTO Paises (nome) VALUES (%s)"
    lista_paises_tuplas = [(pais,) for pais in sorted(list(paises_set))]
    cursor.executemany(sql_insert_pais, lista_paises_tuplas)
    conn.commit()
    print(f"{cursor.rowcount} novos países inseridos na tabela 'Paises'.")

    cursor.execute("SELECT idPais, nome FROM Paises")
    mapa_paises = {nome: id for id, nome in cursor.fetchall()}

    print("\n--- INSERINDO EDIÇÕES NO BANCO ---")
    sql_insert_edicao = """
    INSERT IGNORE INTO Edicoes (ano, idCampeao, idViceCampeao, idTerceiro, idQuarto)
    VALUES (%s, %s, %s, %s, %s)
    """
    edicoes_para_inserir = []
    for edicao in df_edicoes.itertuples():
        ano = int(edicao.Ano)
        id_campeao = mapa_paises.get(edicao.Campeao)
        id_vice = mapa_paises.get(edicao.Vice_Campeao)
        id_terceiro = mapa_paises.get(edicao.Terceiro_Lugar)
        id_quarto = mapa_paises.get(edicao.Quarto_Lugar)
        edicoes_para_inserir.append((ano, id_campeao, id_vice, id_terceiro, id_quarto))

    cursor.executemany(sql_insert_edicao, edicoes_para_inserir)
    conn.commit()
    print(f"{cursor.rowcount} novas edições inseridas na tabela 'Edicoes'.")
    
    cursor.execute("SELECT idEdicao, ano FROM Edicoes")
    mapa_edicoes = {ano: id for id, ano in cursor.fetchall()}

    print("\n--- VINCULANDO SEDES ÀS EDIÇÕES ---")
    sql_insert_sede = "INSERT IGNORE INTO EdicaoSedes (idEdicao, idPais) VALUES (%s, %s)"
    sedes_para_inserir = []
    for edicao in df_edicoes.itertuples():
        id_edicao_atual = mapa_edicoes.get(edicao.Ano)
        if id_edicao_atual:
            paises_sede = edicao.Sede.split(' / ')
            for pais_nome in paises_sede:
                id_pais_sede = mapa_paises.get(pais_nome.strip())
                if id_pais_sede:
                    sedes_para_inserir.append((id_edicao_atual, id_pais_sede))

    cursor.executemany(sql_insert_sede, sedes_para_inserir)
    conn.commit()
    print(f"{cursor.rowcount} novos registros de sede inseridos na tabela 'EdicaoSedes'.")

    print("\n--- INSERINDO JOGADORES NO BANCO ---")
    sql_insert_jogador = """
    INSERT IGNORE INTO Jogador (nome, idPais, totalGols, totalPartidas)
    VALUES (%s, %s, %s, %s)
    """
    jogadores_para_inserir = []
    for jogador in df_artilheiros.itertuples():
        id_pais = mapa_paises.get(jogador.Seleção)
        jogadores_para_inserir.append((jogador.Jogador, id_pais, jogador.Gols, jogador.Jogos))
    
    cursor.executemany(sql_insert_jogador, jogadores_para_inserir)
    conn.commit()
    print(f"{cursor.rowcount} novos jogadores inseridos na tabela 'Jogador'.")

    cursor.execute("SELECT idJogador, nome FROM Jogador")
    mapa_jogadores = {nome: id for id, nome in cursor.fetchall()}

    print("\n--- INSERINDO PARTICIPAÇÕES DOS JOGADORES ---")
    sql_insert_participacao = "INSERT IGNORE INTO ParticipacaoJogador (idEdicao, idJogador) VALUES (%s, %s)"
    participacoes_para_inserir = []
    for jogador in df_artilheiros.itertuples():
        id_jogador = mapa_jogadores.get(jogador.Jogador)
        anos_torneios = str(jogador.Torneios).split(',')
        
        for ano_str in anos_torneios:
            try:
                ano = int(ano_str.strip())
                id_edicao = mapa_edicoes.get(ano)
                if id_jogador and id_edicao:
                    participacoes_para_inserir.append((id_edicao, id_jogador))
            except ValueError:
                continue

    cursor.executemany(sql_insert_participacao, participacoes_para_inserir)
    conn.commit()
    print(f"{cursor.rowcount} novas participações inseridas na tabela 'ParticipacaoJogador'.")
    
    cursor.close()

if __name__ == "__main__":
    DATA_DIR.mkdir(exist_ok=True)
    
    pd.set_option('display.max_columns', None)
    pd.set_option('display.max_rows', None)

    info_artilheiros = PAGINAS['artilheiros']
    html_artilheiros = get_html(info_artilheiros['url'], info_artilheiros['arquivo'])
    df_artilheiros = scrap_artilheiros(html_artilheiros)

    if df_artilheiros is None:
        raise ValueError("Não foi possível extrair a tabela de artilheiros.")

    info_edicoes = PAGINAS['edicoes']
    html_edicoes = get_html(info_edicoes['url'], info_edicoes['arquivo'])
    df_edicoes = scrap_edicoes(html_edicoes)

    if df_edicoes is None or df_artilheiros is None:
        raise ValueError("Não foi possível extrair a tabela de edições.")
    
    try:
        df_artilheiros['Seleção'] = df_artilheiros['Seleção'].str.strip()
        colunas_paises_edicoes = ['Sede', 'Campeao', 'Vice_Campeao', 'Terceiro_Lugar', 'Quarto_Lugar']
        for coluna in colunas_paises_edicoes:
            df_edicoes[coluna] = df_edicoes[coluna].str.replace(r'\[.*?\]', '', regex=True).str.strip()
        
        df_artilheiros['Seleção'] = df_artilheiros['Seleção'].replace(MAPA_CORRECOES)
        for coluna in colunas_paises_edicoes:
            df_edicoes[coluna] = df_edicoes[coluna].replace(MAPA_CORRECOES)

        df_edicoes['Sede'] = df_edicoes['Sede'].str.replace('Coreia do Sul  Japão', 'Coreia do Sul / Japão')
        
        print("\n\n--- 🗄️ INICIANDO PROCESSO DE INSERÇÃO NO BANCO DE DADOS ---")
        conexao_db = mysql.connector.connect(
            host='localhost',
            user='copa_user',
            password='Senha12345678#',
            database='CopaDoMundo'
        )
        popular_banco(conexao_db, df_artilheiros, df_edicoes)

    except Error as e:
        print(f"Erro na conexão com o MySQL: {e}")
    finally:
        if 'conexao_db' in locals() and conexao_db.is_connected():
            conexao_db.close()
            print("\nConexão com o MySQL foi fechada.")
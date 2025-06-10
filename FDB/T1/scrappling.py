import pandas as pd
import requests
import os
from io import StringIO
from pathlib import Path

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

def get_html(url: str, local_path: Path) -> str | None:
    """
    Busca o HTML de um arquivo local se ele existir.
    Caso contrário, baixa da URL e salva localmente.
    """
    if local_path.exists():
        print(f" Lendo HTML do arquivo local: {local_path}")
        return local_path.read_text(encoding='utf-8')
    else:
        print(f" Baixando HTML de: {url}")
        try:
            headers = {'User-Agent': 'Mozilla/5.0'}
            response = requests.get(url, headers=headers, timeout=10)
            response.raise_for_status()
            html_content = response.text
            
            local_path.write_text(html_content, encoding='utf-8')
            print(f" HTML salvo em: {local_path}")
            return html_content
            
        except requests.exceptions.RequestException as e:
            print(f" Erro ao tentar acessar a URL: {e}")
            return None

def scrap_artilheiros(html_content: str) -> pd.DataFrame | None:
    """Extrai e limpa a tabela de artilheiros do conteúdo HTML."""
    if not html_content:
        return None
    
    print("🔎 Extraindo e limpando dados dos artilheiros...")
    try:
        lista_de_tabelas = pd.read_html(StringIO(html_content))
        df = lista_de_tabelas[1]

        if 'Pos.' in df.columns:
            df = df.drop(columns=['Pos.'])

        for col in ['Gols', 'Jogos', 'Média']:
            df[col] = pd.to_numeric(df[col], errors='coerce')
        
        df['Média'] = df['Média'] / 100

        print("✅ Tabela de artilheiros extraída e limpa com sucesso.")
        return df
    except (IndexError, ValueError) as e:
        print(f"Não foi possível encontrar ou processar a tabela de artilheiros: {e}")
        return None

def scrap_edicoes(html_content: str) -> pd.DataFrame | None:
    """Extrai a tabela de edições da Copa do Mundo do conteúdo HTML."""
    if not html_content:
        return None
        
    print(" Extraindo dados das edições...")
    try:
        lista_de_tabelas = pd.read_html(StringIO(html_content))
        df_edicoes = lista_de_tabelas[3]
        df_edicoes.columns = df_edicoes.columns.str.replace(r'\[.*?\]', '', regex=True).str.strip()
        print(" Tabela de edições extraída com sucesso.")
        return df_edicoes
    except (IndexError, ValueError) as e:
        print(f" Não foi possível encontrar a tabela de edições: {e}")
        return None

if __name__ == "__main__":
    # DATA_DIR.mkdir(exist_ok=True)
    
    # pd.set_option('display.max_columns', None)
    # pd.set_option('display.max_rows', None)

    # print("\n--- PROCESSANDO ARTILHEIROS ---")
    # info_artilheiros = PAGINAS['artilheiros']
    # html_artilheiros = get_html(info_artilheiros['url'], info_artilheiros['arquivo'])
    # df_artilheiros = scrap_artilheiros(html_artilheiros)
    
    # if df_artilheiros is not None:
    #     print("\n primeiras 5 linhas da tabela de artilheiros:")
    #     print(df_artilheiros)

    print("\n\n--- PROCESSANDO EDIÇÕES ---")
    info_edicoes = PAGINAS['edicoes']
    html_edicoes = get_html(info_edicoes['url'], info_edicoes['arquivo'])
    df_edicoes = scrap_edicoes(html_edicoes)

    if df_edicoes is not None:
        print("\n primeiras 5 linhas da tabela de edições:")
        print(df_edicoes.head())
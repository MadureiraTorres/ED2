"""
ED2-AT04 - Indice Secundario
Disciplina: Estrutura de Dados 2 - EDCO4B
UTFPR - Campus Apucarana

Uso: python3 ED2-AT04-IndiceSecundario-Enzo-Rafael-Andre.py <arq_dados> <arq_consulta> <arq_saida>

Como funciona o indice secundario:
  - O indice e uma estrutura { chave -> [lista de posicoes logicas] }
  - Cada posicao logica e o numero da linha do registro no arquivo de dados
  - Na hora de buscar, o programa usa essas posicoes para ir diretamente
    ao arquivo e ler apenas os registros que interessam (sem carregar tudo)
"""

import sys


# ---------------------------------------------------------------------------
# Estrutura de dados
# ---------------------------------------------------------------------------

class Musica:
    """Representa um registro de musica lido do arquivo de dados."""

    def __init__(self, ano, duracao, titulo, artista, genero, idioma, posicao_logica):
        self.ano = ano.strip()
        self.duracao = duracao.strip()
        self.titulo = titulo.strip()
        self.artista = artista.strip()
        self.genero = genero.strip()
        self.idioma = idioma.strip()
        # posicao logica = numero da linha no arquivo (1 = primeira musica, apos o cabecalho)
        self.posicao_logica = posicao_logica

    def __str__(self):
        return (f"{self.ano}|{self.duracao}|{self.titulo}|"
                f"{self.artista}|{self.genero}|{self.idioma}")


# ---------------------------------------------------------------------------
# Leitura do arquivo de dados
# ---------------------------------------------------------------------------

def ler_cabecalho(linha):
    """
    Extrai os parametros do cabecalho.
    Formato esperado: SIZE=91 TOP=-1 QTDE=46 STATUS=0
    Retorna um dicionario com os valores inteiros.
    """
    parametros = {}
    for parte in linha.strip().split():
        chave, valor = parte.split('=')
        parametros[chave] = int(valor)
    return parametros


def parsear_linha(linha, posicao_logica):
    """
    Converte uma linha do arquivo em um objeto Musica.
    Retorna None se a linha estiver malformada.
    """
    campos = linha.strip().split('|')
    if len(campos) != 6:
        return None  # registro malformado, ignora
    return Musica(
        ano=campos[0],
        duracao=campos[1],
        titulo=campos[2],
        artista=campos[3],
        genero=campos[4],
        idioma=campos[5],
        posicao_logica=posicao_logica
    )


def ler_todas_musicas(caminho_dados):
    """
    Le o arquivo inteiro e retorna (cabecalho, lista_de_musicas).
    Usado apenas para construir o indice secundario (varre o arquivo uma vez).
    """
    with open(caminho_dados, 'r', encoding='utf-8') as arq:
        linhas = arq.readlines()

    if not linhas:
        raise ValueError("Arquivo de dados vazio.")

    cabecalho = ler_cabecalho(linhas[0])
    musicas = []

    # posicao logica comeca em 1 (linha 0 e o cabecalho)
    for posicao_logica, linha in enumerate(linhas[1:], start=1):
        if not linha.strip():
            continue  # ignora linhas em branco
        musica = parsear_linha(linha, posicao_logica)
        if musica:
            musicas.append(musica)

    return cabecalho, musicas


def buscar_registro_por_posicao(caminho_dados, posicao_logica):
    """
    Acessa diretamente o arquivo e retorna o objeto Musica da posicao logica indicada.
    posicao_logica=1 corresponde a primeira musica (linha 2 do arquivo, apos o cabecalho).

    Essa e a essencia do indice secundario: ao inves de carregar tudo em memoria,
    usamos a posicao armazenada no indice para ir direto ao registro no arquivo.
    """
    with open(caminho_dados, 'r', encoding='utf-8') as arq:
        for numero_linha, linha in enumerate(arq):
            # linha 0 e o cabecalho; posicao_logica 1 corresponde a linha 1, etc.
            if numero_linha == posicao_logica:
                return parsear_linha(linha, posicao_logica)
    return None  # posicao nao encontrada


# ---------------------------------------------------------------------------
# Indice secundario
# ---------------------------------------------------------------------------

# Campos validos para indexacao (conforme enunciado)
CAMPOS_VALIDOS = {'ano', 'titulo', 'artista', 'genero', 'idioma'}


def obter_chave(musica, campo):
    """Retorna o valor do campo solicitado normalizado (minusculas) para uso como chave."""
    mapa = {
        'ano':     musica.ano,
        'titulo':  musica.titulo,
        'artista': musica.artista,
        'genero':  musica.genero,
        'idioma':  musica.idioma,
    }
    return mapa[campo].lower()


def construir_indice_secundario(musicas, campo):
    """
    Constroi o indice secundario para o campo informado.

    Estrutura do indice (como deve ser na teoria):
      dict { chave_normalizada -> [lista de posicoes_logicas] }

    Cada entrada do indice armazena apenas a CHAVE e as POSICOES dos registros,
    nao os dados em si. Os dados sao recuperados depois diretamente do arquivo,
    usando as posicoes armazenadas aqui.

    As chaves ficam em minusculas (busca case-insensitive) e o dicionario
    e ordenado alfabeticamente pelas chaves ao final.
    """
    indice = {}  # { chave -> [posicao_logica, ...] }

    for musica in musicas:
        chave = obter_chave(musica, campo)
        if chave not in indice:
            indice[chave] = []
        # armazena apenas a posicao logica, nao o objeto inteiro
        indice[chave].append(musica.posicao_logica)

    # Ordena o indice pelas chaves (criterio de um indice secundario)
    return dict(sorted(indice.items()))


def buscar_no_indice(indice, valor_busca):
    """
    Busca no indice secundario e retorna a lista de posicoes logicas
    correspondentes ao valor informado (case-insensitive).
    Retorna lista vazia se nao encontrar.
    """
    chave = valor_busca.strip().lower()
    return indice.get(chave, [])


# ---------------------------------------------------------------------------
# Leitura do arquivo de consulta
# ---------------------------------------------------------------------------

def ler_consulta(caminho_consulta):
    """
    Le o arquivo de consulta.
    Linha 1: campo do indice (ano, titulo, artista, genero, idioma)
    Linha 2: valor de busca
    Retorna (campo, valor_busca).
    """
    with open(caminho_consulta, 'r', encoding='utf-8') as arq:
        linhas = arq.readlines()

    if len(linhas) < 2:
        raise ValueError(
            "Arquivo de consulta deve ter ao menos duas linhas: campo e valor de busca."
        )

    campo = linhas[0].strip().lower()
    valor_busca = linhas[1].strip()
    return campo, valor_busca


# ---------------------------------------------------------------------------
# Escrita do arquivo de saida
# ---------------------------------------------------------------------------

def escrever_saida(caminho_saida, campo, valor_busca, resultados, erro=None):
    """
    Grava o arquivo de saida com os resultados da consulta.
    Em caso de erro ou nenhum resultado, registra a mensagem adequada.
    """
    with open(caminho_saida, 'w', encoding='utf-8') as arq:
        arq.write(f"Consulta: {campo} = {valor_busca}\n")
        arq.write("-" * 60 + "\n")

        if erro:
            arq.write(f"ERRO: {erro}\n")
            return

        if not resultados:
            arq.write(f"Nenhuma musica encontrada para {campo} = '{valor_busca}'.\n")
            return

        arq.write(f"Total de registros encontrados: {len(resultados)}\n\n")
        for musica in resultados:
            arq.write(str(musica) + "\n")


# ---------------------------------------------------------------------------
# Programa principal
# ---------------------------------------------------------------------------

def main():
    # --- Valida os argumentos de linha de comando ---
    if len(sys.argv) != 4:
        print("Uso: python3 ED2-AT04-IndiceSecundario-Enzo-Rafael-Andre.py "
              "<arq_dados> <arq_consulta> <arq_saida>")
        sys.exit(1)

    caminho_dados    = sys.argv[1]
    caminho_consulta = sys.argv[2]
    caminho_saida    = sys.argv[3]

    # --- Le o arquivo de dados para construir o indice ---
    try:
        cabecalho, musicas = ler_todas_musicas(caminho_dados)
    except FileNotFoundError:
        print(f"ERRO: Arquivo de dados '{caminho_dados}' nao encontrado.")
        sys.exit(1)
    except ValueError as e:
        print(f"ERRO no arquivo de dados: {e}")
        sys.exit(1)

    print(f"Cabecalho lido: {cabecalho}")
    print(f"Total de musicas carregadas: {len(musicas)}")

    # --- Le o arquivo de consulta ---
    try:
        campo, valor_busca = ler_consulta(caminho_consulta)
    except FileNotFoundError:
        print(f"ERRO: Arquivo de consulta '{caminho_consulta}' nao encontrado.")
        sys.exit(1)
    except ValueError as e:
        print(f"ERRO no arquivo de consulta: {e}")
        sys.exit(1)

    # --- Valida o campo informado ---
    if campo not in CAMPOS_VALIDOS:
        mensagem_erro = (
            f"Campo '{campo}' invalido. "
            f"Opcoes validas: {', '.join(sorted(CAMPOS_VALIDOS))}."
        )
        print(f"ERRO: {mensagem_erro}")
        escrever_saida(caminho_saida, campo, valor_busca, [], erro=mensagem_erro)
        sys.exit(1)

    # --- Constroi o indice secundario (chave -> [posicoes]) ---
    indice = construir_indice_secundario(musicas, campo)
    print(f"Indice secundario construido para '{campo}' "
          f"com {len(indice)} chave(s) unica(s).")

    # --- Busca as posicoes logicas no indice ---
    posicoes = buscar_no_indice(indice, valor_busca)
    print(f"Posicoes encontradas para '{valor_busca}': {posicoes}")

    # --- Recupera os registros diretamente do arquivo pelas posicoes ---
    # Aqui esta a diferenca principal: usamos as posicoes do indice para
    # buscar cada registro no arquivo, sem ter os dados guardados em memoria.
    resultados = []
    for posicao in posicoes:
        musica = buscar_registro_por_posicao(caminho_dados, posicao)
        if musica:
            resultados.append(musica)

    print(f"Registros recuperados do arquivo: {len(resultados)}")

    # --- Grava o arquivo de saida ---
    escrever_saida(caminho_saida, campo, valor_busca, resultados)
    print(f"Resultado gravado em '{caminho_saida}'.")


if __name__ == "__main__":
    main()
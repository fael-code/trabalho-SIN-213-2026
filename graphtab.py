# Utilitários para gráficos e tabelas
import os
import matplotlib.pyplot as plt


def ler_arquivo_tempo(caminho_arquivo: str) -> tuple[int, float]:
    """
    Lê um arquivo de tempo e retorna (tamanho, tempo_gasto).

    Aceita arquivos com ou sem a palavra "segundos" na linha do tempo.
    O 'with' fecha o arquivo automaticamente, mesmo se ocorrer um erro.
    """
    with open(caminho_arquivo, 'r') as arq:
        linha_tamanho = arq.readline().strip()
        linha_tempo = arq.readline().strip()

    linha_tempo = linha_tempo.replace("segundos", "").strip()

    tamanho: int = int(linha_tamanho)
    tempo: float = float(linha_tempo)

    return tamanho, tempo


def coletar_tempos_por_tipo(pasta_algoritmo: str, tipo_instancia: str, tamanhos: list[int]) -> dict[int, float]:
    """
    Retorna um dicionário {tamanho: tempo} para um tipo de instância.
    """
    dados: dict = {}
    for tamanho in tamanhos:
        nome_arquivo: str = f"Tempo{tipo_instancia}{tamanho}.txt"
        path: str = os.path.join(pasta_algoritmo, "Tempo", tipo_instancia, nome_arquivo)

        _, tempo = ler_arquivo_tempo(path)
        dados[tamanho] = tempo

    return dados


def coletar_tempos_por_algoritmo(algoritmos: list[str], tipo_instancia: str, tamanhos: list[int]) -> dict[str, dict[int, float]]:
    """
    Retorna um dicionário {algoritmo: {tamanho: tempo}} para um tipo de
    instância fixo, comparando os algoritmos entre si.
    """
    dados: dict = {}

    for algoritmo in algoritmos:
        dados[algoritmo] = coletar_tempos_por_tipo(algoritmo, tipo_instancia, tamanhos)

    return dados


def coletar_todos_os_dados(pasta_algoritmo: str, tamanhos: list[int], tipos: list[str] | None = None) -> dict[str, dict[int, float]]:
    """
    Retorna um dicionário {tipo_instancia: {tamanho: tempo}}.
    Se 'tipos' não for informado, usa Crescente, Decrescente e Random.
    """
    if tipos is None:
        tipos = ['Crescente', 'Decrescente', 'Random']

    dados: dict = {}
    for tipo in tipos:
        dados[tipo] = coletar_tempos_por_tipo(pasta_algoritmo, tipo, tamanhos)

    return dados


def gerar_grafico(dados: dict[str, dict[int, float]], caminho_saida: str, nome_algoritmo: str) -> None:
    """
    Gera e salva um gráfico de linha com uma curva para cada chave de 'dados'
    (tipos de instância ou algoritmos).
    """
    plt.figure()

    for nome, tempo_por_tamanho in dados.items():
        tamanho: list = list(tempo_por_tamanho.keys())
        tempo: list = list(tempo_por_tamanho.values())

        plt.plot(tamanho, tempo, label=nome)

    plt.xscale('log')
    plt.xlabel("Tamanho da Instância")
    plt.ylabel("Tempo (em Segundos)")
    plt.title(f"Tempo de execução - {nome_algoritmo}")
    plt.legend()
    plt.savefig(caminho_saida)
    plt.close()


def gerar_tabela(dados: dict[str, dict[int, float]], caminho_saida: str) -> None:
    """
    Gera e salva uma tabela com uma linha para cada chave de 'dados'
    e uma coluna para cada tamanho de instância.
    """
    linhas = list(dados.keys())
    tamanhos = list(next(iter(dados.values())).keys())

    cell_text = []
    for linha_nome in linhas:
        linha = [f"{dados[linha_nome][tamanho]:.6f}" for tamanho in tamanhos]
        cell_text.append(linha)

    col_labels = [str(tamanho) for tamanho in tamanhos]

    fig, ax = plt.subplots()
    ax.axis('off')

    tabela = ax.table(
        cellText=cell_text,
        rowLabels=linhas,
        colLabels=col_labels,
        loc='center'
    )

    tabela.auto_set_font_size(False)
    tabela.set_fontsize(8)
    tabela.scale(1, 1.5)

    plt.savefig(caminho_saida, bbox_inches='tight', dpi=200)
    plt.close(fig)
import os
import matplotlib.pyplot as plt
import graphtab as gp

algoritmos = ["Insertion Sort", "Selection Sort", "Bubble Sort", "Shell Sort", "Merge Sort", "Quick Sort - First", "Quick Sort - Median", "Heap Sort"]
algoritmos_quick = ["Quick Sort - First", "Quick Sort - Median"]
tipos_instancia = ["Crescente", "Decrescente", "Random"]
tamanhos = [10, 100, 1000, 10000, 100000, 1000000]

opcao = 0
while opcao != 3:
    print("\n===== MENU =====")
    print("1 - Ver gráfico/tabela de um algoritmo específico")
    print("2 - Ver gráfico/tabela comparando todos os algoritmos")
    print("3 - Sair")
    opcao = int(input("Escolha uma opção: "))

    if opcao == 1:
        print("\n--- Escolha o algoritmo ---")
        for i, nome in enumerate(algoritmos, start=1):
            print(f"{i} - {nome}")
        opcao_algoritmo = int(input("Escolha: "))

        if opcao_algoritmo < 1 or opcao_algoritmo > len(algoritmos):
            print("\nOpção de algoritmo inválida!")
            continue

        algoritmo_escolhido = algoritmos[opcao_algoritmo - 1]

        if algoritmo_escolhido in algoritmos_quick:
            dados = gp.coletar_todos_os_dados(algoritmo_escolhido, tamanhos, ["Decrescente", "Crescente"])
        else:
            dados = gp.coletar_todos_os_dados(algoritmo_escolhido, tamanhos)

        pasta_imagens = os.path.join("Imagens", algoritmo_escolhido)
        os.makedirs(pasta_imagens, exist_ok=True)

        caminho_grafico = os.path.join(pasta_imagens, "grafico_tempos.png")
        caminho_tabela = os.path.join(pasta_imagens, "tabela_tempos.png")

        gp.gerar_grafico(dados, caminho_grafico, algoritmo_escolhido)
        gp.gerar_tabela(dados, caminho_tabela)

        print(f"\nGráfico e tabela do algoritmo {algoritmo_escolhido} gerados!")

    elif opcao == 2:
        print("\n--- Escolha o tipo de instância ---")
        for i, tipo in enumerate(tipos_instancia, start=1):
            print(f"{i} - {tipo}")
        opcao_tipo = int(input("Escolha: "))

        if opcao_tipo < 1 or opcao_tipo > len(tipos_instancia):
            print("\nOpção de tipo inválida!")
            continue

        tipo_escolhido = tipos_instancia[opcao_tipo - 1]

        dados_comparativo = gp.coletar_tempos_por_algoritmo(algoritmos, tipo_escolhido, tamanhos)

        pasta_comparativo = os.path.join("Imagens", "Comparativo")
        os.makedirs(pasta_comparativo, exist_ok=True)

        caminho_grafico = os.path.join(pasta_comparativo, f"grafico_{tipo_escolhido}.png")
        caminho_tabela = os.path.join(pasta_comparativo, f"tabela_{tipo_escolhido}.png")

        gp.gerar_grafico(dados_comparativo, caminho_grafico, f"Comparativo - {tipo_escolhido}")
        gp.gerar_tabela(dados_comparativo, caminho_tabela)

        print(f"\nGráfico e tabela comparativos ({tipo_escolhido}) gerados!")

    elif opcao == 3:
        print("\nEncerrando...")

    else:
        print("\nOpção inválida! Tente novamente.")
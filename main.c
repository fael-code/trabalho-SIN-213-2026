#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<limits.h>
#include<windows.h>
#include<direct.h>

#include "funcoes.h"

int main(){

    srand(time(NULL)); 

    int opcao;
    do {
        printf("\n---===== MENU =====---\n");
        printf("1 - Executar algoritmo em um vetor\n");
        printf("2 - Heap Sort e fila de prioridade\n");
        printf("3 - Sair da aplicacao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        if(opcao == 1){

            int opcaoAlgoritmo;
            char nome_algoritmo[30];

            printf("\n---------- Algoritmo ----------\n");
            printf("1 - Insertion Sort\n");
            printf("2 - Selection Sort\n");
            printf("3 - Bubble Sort\n");
            printf("4 - Shell Sort\n");
            printf("5 - Merge Sort\n");
            printf("6 - Quick Sort - First\n");
            printf("7 - Quick Sort - Median\n");
            printf("8 - Heap Sort\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoAlgoritmo);
            switch(opcaoAlgoritmo){
                case 1:
                    strcpy(nome_algoritmo, "Insertion Sort");
                    break;
                case 2:
                    strcpy(nome_algoritmo, "Selection Sort");
                    break;
                case 3:
                    strcpy(nome_algoritmo, "Bubble Sort");
                    break;
                case 4:
                    strcpy(nome_algoritmo, "Shell Sort");
                    break;
                case 5:
                    strcpy(nome_algoritmo, "Merge Sort");
                    break;
                case 6:
                    strcpy(nome_algoritmo, "Quick Sort - First");
                    break;
                case 7: 
                    strcpy(nome_algoritmo, "Quick Sort - Median");
                    break;
                case 8:
                    strcpy(nome_algoritmo, "Heap Sort");
                    break;
                default:
                    printf("\nOpcao de algoritmo invalida!\n");
                    continue;
            }

            criarDiretorios(nome_algoritmo);

            int opcaoTamanho;
            int tamanho;

            printf("\n---------- Tamanho da instancia ----------\n");
            printf("1 - 10\n");
            printf("2 - 100\n");
            printf("3 - 1.000\n");
            printf("4 - 10.000\n");
            printf("5 - 100.000\n");
            printf("6 - 1.000.000\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoTamanho);
            switch(opcaoTamanho){
                case 1: 
                    tamanho = 10;      
                    break;
                case 2: 
                    tamanho = 100;     
                    break;
                case 3: 
                    tamanho = 1000;    
                    break;
                case 4: 
                    tamanho = 10000;   
                    break;
                case 5: 
                    tamanho = 100000;  
                    break;
                case 6: 
                    tamanho = 1000000; 
                    break;
                default:
                    printf("\nOpcao de tamanho invalida!\n");
                    continue;
            }

            int opcaoTipo;
            char tipoInstancia[20];

            printf("\n---------- Tipo de instancia ----------\n");
            printf("1 - Crescente\n");
            printf("2 - Decrescente\n");
            printf("3 - Random\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoTipo);
            switch(opcaoTipo){
                case 1: 
                    strcpy(tipoInstancia, "Crescente");   
                    break;
                case 2: 
                    strcpy(tipoInstancia, "Decrescente"); 
                    break;
                case 3: 
                    strcpy(tipoInstancia, "Random");      
                    break;
                default:
                    printf("\nOpcao de tipo invalida!\n");
                    continue;
            }
            double tempo_execucao = executarOrdenacao(nome_algoritmo, tipoInstancia, tamanho);

            printf("\nExecucao concluida! Arquivo gerado com sucesso.\n");
            printf("Algoritmo: %s | Tamanho: %d | Tipo: %s | Tempo: %lf\n", nome_algoritmo, tamanho, tipoInstancia, tempo_execucao);

        } else if(opcao == 2){

            int opcaoFila;
            do {
                printf("\n---------- Heap Sort e Fila de Prioridade (heap minimo) ----------\n");
                printf("1 - HEAPSORT_MIN (vetor original, apos build e apos heapsort)\n");
                printf("2 - HEAP_MINIMUM\n");
                printf("3 - HEAP_EXTRACT_MIN\n");
                printf("4 - HEAP_DECREASE_KEY (inserir 100 em uma posicao)\n");
                printf("5 - MIN_HEAP_INSERT (inserir 100 no heap)\n");
                printf("0 - Voltar\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcaoFila);

                int base[10] = {6, 4, 3, 56, 76, 43, 24, 96, 87, 1};
                int heap[11];
                int n = 10;
                int k;

                for(k = 0; k < n; k++)
                    heap[k] = base[k];

                switch(opcaoFila){

                    case 1: {
                        printf("\nVETOR ORIGINAL:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);

                        build_min_heap(heap, n);
                        printf("\n\nCHAMADO A BUILD:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);

                        heapSortMin(heap, n);
                        printf("\n\nCHAMADO O HEAPSORT:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);
                        printf("\n");
                        break;
                    }

                    case 2: {
                        build_min_heap(heap, n);
                        printf("\nHEAP CRIADO:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);
                        printf("\nELEMENTO MINIMO: %d\n", heap_minimum(heap));
                        break;
                    }

                    case 3: {
                        build_min_heap(heap, n);
                        printf("\nHEAP ANTES DA EXTRACAO:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);

                        int minimo = heap_extract_min(heap, &n);
                        printf("\nMENOR ELEMENTO RETORNADO: %d\n", minimo);

                        printf("HEAP DEPOIS DA EXTRACAO:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);
                        printf("\n");
                        break;
                    }

                    case 4: {
                        int pos;
                        build_min_heap(heap, n);
                        printf("\nHEAP ANTES:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);

                        printf("\nPosicao para inserir 100 (0 a %d): ", n - 1);
                        scanf("%d", &pos);
                        if(pos < 0 || pos >= n){
                            printf("Posicao invalida!\n");
                            break;
                        }

                        heap[pos] = 100;
                        min_heapfy(heap, n, pos);

                        printf("HEAP DEPOIS:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);
                        printf("\n");
                        break;
                    }

                    case 5: {
                        build_min_heap(heap, n);
                        printf("\nHEAP ANTES:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);

                        min_heap_insert(heap, &n, 100);

                        printf("\nHEAP DEPOIS:\n");
                        for(k = 0; k < n; k++) 
                            printf("%d ", heap[k]);
                        printf("\n");
                        break;
                    }

                    case 0:
                        break;

                    default:
                        printf("\nOpcao invalida! Tente novamente.\n");
                        break;
                }
            } while(opcaoFila != 0);

        } else if(opcao == 3){
            printf("\nEncerrando...\n");
        } else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 3);

    return 0;
}
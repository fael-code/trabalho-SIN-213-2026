#include"funcoes.h"

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>
#include<direct.h>
#include<limits.h>

void trocar(int* maior, int* menor){
    int aux = *maior;
    *maior = *menor;
    *menor = aux;
}

void bubbleSort(int *vetor, int tamanho){
    for (int i = 0; i < tamanho-1; i++) {
        int troca = 0;
        for (int j = 0; j < tamanho-i-1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                trocar(&vetor[j], &vetor[j + 1]);
                troca = 1;
            }
        }
        if (troca == 0)
            break;
    }
}

void insertionSort(int *vetor, int tamanho){
    for(int j=1; j<tamanho; j++){
        
        int chave = vetor[j];
        int i = j - 1;
        while(i >= 0 && vetor[i] > chave){
            vetor[i+1] = vetor[i];
            i = i - 1;
        }
        vetor[i+1] = chave;
    }
}

void selectionSort(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        
        int aux = vetor[i];
        vetor[i] = vetor[min_idx];
        vetor[min_idx] = aux;
    }
}

void shellSort(int *vetor, int tamanho) {
    for (int gap = tamanho / 2; gap > 0; gap /= 2) {
        // Faz a ordenação por inserção para este gap
        for (int i = gap; i < tamanho; i+=1) {
            int aux = vetor[i];
            int j;
            for (j = i; j >= gap && vetor[j-gap] > aux; j-=gap) {
                vetor[j] = vetor[j - gap];
            }
            vetor[j] = aux;
        }
    }
}

void merge(int *vetor, int inicio, int meio, int fim){

    int tamanho = fim - inicio + 1;
    int *auxiliar = (int*)malloc(tamanho * sizeof(int));
    if(auxiliar == NULL){
        printf("Erro ao alocar vetor auxiliar.\n");
        return;
    }

    int i = inicio;
    int j = meio + 1;
    int k = 0;

    while(i <= meio && j <= fim){
        if(vetor[i] <= vetor[j])
            auxiliar[k++] = vetor[i++];
        else
            auxiliar[k++] = vetor[j++];
    }

    while(i <= meio)
        auxiliar[k++] = vetor[i++];

    while(j <= fim)
        auxiliar[k++] = vetor[j++];

    for(k = 0; k < tamanho; k++)
        vetor[inicio + k] = auxiliar[k];

    free(auxiliar);
}

void mergeSort(int *vetor, int inicio, int fim){
    
    if (inicio < fim){
        int meio = floor((inicio+fim)/2);
    
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, inicio, meio, fim);
    }
    
}

int particiona_first(int *vetor, int inicio, int fim){
    // Pivô como inicio do vetor
    int p = vetor[inicio];
    int i = inicio;
    int j = fim;
    while (i < j) {
        while (vetor[i] <= p && i <= fim - 1) {
            i++;
        }
		while (vetor[j] > p && j >= inicio + 1) {
            j--;
        }
        if (i < j) {
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[inicio], &vetor[j]);
    return j;
}

int particiona_median(int *vetor, int inicio, int fim){
    //Pivô como mediana
    int pivo = inicio + (fim - inicio) / 2;
    trocar(&vetor[inicio], &vetor[pivo]);
    int p = vetor[inicio];
    int i = inicio;
    int j = fim;
    while (i < j) {
        while (vetor[i] <= p && i <= fim - 1) {
            i++;
        }
        while (vetor[j] > p && j >= inicio + 1) {
            j--;
        }
        if (i < j) {
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[inicio], &vetor[j]);
    return j;
}

void quickSort_first(int *vetor, int inicio, int fim){
    if (inicio < fim){
        int pi = particiona_first(vetor, inicio, fim);
        quickSort_first(vetor, inicio, pi - 1);
        quickSort_first(vetor, pi + 1, fim);
    }
}

void quickSort_median(int *vetor, int inicio, int fim){
    if (inicio < fim){
        int pi = particiona_median(vetor, inicio, fim);
        quickSort_median(vetor, inicio, pi - 1);
        quickSort_median(vetor, pi + 1, fim);
    }
}

void min_heapfy(int* heap, int tamanho, int i){
    int esquerda = 2*i + 1, direita = 2*i+2, menor = i;
    if(esquerda < tamanho && heap[esquerda] < heap[menor])
        menor = esquerda;
    
    if(direita < tamanho && heap[direita] < heap[menor])
        menor = direita;
    
    if(menor != i){
        trocar(&heap[i], &heap[menor]);
        min_heapfy(heap, tamanho, menor);
    }
}

void max_heapfy(int* heap, int tamanho, int i){
    int esquerda = 2*i + 1, direita = 2*i+2, maior = i;
    if(esquerda < tamanho && heap[esquerda] > heap[maior])
        maior = esquerda;
    
    if(direita < tamanho && heap[direita] > heap[maior])
        maior = direita;
    
    if(maior != i){
        trocar(&heap[i], &heap[maior]);
        max_heapfy(heap, tamanho, maior);
    }
}

void build_min_heap(int* heap, int tamanho){
    for(int i = (tamanho/2) - 1; i>=0; i--)
        min_heapfy(heap, tamanho, i);
}

void build_max_heap(int* heap, int tamanho){
    for(int i = (tamanho/2) - 1; i >= 0; i--)
        max_heapfy(heap, tamanho, i);
}

void heapSortMin(int* heap, int tamanho){
    build_min_heap(heap, tamanho);
    for(int i = tamanho-1; i >= 1; i--){
        trocar(&heap[0], &heap[i]);
        tamanho--;
        min_heapfy(heap, tamanho, 0);
    }
}

void heapSortMax(int* heap, int tamanho){
    build_max_heap(heap, tamanho);
    for(int i = tamanho-1; i >= 1; i--){
        trocar(&heap[0], &heap[i]);
        tamanho--;
        max_heapfy(heap, tamanho, 0);
    }
}

int heap_maximum(int* heap){
    return heap[0];
}

int heap_extract_max(int* heap, int *tamanho){
    if(*tamanho < 1){
        printf("ERRO!\nHEAP UNDER FLOW");
        return -1;
    }
    int max = heap[0];
    heap[1] = heap[(*tamanho)-1];
    (*tamanho)--;
    max_heapfy(heap, *tamanho, 1);
    return max;
}

void heap_increase_key(int *heap, int i, int chave){
    if(chave < heap[i]){
        printf("ERRO!\nCHAVE < A[i]");
        return;
    }
    heap[i] = chave;
    while(i>0 && heap[(i-1)/2]<heap[i]){
        trocar(&heap[i], &heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

void max_heap_insert(int *heap, int *tamanho, int chave){
    (*tamanho)++;
    heap[*tamanho - 1] = INT_MIN;
    heap_increase_key(heap, *tamanho - 1, chave);
}

int  heap_minimum(int *heap){
    return heap[0];
}

int  heap_extract_min(int *heap, int *tamanho){
    if(*tamanho < 1){
        printf("ERRO!\nHEAP UNDER FLOW");
        return -1;
    }
    int min = heap[0];
    heap[0] = heap[(*tamanho)-1];
    (*tamanho)--;
    min_heapfy(heap, *tamanho, 0);
    return min;
}

void heap_decrease_key(int *heap, int i, int chave){
    if(chave > heap[i]){
        printf("ERRO!\nCHAVE > heap[i]");
        return;
    }
    heap[i] = chave;
    while(i>0 && heap[(i-1)/2]>heap[i]){
        trocar(&heap[i], &heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

void min_heap_insert(int *heap, int *tamanho, int chave){
    (*tamanho)++;
    heap[*tamanho - 1] = INT_MAX;
    heap_decrease_key(heap, *tamanho - 1, chave);
}

void criarDiretorios(const char* nome_algoritmo){

    _mkdir(nome_algoritmo);

    char caminho[255];

    /*Arquivos de Entrada*/
    snprintf(caminho, sizeof(caminho), "%s\\Entrada", nome_algoritmo);
    _mkdir(caminho);
    
    snprintf(caminho, sizeof(caminho), "%s\\Entrada\\Crescente", nome_algoritmo);
    _mkdir(caminho);
    snprintf(caminho, sizeof(caminho), "%s\\Entrada\\Decrescente", nome_algoritmo);
    _mkdir(caminho);
    snprintf(caminho, sizeof(caminho), "%s\\Entrada\\Random", nome_algoritmo);
    _mkdir(caminho);

    /*Arquivos de Saida*/
    snprintf(caminho, sizeof(caminho), "%s\\Saida", nome_algoritmo);
    _mkdir(caminho);

    snprintf(caminho, sizeof(caminho), "%s\\Saida\\Crescente", nome_algoritmo);
    _mkdir(caminho);
    snprintf(caminho, sizeof(caminho), "%s\\Saida\\Decrescente", nome_algoritmo);
    _mkdir(caminho);
    snprintf(caminho, sizeof(caminho), "%s\\Saida\\Random", nome_algoritmo);
    _mkdir(caminho);

    /*Arquivos de Tempo*/  
    snprintf(caminho, sizeof(caminho), "%s\\Tempo", nome_algoritmo);
    _mkdir(caminho);

    snprintf(caminho, sizeof(caminho), "%s\\Tempo\\Crescente", nome_algoritmo);
    _mkdir(caminho);
    snprintf(caminho, sizeof(caminho), "%s\\Tempo\\Decrescente", nome_algoritmo);
    _mkdir(caminho);
    snprintf(caminho, sizeof(caminho), "%s\\Tempo\\Random", nome_algoritmo);
    _mkdir(caminho);

}

void montarCaminhoArquivo(char *destino, const char *nome_algoritmo, const char *tipoPasta, const char *tipoInstancia, int tamanho){

    char caminho[255] = "";
    char arquivo[63] = "";

    /*Caminho*/
    strcat(caminho, nome_algoritmo);
    strcat(caminho, "\\");
    strcat(caminho, tipoPasta);
    strcat(caminho, "\\");
    strcat(caminho, tipoInstancia);
    strcat(caminho, "\\");

    /*Arquivo*/
    strcat(arquivo, tipoPasta);
    strcat(arquivo, tipoInstancia);
    char tam_char[9];
    snprintf(tam_char, sizeof(tam_char), "%d", tamanho);
    strcat(arquivo, tam_char);
    strcat(arquivo, ".txt");

    destino[0] = '\0';
    strcat(destino, strcat(caminho, arquivo));

}

void salvarArquivoEntrada(int *vetor, int tamanho,const char* nome_algoritmo ,const char *tipoInstancia){

    char caminho_arq[255];
    montarCaminhoArquivo(caminho_arq, nome_algoritmo, "Entrada", tipoInstancia, tamanho);

    FILE* ponteiro_arq = fopen(caminho_arq, "w");
    if(ponteiro_arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    fprintf(ponteiro_arq, "%d\n", tamanho);
    for(int i = 0; i < tamanho; i++)
        fprintf(ponteiro_arq, "%d\n", vetor[i]);

    fclose(ponteiro_arq);

}

void salvarArquivoSaida(int *vetor, int tamanho,const char* nome_algoritmo ,const char *tipoInstancia){
    
    char caminho_arq[255];
    montarCaminhoArquivo(caminho_arq, nome_algoritmo, "Saida", tipoInstancia, tamanho);

    FILE* ponteiro_arq = fopen(caminho_arq, "w");
    if(ponteiro_arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    fprintf(ponteiro_arq, "%d\n", tamanho);
    for(int i = 0; i < tamanho; i++)
        fprintf(ponteiro_arq, "%d\n", vetor[i]);

    fclose(ponteiro_arq);
}

void salvarArquivoTempo(double tempo, int tamanho,const char* nome_algoritmo, const char *tipoInstancia){

    char caminho_arq[255];
    montarCaminhoArquivo(caminho_arq, nome_algoritmo, "Tempo", tipoInstancia, tamanho);

    FILE* ponteiro_arq = fopen(caminho_arq, "w");
    if(ponteiro_arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(ponteiro_arq, "%d\n", tamanho);
    fprintf(ponteiro_arq, "%lf segundos\n", tempo);

    fclose(ponteiro_arq);
}

double medirTempoExecucao(char *nome_algoritmo, int *vetor, int tamanho){

    clock_t inicio, fim;
    inicio = clock();

    if (strcmp(nome_algoritmo, "Insertion Sort") == 0) {
        insertionSort(vetor, tamanho);
    }else if (strcmp(nome_algoritmo, "Selection Sort") == 0) {
        selectionSort(vetor, tamanho);
    }else if (strcmp(nome_algoritmo, "Bubble Sort") == 0) {
        bubbleSort(vetor, tamanho);
    }else if (strcmp(nome_algoritmo, "Shell Sort") == 0) {
        shellSort(vetor, tamanho);
    }else if (strcmp(nome_algoritmo, "Merge Sort") == 0) {
        mergeSort(vetor, 0, tamanho - 1);
    }else if (strcmp(nome_algoritmo, "Quick Sort - First") == 0) {
        quickSort_first(vetor, 0, tamanho - 1);
    }else if (strcmp(nome_algoritmo, "Quick Sort - Median") == 0) {
        quickSort_median(vetor, 0, tamanho - 1);
    }else if (strcmp(nome_algoritmo, "Heap Sort") == 0) {
        heapSortMin(vetor, tamanho);
    }else{
        printf("Algoritmo '%s' nao reconhecido em medirTempoExecucao.\n", nome_algoritmo);
        return 0.0;
    }

    fim = clock();

    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}


int RNG(){
    /*
        Em C, a função rand() gera um inteiro que é armazenado em 32 bits, 15 desses 32 são usados para armazenar os números gerados pela função aleatória, que no máximo é 32767(ou 111111111111111). Para que seja gerado números maiores que 32767, ao usar rand()<<15, ele empurra o número em binário 15 bits para a esquerda, abrindo espaço para outros 15 bits, após isso, é chamada outra função rand() que irá gerar outro número que ocupara esses 15 bits que foram movidos à esquerda e será  encaixado pelo operador "|" no novo espaço aberto.
    */

    int numero = (rand() << 15) | rand();
    return numero % 1000001;
}

void gerarVetorCrescente(int *vetor, int tamanho){

    for(int i = 0; i < tamanho; i++){
        vetor[i] = i;
    }

}

void gerarVetorDecrescente(int *vetor, int tamanho){

    for(int i = 0; i < tamanho; i++){
        
        int j = tamanho-i-1;
        vetor[i] = j;
    }

}

void gerarVetorRandomico(int *vetor, int tamanho){

    for(int i = 0; i < tamanho; i++){
        vetor[i] = RNG();
    }

}

double executarOrdenacao(const char *nome_algoritmo, const char *tipoInstancia, int tamanho){
    int* vetor = (int*)malloc(tamanho*sizeof(int));
    if(vetor == NULL){
        printf("Erro ao alocar vetor.\n");
        return -1;
    }
    if(strcmp(tipoInstancia, "Crescente") == 0){
        
        gerarVetorCrescente(vetor, tamanho);

    }else if(strcmp(tipoInstancia, "Decrescente") == 0){

        gerarVetorDecrescente(vetor, tamanho);

    }else if(strcmp(tipoInstancia, "Random") == 0){

        gerarVetorRandomico(vetor, tamanho);

    }
    salvarArquivoEntrada(vetor, tamanho, nome_algoritmo, tipoInstancia);
    
    clock_t inicio = 0, fim = 0;
    double tempo;
    if(strcmp(nome_algoritmo, "Insertion Sort") == 0){
        inicio = clock();
        insertionSort(vetor, tamanho);
        fim = clock();
    }else if(strcmp(nome_algoritmo, "Selection Sort") == 0){
        inicio = clock();
        selectionSort(vetor, tamanho);
        fim = clock();
    }else if(strcmp(nome_algoritmo, "Bubble Sort") == 0){
        inicio = clock();
        bubbleSort(vetor, tamanho);
        fim = clock();
    }else if(strcmp(nome_algoritmo, "Shell Sort") == 0){
        inicio = clock();
        shellSort(vetor, tamanho);
        fim = clock();
    }else if(strcmp(nome_algoritmo, "Merge Sort") == 0){
        inicio = clock();
        mergeSort(vetor, 0, tamanho-1);
        fim = clock();
    }else if(strcmp(nome_algoritmo, "Quick Sort - First") == 0){
        inicio = clock();
        quickSort_first(vetor, 0, tamanho-1);
        fim = clock();
    }else if(strcmp(nome_algoritmo, "Quick Sort - Median") == 0){
        inicio = clock();
        quickSort_median(vetor, 0, tamanho-1);
        fim = clock();
    }else if(strcmp(nome_algoritmo, "Heap Sort") == 0){
        inicio = clock();
        heapSortMin(vetor, tamanho);
        fim = clock();
    }
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    salvarArquivoSaida(vetor, tamanho, nome_algoritmo, tipoInstancia);
    salvarArquivoTempo(tempo, tamanho, nome_algoritmo, tipoInstancia);
    free(vetor);
    
    return tempo; 
}

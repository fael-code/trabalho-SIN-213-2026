#ifndef FUNCOES_H

#define FUNCOES_H

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>
#include<direct.h>

void trocar(int* maior, int* menor); /*Feito*/

void insertionSort(int *vetor, int tamanho); /*Feito*/

void selectionSort(int *vetor, int tamanho); /*Feito*/

void bubbleSort(int *vetor, int tamanho); /*Feito*/

void shellSort(int *vetor, int tamanho); /*Feito*/

void mergeSort(int *vetor, int inicio, int fim); /*Feito*/

void merge(int *vetor, int inicio, int meio, int fim); /*Feito*/

int particiona_first(int *vetor, int inicio, int fim); /*Feito*/
void quickSort_first(int *vetor, int inicio, int fim); /*Feito*/

int particiona_median(int *vetor, int inicio, int fim); /*Feito*/
void quickSort_median(int *vetor, int inicio, int fim); /*Feito*/

void min_heapfy(int* vetor, int tamanho, int i); /*Feito*/
void build_min_heap(int* vetor, int tamanho); /*Feito*/
void heapSortMin(int* vetor, int tamanho); /*Feito*/

void max_heapfy(int* vetor, int tamanho, int i); /*Feito*/
void build_max_heap(int* vetor, int tamanho); /*Feito*/
void heapSortMax(int* vetor, int tamanho); /*Feito*/

int  heap_minimum(int *heap);/*Feito*/
int  heap_extract_min(int *heap, int *tamanho);/*Feito*/
void heap_decrease_key(int *heap, int i, int chave);/*Feito*/
void min_heap_insert(int *heap, int *tamanho, int chave);/*Feito*/

int heap_maximum(int* heap); /*Feito*/
int heap_extract_max(int* heap, int* tamanho);/*Feito*/
void heap_incrase_key(int *heap, int i, int chave);/*Feito*/
void max_heap_insert(int *heap, int *tamanho, int chave);/*Feito*/

double executarOrdenacao(const char *nome_algoritmo, const char *tipoInstancia, int tamanho); /*Feito*/

void criarDiretorios(const char* nome_algoritmo); /*Feito*/

void montarCaminhoArquivo(char *destino, const char *nome_algoritmo, const char *tipoPasta, const char *tipoInstancia, int tamanho); /*Feito*/

int RNG(); /*Feito*/

void gerarVetorCrescente(int *vetor, int tamanho); /*Feito*/
void gerarVetorDecrescente(int *vetor, int tamanho); /*Feito*/
void gerarVetorRandomico(int *vetor, int tamanho); /*Feito*/

void salvarArquivoEntrada(int *vetor, int tamanho,const char* nome_algoritmo ,const char *tipoInstancia); /*Feito*/
void salvarArquivoSaida(int *vetor, int tamanho,const char* nome_algoritmo ,const char *tipoInstancia); /*Feito*/
void salvarArquivoTempo(double tempo, int tamanho,const char* nome_algoritmo, const char *tipoInstancia); /*Feito*/

double medirTempoExecucao(char* nome_algoritmo, int *vetor, int tamanho); /*Feito*/

#endif
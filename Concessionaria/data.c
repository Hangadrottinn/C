/******************************************************************************
João Gabriel de Almeida
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


#define MAX_VEICULOS 51 //Por ser apenas números entre 100 e 150

Veiculo veiculos[MAX_VEICULOS];
int contadorVeiculos = 0;



// funções internas ================================================
void inserirVeiculoOrdenado(Veiculo v);
int compararMarca(const void *a, const void *b);
int compararValor(const void *a, const void *b);



//Funções auxiliares ================================================
int compararMarca(const void *a, const void *b) {
    // converte os ponteiros
    const Veiculo *veiculoA = (const Veiculo *)a;
    const Veiculo *veiculoB = (const Veiculo *)b;
    
    // strcmp retorna < 0 se a < b | 0 se a == b > | 0 se a > b
    return strcmp(veiculoA->marca, veiculoB->marca);
}


int compararValor(const void *a, const void *b){
    const Veiculo *veiculoA = (const Veiculo *)a;
    const Veiculo *veiculoB = (const Veiculo *)b;
    
    if (veiculoA->valor < veiculoB->valor) return -1;
    if (veiculoA->valor > veiculoB->valor) return 1;
    return 0;

}

int compararNumero(int numero){
    for (int i = 0; i < contadorVeiculos; i++) {
        if (veiculos[i].numero == numero) {
            return 1;
        }
    }
    return 0;
}



// Funções exemplificadas ================================================
void cadastrarVeiculo() {
    int TAM;
    if (contadorVeiculos >= MAX_VEICULOS) {
        printf("Limite de veículos atingido!\n");
        return;
    }
    
    printf("\n=========CADASTRO DE VEICULOS=========\n");
    printf("Quantos veiculos deseja cadastrar: ");
    scanf("%d", &TAM);

    Veiculo novoVeiculo;
    
    for(int i=0; i<TAM; i++){

    while(1){
    printf("Número do veículo (100 a 150): ");
    scanf("%d", &novoVeiculo.numero);
    
    if(novoVeiculo.numero >= 100 && novoVeiculo.numero <= 150){
        if(compararNumero(novoVeiculo.numero) == 0){
        break;
        }
        else{
            printf("O número ja está cadastrado\n");
        }
    }
    else{
        printf("Digite um número Válido\n");
    }
}
    printf("Marca do veículo (até 15 caracteres): ");
    scanf("%15s", novoVeiculo.marca);

    printf("Nome do veículo (até 20 caracteres): ");
    scanf("%20s", novoVeiculo.nome);

    printf("Placa do veículo (até 8 caracteres): ");
    scanf("%8s", novoVeiculo.placa);

    printf("Valor do veículo: ");
    scanf("%f", &novoVeiculo.valor);


    veiculos[contadorVeiculos++] = novoVeiculo;


    ordenarVeiculosPorMarca();
    }
}


void ordenarVeiculosPorMarca() {

qsort(veiculos, contadorVeiculos, sizeof(Veiculo), compararMarca);
    
}

void buscarVeiculoNumero(){
    int numeroBuscado, encontrado = 0;
    printf("Digite o número do veículo para busca: ");
    scanf("%d", &numeroBuscado);

    for (int i = 0; i < contadorVeiculos; i++) {
        if (veiculos[i].numero == numeroBuscado) {
            printf("Veículo encontrado:\n");
            printf("Número: %d\n", veiculos[i].numero);
            printf("Marca: %s\n", veiculos[i].marca);
            printf("Nome: %s\n", veiculos[i].nome);
            printf("Placa: %s\n", veiculos[i].placa);
            printf("Valor: R$%.2f\n", veiculos[i].valor);
            encontrado = 1;
            break;
        }
    }

    if (encontrado != 1) {
        printf("Informação não localizada!\n");
    }
}


void buscarVeiculoPlaca(){
    char placaBuscada[9];
    int encontrado = 0;
    
    printf("Digite a placa do veículo para busca: ");
    scanf("%s", placaBuscada);

    for (int i = 0; i < contadorVeiculos; i++) {
        if (strcmp(veiculos[i].placa, placaBuscada) == 0) {
            printf("Veículo encontrado:\n");
            printf("Nome: %s\n", veiculos[i].nome);
            printf("Valor: R$%.2f\n", veiculos[i].valor);
            encontrado = 1;
            break;
        }
    }

    if (encontrado != 1) {
        printf("Informação não localizada!\n");
    }
}


void listarVeiculosMarca() {
    // só lista pq ja é organizado pela marca assim que cadastra
    if (contadorVeiculos == 0) {
        printf("Não há veículos cadastrados.\n");
        return;
    }

    printf("Listagem de veículos por marca:\n");
    for (int i = 0; i < contadorVeiculos; i++) {
        printf("%d. Marca: %s - Nome: %s - Valor: R$%.2f\n", i + 1, veiculos[i].marca, veiculos[i].nome, veiculos[i].valor);
    }
}


void listarVeiculosValor() {
    if (contadorVeiculos == 0) {
        printf("Não há veículos cadastrados.\n");
        return;
    }
    
    qsort(veiculos, contadorVeiculos, sizeof(Veiculo), compararValor);

    
    printf("Listagem de veículos por valor (decrescente):\n");
    for (int i = contadorVeiculos - 1; i >= 0; i--) { 
        printf("%d. Marca: %s - Nome: %s - Valor: R$%.2f\n", contadorVeiculos - i, veiculos[i].marca, veiculos[i].nome, veiculos[i].valor);
    }
}




// Menu interativo ================================================
void menu() {
    int opcao;
    do {
        printf("\n=========CONCESSIONÁRIA UNIÃO=========\n");
        printf("1. Cadastro de veículos\n");
        printf("2. Busca de veículos pelo número\n");
        printf("3. Busca de veículos pela placa\n");
        printf("4. Listagem de veículos pela ordem crescente da marca\n");
        printf("5. Listagem de veículos pela ordem decrescente do valor\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarVeiculo();
                break;
            case 2:
                buscarVeiculoNumero();
                break;
            case 3:
                buscarVeiculoPlaca();
                break;
            case 4:
                listarVeiculosMarca();
                break;
            case 5:
                listarVeiculosValor();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
}



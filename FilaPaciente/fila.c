#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

Fila* criarFila(int m) {
    Fila *F = malloc(sizeof(Fila));
    F->max = m;
    F->total = 0;
    F->inicio = 0;
    F->final = 0;
    F->item = malloc(m * sizeof(Paciente));
    return F;
}

int vaziaf(Fila *F) {
    return (F->total == 0);
}

int cheiaf(Fila *F) {
    return (F->total == F->max);
}

void enfila(Paciente x, Fila *F) {
    if (cheiaf(F)) {
        printf("Fila cheia!\n");
        return;
    }
    F->item[F->final] = x;
    F->final = (F->final + 1) % F->max;
    F->total++;
}

Paciente desenfila(Fila *F) {
    if (vaziaf(F)) {
        printf("Fila vazia!\n");
        Paciente vazio = {"", "", "", "", ""};
        return vazio;
    }
    Paciente p = F->item[F->inicio];
    F->inicio = (F->inicio + 1) % F->max;
    F->total--;
    return p;
}

void destruirFila(Fila *F, const char* nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }
    while (!vaziaf(F)) {
        Paciente p = desenfila(F);
        fprintf(arquivo, "Paciente %s, sob responsabilidade do Médico %s, encaminhado para cirurgia %s, em modo %s.\n",
                p.nome, p.medico, p.especialidade, p.tipoCirurgia);
    }
    fclose(arquivo);
    free(F->item);
    free(F);
}

int validarCPF(char *cpf) {
    int i, j, digito1 = 0, digito2 = 0;

    if (strlen(cpf) != 11) return 0;

    for (i = 0, j = 10; i < 9; i++, j--) {
        digito1 += (cpf[i] - '0') * j;
    }
    digito1 = (digito1 * 10) % 11;
    if (digito1 == 10) digito1 = 0;

    for (i = 0, j = 11; i < 10; i++, j--) {
        digito2 += (cpf[i] - '0') * j;
    }
    digito2 = (digito2 * 10) % 11;
    if (digito2 == 10) digito2 = 0;

    return (digito1 == cpf[9] - '0' && digito2 == cpf[10] - '0');
}

void menu() {
    Fila *filaEletiva = criarFila(100);
    Fila *filaEmergencia = criarFila(100);
    int opcao;

    do {
        printf("\n=======================Menu=======================\n");
        printf("1. Cadastrar paciente\n");
        printf("2. Retirar paciente da fila de emergência\n");
        printf("3. Retirar paciente da fila eletiva\n");
        printf("4. Consultar quantidade de pacientes nas filas\n");
        printf("5. Destruir filas e gerar arquivo\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Paciente p;
            printf("Digite o CPF (11 dígitos): ");
            scanf("%s", p.cpf);
            if (!validarCPF(p.cpf)) {
                printf("CPF inválido!\n");
                continue;
            }
            printf("Nome: ");
            scanf(" %[^\n]", p.nome);
            printf("Especialidade da cirurgia: ");
            scanf(" %[^\n]", p.especialidade);
            printf("Nome do médico: ");
            scanf(" %[^\n]", p.medico);
            printf("Tipo de cirurgia (Eletiva/Emergência): ");
            scanf(" %[^\n]", p.tipoCirurgia);

            if (strcmp(p.tipoCirurgia, "Eletiva") == 0) {
                enfila(p, filaEletiva);
            } else if (strcmp(p.tipoCirurgia, "Emergência") == 0) {
                enfila(p, filaEmergencia);
            } else {
                printf("Tipo de cirurgia inválido!\n");
            }
        } else if (opcao == 2) {
            Paciente p = desenfila(filaEmergencia);
            if (strlen(p.cpf) > 0) {
                printf("Paciente %s, sob responsabilidade do Médico %s, encaminhado para cirurgia %s, em modo Emergência.\n",
                       p.nome, p.medico, p.especialidade);
            }
        } else if (opcao == 3) {
            Paciente p = desenfila(filaEletiva);
            if (strlen(p.cpf) > 0) {
                printf("Paciente %s, sob responsabilidade do Médico %s, encaminhado para cirurgia %s, em modo Eletiva.\n",
                       p.nome, p.medico, p.especialidade);
            }
        } else if (opcao == 4) {
            printf("Total de pacientes na fila de emergência: %d\n", filaEmergencia->total);
            printf("Total de pacientes na fila eletiva: %d\n", filaEletiva->total);
        } else if (opcao == 5) {
            destruirFila(filaEletiva, "encaminhamentos_eletiva.txt");
            destruirFila(filaEmergencia, "encaminhamentos_emergencia.txt");
            printf("Filas destruídas e encaminhamentos gerados.\n");
        }

    } while (opcao != 6);
}
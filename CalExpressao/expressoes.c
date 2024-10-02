#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressoes.h"

void inicializaPilha(Pilha* p) {
    p->topo = -1;
}

int pilhaVazia(Pilha* p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha* p) {
    return p->topo == MAX - 1;
}

void push(Pilha* p, float valor) {
    if (!pilhaCheia(p)) {
        p->itens[++(p->topo)] = valor;
    }
}

float pop(Pilha* p) {
    if (!pilhaVazia(p)) {
        return p->itens[(p->topo)--];
    }
    return -1;
}

int prioridade(char operador) {
    switch (operador) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 0;
        default:
            return -1;
    }
}

void infixoParaPosfixo(char* infixo, char* posfixo) {
    Pilha operadores;
    inicializaPilha(&operadores);
    int j = 0;

    for (int i = 0; infixo[i] != '\0'; i++) {
        char simbolo = infixo[i];

        if ((simbolo >= 'A' && simbolo <= 'Z') || (simbolo >= 'a' && simbolo <= 'z')) {
            posfixo[j++] = simbolo;
        } else if (simbolo == '(') {
            push(&operadores, simbolo);
        } else if (simbolo == ')') {
            while (!pilhaVazia(&operadores) && operadores.itens[operadores.topo] != '(') {
                posfixo[j++] = pop(&operadores);
            }
            pop(&operadores);
        } else { 
            while (!pilhaVazia(&operadores) && prioridade(operadores.itens[operadores.topo]) >= prioridade(simbolo)) {
                posfixo[j++] = pop(&operadores);
            }
            push(&operadores, simbolo);
        }
    }

    while (!pilhaVazia(&operadores)) {
        posfixo[j++] = pop(&operadores);
    }
    posfixo[j] = '\0';  
}

float obtemValorVariavel(char var, Variavel* variaveis, int numVariaveis) {
    for (int i = 0; i < numVariaveis; i++) {
        if (variaveis[i].variavel == var) {
            return variaveis[i].valor;
        }
    }
    printf("Erro: Variável %c não foi definida.\n", var);
    exit(1);
}

float avaliaPosfixa(char* expressao, Variavel* variaveis, int numVariaveis) {
    Pilha valores;
    inicializaPilha(&valores);

    for (int i = 0; expressao[i] != '\0'; i++) {
        char simbolo = expressao[i];

        if ((simbolo >= 'A' && simbolo <= 'Z') || (simbolo >= 'a' && simbolo <= 'z')) {
            float valor = obtemValorVariavel(simbolo, variaveis, numVariaveis);
            push(&valores, valor);
        } else { 
            float op2 = pop(&valores);
            float op1 = pop(&valores);
            switch (simbolo) {
                case '+': push(&valores, op1 + op2); break;
                case '-': push(&valores, op1 - op2); break;
                case '*': push(&valores, op1 * op2); break;
                case '/': push(&valores, op1 / op2); break;
            }
        }
    }

    return pop(&valores);
}

int verificaExpressao(char* expressao) {
    int balanceamento = 0;
    for (int i = 0; expressao[i] != '\0'; i++) {
        if (expressao[i] == '(') {
            balanceamento++;
        } else if (expressao[i] == ')') {
            balanceamento--;
            if (balanceamento < 0) return 0;
        }
    }
    return balanceamento == 0;
}

void menu(){
    char expressao[100];
    char posfixa[100];
    Variavel variaveis[MAX];
    int numVariaveis = 0;
    int opcao;

    while (1) {
        printf("\n==============MENU==============\n");
        printf("1. Definir expressao\n");
        printf("2. Definir valor das variaveis\n");
        printf("3. Avaliar expressao\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a expressao infixa: ");
                scanf("%s", expressao);

                if (verificaExpressao(expressao)) {
                    infixoParaPosfixo(expressao, posfixa);
                    printf("Expressao posfixa: %s\n", posfixa);
                } else {
                    printf("Erro: Expressao malformada.\n");
                }
                break;

            case 2:
                printf("Digite o numero de variaveis: ");
                scanf("%d", &numVariaveis);

                for (int i = 0; i < numVariaveis; i++) {
                    printf("Digite a variavel (letra) e o valor: ");
                    scanf(" %c %f", &variaveis[i].variavel, &variaveis[i].valor);
                }
                break;

            case 3:
                if (numVariaveis == 0) {
                    printf("Erro: Defina os valores das variaveis antes de avaliar a expressao.\n");
                } else {
                    float resultado = avaliaPosfixa(posfixa, variaveis, numVariaveis);
                    printf("Resultado da expressao: %.2f\n", resultado);
                }
                break;

            case 4:
                exit(0);

            default:
                printf("Opcao invalida.\n");
        }
    }
}
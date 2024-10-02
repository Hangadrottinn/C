typedef struct Paciente {
    char cpf[12];
    char nome[100];
    char especialidade[50];
    char medico[100];
    char tipoCirurgia[10];
} Paciente;

typedef struct Fila {
    int max;
    int total;
    int inicio;
    int final;
    Paciente *item;
} Fila;

Fila* criarFila(int m);
int vaziaf(Fila *F);
int cheiaf(Fila *F);
void enfila(Paciente x, Fila *F);
Paciente desenfila(Fila *F);
void destruirFila(Fila *F, const char* nomeArquivo);
void menu();
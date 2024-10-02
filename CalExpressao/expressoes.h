#define MAX 100

typedef struct {
    char variavel;
    float valor;
} Variavel;

typedef struct {
    float itens[MAX];
    int topo;
} Pilha;

void inicializaPilha(Pilha* p);
int pilhaVazia(Pilha* p);
int pilhaCheia(Pilha* p);
void push(Pilha* p, float valor);
float pop(Pilha* p);
int prioridade(char operador);
void infixoParaPosfixo(char* infixo, char* posfixo);
float avaliaPosfixa(char* expressao, Variavel* variaveis, int numVariaveis);
int verificaExpressao(char* expressao);
float obtemValorVariavel(char var, Variavel* variaveis, int numVariaveis);

void menu();



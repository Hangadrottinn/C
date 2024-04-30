/******************************************************************************
João Gabriel de Almeida
*******************************************************************************/
typedef struct {
    int numero;
    char marca[16];
    char nome[21];
    char placa[9];
    float valor;
} Veiculo;

void cadastrarVeiculo();
void buscarVeiculoNumero();
void buscarVeiculoPlaca();
void listarVeiculosMarca();
void listarVeiculosValor();
void menu();
void ordenarVeiculosPorMarca();
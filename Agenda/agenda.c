#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Pessoa{
            int id;
            char nome[30];
            char email[50];
            char data[8];
            char cpf[11];
        } pessoa;
        
        
int validarCPF(char *cpf)
{
    int i, j, digito1 = 0, digito2 = 0;
    for (i = 0; i < 11; i++)
    {
        if (cpf[i] < 48 || cpf[i] > 57)
        return 2;
    }
    if (strlen(cpf) != 11)
        return 0;
    else if ((strcmp(cpf, "00000000000") == 0) || (strcmp(cpf, "11111111111") == 0) || (strcmp(cpf, "22222222222") == 0) ||
            (strcmp(cpf, "33333333333") == 0) || (strcmp(cpf, "44444444444") == 0) || (strcmp(cpf, "55555555555") == 0) ||
            (strcmp(cpf, "66666666666") == 0) || (strcmp(cpf, "77777777777") == 0) || (strcmp(cpf, "88888888888") == 0) ||
            (strcmp(cpf, "99999999999") == 0))
        return 0;
    else
    {
        for (i = 0, j = 10; i < strlen(cpf) - 2; i++, j--)
            digito1 += (cpf[i] - 48) * j;
        digito1 %= 11;
        if (digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if ((cpf[9] - 48) != digito1)
            return 0;
        else
        {
            for (i = 0, j = 11; i < strlen(cpf) - 1; i++, j--)
            digito2 += (cpf[i] - 48) * j;
            digito2 %= 11;
            if (digito2 < 2)
            digito2 = 0;
            else
            digito2 = 11 - digito2;
            if ((cpf[10] - 48) != digito2)
            return 0;
        }
    }
    return 1;
}

int verificarNome(pessoa p){
    FILE *arquivo = fopen("agenda.txt", "r");
    char nomes[30];
    int id;
    int ver;
    
    p.nome[strcspn(p.nome, "\n")] = 0;
    
    if(arquivo == NULL){
        printf("Não foi possivel abrir o arquivo. \n");
    }
    while (fgets(nomes, sizeof(nomes), arquivo)) {
        
        if(strstr(nomes, p.nome) != NULL){
            ver = 1;
            break;
        }
    }
    fclose(arquivo);
    
    
    
    if(ver == 1){
        return 1;
    }
    else{
    return 0;
    }
}

int verificarNome2(char *nome){
    FILE *arquivo = fopen("agenda.txt", "r");
    char nomes[30];
    int id;
    int ver;
    
    nome[strcspn(nome, "\n")] = 0;
    
    if(arquivo == NULL){
        printf("Não foi possivel abrir o arquivo. \n");
    }
    while (fgets(nomes, sizeof(nomes), arquivo)) {
        
        if(strstr(nomes, nome) != NULL){
            ver = 1;
            break;
        }
    }
    fclose(arquivo);
    
    
    
    if(ver == 1){
        return 1;
    }
    else{
    return 0;
    }
}

int buscarID(pessoa p){
    FILE *arquivo = fopen("agenda.txt", "r");
    char lin[300];
    int id = 0;
    int ver;
    
    
    
    if(arquivo == NULL){
        printf("Não foi possivel abrir o arquivo. \n");
    }
    while (fgets(lin, sizeof(lin), arquivo)) {
        id++;
        if(id == p.id){
            ver = 1;
            break;
        }
    }
    fclose(arquivo);
    
    
    
    if(ver == 1){
        return 1;
    }
    else{
    return 0;
    }
    
}

int definirID(){
    FILE *arquivo = fopen("agenda.txt", "r");
    if(arquivo == NULL){
        printf("Não foi possivel abrir o arquivo.\n");
    }
    
    int lin = 0;
    char ch;
    
    while((ch = fgetc(arquivo)) != EOF){
        if (ch == '\n'){
            lin++;
        }
    }
    return lin;
    
    fclose(arquivo);
}

        
void inserir(pessoa p){
    FILE *arquivo = fopen("agenda.txt", "a");
    if(arquivo == NULL){
        printf("Não foi possivel abrir o arquivo.\n");
    }
    
    // definir ID
    p.id = definirID();
    
    
    fprintf(arquivo, "ID:%d / Nome:%s / Email:%s / Data de nascimento:%.8s / CPF:%s \n", p.id, p.nome, p.email, p.data, p.cpf);
    
        
}

void cadastrarTelefone(char *telefone, char *nome){
    FILE *arquivo, *temp;
    char lin[300];
    int ver;
    
    arquivo = fopen("agenda.txt", "r");
    temp = fopen("temp.txt", "w");
    
    nome[strcspn(nome, "\n")] = 0;
    
    telefone[strcspn(telefone, "\n")] = 0;
    
    
    
    if(arquivo == NULL || temp == NULL){
        printf("Não foi possivel abrir o arquivo");
        
    }
    
    while (fgets(lin, sizeof(lin), arquivo)) {
        if (strstr(lin, nome) != NULL) {
            ver = 1;
            lin[strcspn(lin, "\n")] = 0;
            fprintf(temp, "%s / telefone: %s\n", lin, telefone);
        } else {
            fprintf(temp, "%s", lin);
        }
    }

    
    
    if(ver == 1){
        remove("agenda.txt");
        rename("temp.txt", "agenda.txt");
    }
    else{
        remove("temp.txt");
    }
    
    
    fclose(arquivo);
    fclose(temp);
    
}

void cadastrarTelefoneID(char *telefone, int id){
    FILE *arquivo, *temp;
    char lin[300];
    int IDs = -1;
    int ver;
    
    arquivo = fopen("agenda.txt", "r");
    temp = fopen("temp.txt", "w");
    
    telefone[strcspn(telefone, "\n")] = 0;
    
    
    
    if(arquivo == NULL || temp == NULL){
        printf("Não foi possivel abrir o arquivo");
        
    }
    
    while (fgets(lin, sizeof(lin), arquivo)) {
        IDs++;
        if (IDs == id) {
            ver = 1;
            lin[strcspn(lin, "\n")] = 0;
            fprintf(temp, "%s / telefone: %s\n", lin, telefone);
        } else {
            fprintf(temp, "%s", lin);
        }
    }

    
    
    if(ver == 1){
        remove("agenda.txt");
        rename("temp.txt", "agenda.txt");
    }
    else{
        remove("temp.txt");
    }
    
    
    fclose(arquivo);
    fclose(temp);
    
}

void editarNome(char *nomeNovo, char *nomeAntigo){

    FILE *arquivo = fopen("agenda.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    char linha[300];
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, nomeAntigo) != NULL) {
            
            char novaLinha[300];
            char *pos = strstr(linha, nomeAntigo);
            strncpy(novaLinha, linha, pos - linha); 
            novaLinha[pos - linha] = '\0'; 
            strcat(novaLinha, nomeNovo); 
            strcat(novaLinha, pos + strlen(nomeAntigo)); 
            fprintf(temp, "%s", novaLinha);
        } else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("agenda.txt");
    rename("temp.txt", "agenda.txt");
}


void editarData(char *data, char *nome){
    FILE *arquivo = fopen("agenda.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    struct Pessoa p;
    char linha[300];
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "ID:%d / Nome:%s / Email:%s / Data de nascimento:%s / CPF:%s Telefone:\n", &p.id, p.nome, p.email, p.data, p.cpf);
        if (strcmp(p.nome, nome) == 0) {
            
            strcpy(p.data, data);
        }
        
        fprintf(temp, "ID:%d / Nome:%s / Email:%s / Data de nascimento:%.8s / CPF:%s Telefone:\n", p.id, p.nome, p.email, p.data, p.cpf);
    }

    fclose(arquivo);
    fclose(temp);

    
    remove("agenda.txt");
    rename("temp.txt", "agenda.txt");
}

void editarCPF(char *cpf, char *nome){
    FILE *arquivo = fopen("agenda.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    struct Pessoa p;
    char linha[300];
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "ID:%d / Nome:%s / Email:%s / Data de nascimento:%s / CPF:%s Telefone:\n", &p.id, p.nome, p.email, p.data, p.cpf);
        if (strcmp(p.nome, nome) == 0) {
            
            strcpy(p.cpf, cpf);
        }
        
        fprintf(temp, "ID:%d / Nome:%s / Email:%s / Data de nascimento:%.8s / CPF:%s Telefone:\n", p.id, p.nome, p.email, p.data, p.cpf);
    }

    fclose(arquivo);
    fclose(temp);

    
    remove("agenda.txt");
    rename("temp.txt", "agenda.txt");
}


void editarEmail(char *email, char *nome){
    FILE *arquivo = fopen("agenda.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    struct Pessoa p;
    char linha[300];
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "ID:%d / Nome:%s / Email:%s / Data de nascimento:%s / CPF:%s Telefone:\n", &p.id, p.nome, p.email, p.data, p.cpf);
        if (strcmp(p.nome, nome) == 0) {
            
            strcpy(p.email, email);
        }
        
        fprintf(temp, "ID:%d / Nome:%s / Email:%s / Data de nascimento:%.8s / CPF:%s Telefone:\n", p.id, p.nome, p.email, p.data, p.cpf);
    }

    fclose(arquivo);
    fclose(temp);

    
    remove("agenda.txt");
    rename("temp.txt", "agenda.txt");
}

char* converterID(int id){
    FILE *arquivo = fopen("agenda.txt", "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        
    }
    char *nome = malloc(30 * sizeof(char));

    struct Pessoa p;
    char linha[300];
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "ID:%d / Nome:%s / Email:%s / Data de nascimento:%s / CPF:%s Telefone:\n", &p.id, p.nome, p.email, p.data, p.cpf);
        if (p.id == id) {
            break;
        }
    }

    fclose(arquivo);
    strcpy(nome, p.nome);
    return nome;
}

void editarPessoaNome(int dado, pessoa p){
    // pessoa p;
    char nomeN[30];
    if(p.id > -1){
        
        char *nome = converterID(p.id);
        strcpy(p.nome, nome);
        
        free(nome);
        
    }

        if(dado == 1){
               while(1){
                    printf("Novo Nome: ");
                    scanf("%s", nomeN);
                    if(strlen(nomeN) < 3){
                        printf("Caracteres Insuficientes\n");
                    }
                    else{
                        if(verificarNome2(nomeN) == 1){
                            printf("Esse Nome já foi cadastrado\n");
                        }
                        else{
                            editarNome(nomeN, p.nome);
                            break;
                        }
                        
                    }
                    
                }             
            
        }
        
        if(dado == 2){
            while(1){
                printf("Nova Data de Nascimento (dd/mm/aaaa): ");
                scanf("%s", p.data);
                if(strlen(p.data) != 8){
                    printf("Data Inválida\n");
                }
                else{
                    editarData(p.data, p.nome);
                    break;
                }
            }
            
        }
        
        if(dado == 3){
            while(1){
                printf("Digite o novo CPF: ");
                scanf("%s", p.cpf);
                                
                if(validarCPF(p.cpf) == 2){
                    printf("Número inválido\n");
                }
                if(validarCPF(p.cpf) == 0){
                    printf("CPF inválido\n");
                }
                if(validarCPF(p.cpf) == 1){
                    editarCPF(p.cpf, p.nome);
                    break;
                }
            }
            
        }
        
        if(dado == 4){
            while(1){
                printf("Digite um novo E-mail: ");
                scanf("%s", p.email);
                                
                if(strlen(p.email) <= 10){
                    printf("E-mail inválido\n");
                }
                                
                else{
                    if(strlen(p.email) < 10){
                        printf("E-mail inválido\n");
                    }
                    else{
                        char ch = '@';
                                        
                        char *resul = strchr(p.email, ch);
                        if(resul){
                            editarEmail(p.email, p.nome);
                            break;
                        }
                        else{
                            printf("E-mail inválido\n");
                        }
                    }
                }
                                
            }
        }
}





void listarPessoas(){
    FILE *arquivo = fopen("agenda.txt", "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
    }

    char linha[300];
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }

    fclose(arquivo);
    
}

void excluir(char *nome){
    FILE *arquivo = fopen("agenda.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    struct Pessoa p;
    char linha[300];
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "ID:%d / Nome:%s / Email:%s / Data de nascimento:%s / CPF:%s Telefone:\n", &p.id, p.nome, p.email, p.data, p.cpf);
        if (strcmp(p.nome, nome) != 0) {
            
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    
    remove("agenda.txt");
    rename("temp.txt", "agenda.txt");
}


int main(void)
{
    int opcao;
    
    
    pessoa p;
    
    
    
    
    // MENU PRINCIPAL:
    
    while(1){
    
    printf("   Menu da Agenda\nDigite o número de uma função:\n 1. Cadastrar\n 2. Editar\n 3. Excluir\n 4. Consultar\n 5. Sair\n");
    scanf("%d", &opcao);
    
    switch (opcao){
        
        
        case 1:
        
            // MENU CADASTRAR
            while(1){
                printf("  Menu Cadastrar\nDigite o número:\n 1. Pessoa\n 2. Telefone\n 3. Retornar\n");
                scanf("%d", &opcao);
                
                switch(opcao){
                    case 1:
                        printf("Cadastrar Pessoa:\n");
                        int a;
    
                        printf("Digite os dados da Pessoa\n");
                        while(1){
                            printf("Nome: ");
                            scanf("%s", p.nome);
                            if(strlen(p.nome) < 3){
                                printf("Caracteres Insuficientes\n");
                            }
                            else{
                                if(verificarNome(p) == 1){
                                    printf("Essa Pessoa já foi cadastrada\n");
                                }
                                else{
                                    break;
                                }
                            }
                        }
                        
                        while(1){
                            printf("Data de Nascimento (dd/mm/aaaa): ");
                            scanf("%s", p.data);
                            if(strlen(p.data) != 8){
                                printf("Data Inválida\n");
                            }
                            else{
                                break;
                            }
                        }
                        
                        while(1){
                            printf("CPF: ");
                            scanf("%s", p.cpf);
                            
                            if(validarCPF(p.cpf) == 2){
                                printf("Número inválido\n");
                            }
                            if(validarCPF(p.cpf) == 0){
                                printf("CPF inválido\n");
                            }
                            if(validarCPF(p.cpf) == 1){
                                break;
                            }
                        }
                        
                        while(1){
                            printf("E-mail: ");
                            scanf("%s", p.email);
                            
                            if(strlen(p.email) <= 10){
                                printf("E-mail inválido\n");
                            }
                            
                            else{
                                if(strlen(p.email) < 10){
                                    printf("E-mail inválido\n");
                                }
                                else{
                                    char ch = '@';
                                    
                                    char *resul = strchr(p.email, ch);
                                    if(resul){
                                        inserir(p);
                                        break;
                                    }
                                    else{
                                        printf("E-mail inválido\n");
                                    }
                                }
                            }
                            
                        }
                        // printf("O programa deverá continuar aqui\n");
                     return 0;
                     break;
                    
                    
                    //Menu Cadastrar Telefone
                    
                    case 2:
                        while(1){
                            printf("Cadastrar Telefone com base em:\n 1. Nome\n 2. IDPessoa\n 3. Retornar\n");
                            scanf("%d", &opcao);
                            
                            switch(opcao){
                                case 1:
                                while(1){
                                char nome[30];
                                printf("Digite o Nome: ");
                                scanf("%s", p.nome);
                                if(verificarNome(p) == 0){
                                    printf("Esse nome não está cadastrado\n");
                                }
                                else{
                                    char telefone[11];
                                    printf("Digite o número de telefone: ");
                                    scanf("%s", telefone);
                                    
                                    if(strlen(telefone) < 10){
                                        printf("Número Inválido\n");
                                    }
                                    else{
                                    cadastrarTelefone(telefone, p.nome);
                                    opcao = 3;
                                    break;
                                    }
                                }
                                }
                                break;
                                
                                case 2:
                                while(1){
                                    printf("Digite o ID: ");
                                    scanf("%d", &p.id);
                                    if(buscarID(p) == 0){
                                        printf("ID inválido\n");
                                    }
                                    else{
                                        char telefone[11];
                                        
                                        printf("Digite o número de Telefone: ");
                                        scanf("%s", telefone);
                                        
                                        if(strlen(telefone) < 10){
                                        printf("Número Inválido\n");
                                        }
                                        else{
                                        cadastrarTelefoneID(telefone, p.id);
                                        opcao = 3;
                                        break;
                                        }
                                    }
                                }
                                
                                break;
                                
                                case 3:
                                break;
                                
                                }
                            if(opcao == 3){
                                break;
                            }
                        }
                        return 0;
                        break;
                    
                    case 3:
                        break;
                        
                    default:
                        printf("Opção inválida");
                        break;
                }
                if (opcao == 3){
                    break;
                }
            }
           
         break;
         
         
        // MENU EDITAR
        case 2:
            
            while(1){
                printf("   Menu Editar\n 1. Pessoa\n 2. Retornar\n");
                scanf("%d", &opcao);
                
                switch(opcao){
                    case 1:
                        while(1){
                            printf("  Selecione a opção de busca\n 1. Nome\n 2. IDPessoa\n 3. Retornar\n");
                            scanf("%d", &opcao);
                            
                            
                                switch(opcao){
                                    case 1:
                                        while(1){
                                            printf("Digite o nome: \n");
                                            scanf("%s", p.nome);
                                            if(verificarNome(p) == 0){
                                                printf("Nome Inválido\n");
                                            }
                                            else{
                                                int dado;
                                                printf("Qual dado deseja editar?\n 1. Nome\n 2. Data de Nascimento\n 3. CPF\n 4. E-mail\n 5. Retornar\n");
                                                scanf("%d", &dado);
                                                if(dado == 5){
                                                    break;
                                                }
                                                else{
                                                    editarPessoaNome(dado, p);
                                                    return 0;
                                                    break;
                                                }
                                            }
                                        
                                        }
                                        
                                        
                                        break;
                                    
                                    case 2:
                                        while(1){
                                            printf("Digite o ID: ");
                                            scanf("%d", &p.id);
                                            if(buscarID(p) == 0){
                                                printf("ID invalido\n");
                                            }
                                            else{
                                                int dado;
                                                printf("Qual dado deseja editar?\n 1. Nome\n 2. Data de Nascimento\n 3. CPF\n 4. E-mail\n 5. Retornar\n");
                                                scanf("%d", &dado);
                                                if(dado == 5){
                                                    break;
                                                }
                                                else{
                                                    editarPessoaNome(dado, p);
                                                    return 0;
                                                    break;
                                                }
                                            }
                                        }
                                        
                                        break;
                                    
                                    case 3:
                                        break;
                                        
                                    default:
                                        printf("Opção Inválida\n");
                                        break;
                                }
                                if(opcao == 3){
                                    break;
                                }
                        }
                        break;
                    
                    case 2:
                        break;
                        
                    default:
                        printf("Opção Inválida\n");
                        break;                
                }
                if(opcao == 2){
                    break;
                }
            
            }
            
            break;
        
        case 3:
            while(1){
                printf("   Menu Excluir\n 1. Nome\n 2. Retornar\n");
                scanf("%d", &opcao);
                
                switch(opcao){
                    case 1:
                        while(1){
                            char nomeE[30];
                            printf("Digite o nome a ser Excluido: \n");
                            scanf("%s", nomeE);
                            if(verificarNome2(nomeE) == 0){
                                printf("Nome Inválido\n");
                            }
                            else{
                                excluir(nomeE);
                                return 0;
                                break;
                            }
                        }
                
                        break;
                    
                    case 2:
                        break;
                        
                    
                    default:
                        printf("Opção Inválida\n");
                        break;
                }
            }
                
                if(opcao == 2){
                    break;
                }
            
            
        case 4:
            listarPessoas();
            return 0;
            break;
        
        case 5:
            return 0;
            break;
        
        default:
            printf("Opção Inválida\n");
            break;
    }
    }
}

      

    
    


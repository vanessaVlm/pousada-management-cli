#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define Q 30

struct cliente {
    char nome[100];
    int cpf;
    char email[100];
    char senha[100];
    int quarto;
    int noites;
    float precototal;
};

struct cliente *clientes = NULL;
int total = 0;

void salvarclientes() {
    FILE *arquivo;
    arquivo = fopen("cadastros_realizados.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "Nome: %s\nCPF: %d\nCelular: %d\nEmail: %s\nSenha: %s\nQuarto: %d\nNoites: %d\n",
            clientes[i].nome, clientes[i].cpf,
            clientes[i].email, clientes[i].senha, clientes[i].quarto, clientes[i].noites);
        if (i < total - 1) {
            fprintf(arquivo, "\n");
        }
    }

    fclose(arquivo);
}

void cadastrarcliente() {
    struct cliente atualcliente;
    if (clientes == NULL) {
        clientes = (struct cliente*)malloc(sizeof(struct cliente));
    } else {
        clientes = (struct cliente*)realloc(clientes,(total + 1)*sizeof(struct cliente));
    }

    if (clientes == NULL) {
        printf("Erro ao alocar memoria para o cliente.\n");
        return;
    }

    printf("-----Cadastrar cliente-----\n");

    fflush(stdin);
    printf("Nome:");
    gets(atualcliente.nome);
    fflush(stdin);

    printf("CPF:");
    scanf("%d",&atualcliente.cpf);

    fflush(stdin);
    printf("Email:");
    gets(atualcliente.email);
    fflush(stdin);

    printf("Crie uma senha:");
    gets(atualcliente.senha);
    fflush(stdin);

    clientes[total] = atualcliente;
    total++;
    printf("Cliente cadastrado com sucesso!\n");
}

void consultarcliente() {
    int cpf2;
    int achou=0;

    printf("-----Buscar cliente-----\n");
    printf("Digite o CPF:");
    scanf("%d", &cpf2);

    for (int i = 0; i < total; i++) {
        if (clientes[i].cpf==cpf2) {
            printf("Cliente encontrado!\n");
            printf("Nome: %s\n",clientes[i].nome);
            printf("Email: %s\n",clientes[i].email);
            achou=1;
            break;
        }
    }

    if (!achou) {
        printf("Cliente nao encontrado!\n");
    }
}
int quartos[Q];
float preco=100;

void reservacliente() {
    int cpf2;
    int achou=0;

    printf("-----Reservas-----\n");

    printf("Digite o CPF:");
    scanf("%d",&cpf2);

    for (int i = 0; i < total; i++) {
        if (clientes[i].cpf==cpf2) {
            char senha[100];

            fflush(stdin);
            printf("Senha:");
            gets(senha);
            fflush(stdin);

            if (strcmp(clientes[i].senha,senha)==0) {
                printf("Quartos ocupados:");
                    for (int j = 0; j < Q; j++) {
                        if (quartos[j] == 1) {
                            printf("Quarto %d,", j + 1);
                        }
                    }
                printf("\nNumero do quarto (1 a 30):");
                scanf("%d",&clientes[i].quarto);

                if (clientes[i].quarto<1 || clientes[i].quarto>Q){
                    printf("Esse numero de quarto nao existe!");
                    return;
                }
                if (quartos[clientes[i].quarto - 1] == 0) {

                    printf("Diaria 100.00 R$\n");
                    printf("Numero de noites:");
                    scanf("%d",&clientes[i].noites);

                    clientes[i].precototal=preco*clientes[i].noites;
                    printf("Total a ser pago:%.2f\n",clientes[i].precototal);

                    printf("Reserva feita com sucesso!\n");
                    quartos[clientes[i].quarto - 1] = 1;
                }
                else{
                    printf("O quarto %d esta ocupado.\n", clientes[i].quarto);
                }
            } else {
                printf("Senha incorreta,cliente nao encontrado!\n");
            }

            achou=1;
            break;
        }
    }

    if (!achou) {
        printf("Cliente nao encontrado!\n");
    }
}

void alterarcliente() {
    int cpf2;
    int achou=0;
    int opcao;

    printf("-----Alterar cadastro-----\n");
    printf("Digite o CPF:");
    scanf("%d", &cpf2);

    for (int i = 0; i < total; i++) {
        if (clientes[i].cpf==cpf2) {
            printf("Selecione o dado que deseja alterar\n");
            printf("1-Nome\n");
            printf("2-Email\n");
            printf("3-Senha\n");
            printf("4-Quarto\n");
            printf("5-Noites\n");
            printf(":");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Nome:");
                    fflush(stdin);
                    gets(clientes[i].nome);
                    fflush(stdin);
                    printf("Alteracao realizada com sucesso!\n");
                    break;
                case 2:
                    printf("Email:");
                    fflush(stdin);
                    gets(clientes[i].email);
                    fflush(stdin);
                    printf("Alteracao realizada com sucesso!\n");
                    break;
                case 3:
                    printf("Senha:");
                    fflush(stdin);
                    gets(clientes[i].senha);
                    fflush(stdin);
                    printf("Alteracao realizada com sucesso!\n");
                    break;
                case 4:
                    printf("Quarto:");
                    scanf("%d", &clientes[i].quarto);
                    printf("Alteracao realizada com sucesso!\n");
                    break;
                case 5:
                    printf("Noites:");
                    scanf("%d", &clientes[i].noites);
                    clientes[i].precototal=preco*clientes[i].noites;
                    printf("Alteracao realizada com sucesso!\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
            achou=1;
            break;
        }
    }

    if (!achou) {
        printf("Cliente nao encontrado!\n");
    }
}

void excluircliente() {
    int cpf2;
    int achou=0;
    int opcao;

    printf("-----Excluir dado-----\n");
    printf("Digite o CPF:");
    scanf("%d", &cpf2);

    for (int i = 0; i < total; i++) {
        if (clientes[i].cpf == cpf2) {
            printf("Selecione o dado que deseja excluir\n");
            printf("1-Nome\n");
            printf("2-Email\n");
            printf("3-Senha\n");
            printf("4-Quarto\n");
            printf("5-Noites\n");
            printf(":");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Nome excluido!\n");
                    strcpy(clientes[i].nome, "Sem dado");
                    break;
                case 2:
                    printf("Email excluido!\n");
                    strcpy(clientes[i].email,"Sem dado");
                    break;
                case 3:
                    printf("Senha excluida!\n");
                    strcpy(clientes[i].senha,"Sem dado");
                    break;
                case 4:
                    printf("Reserva do quarto excluida!\n");
                    clientes[i].quarto=0;
                    break;
                case 5:
                    printf("Numero de noites excluido!\n");
                    clientes[i].noites=0;
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
            achou=1;
            break;
        }
    }

    if (!achou) {
        printf("Cliente nao encontrado!\n");
    }
}
void imprimirrelatorio() {
    int cpf2;
    int achou=0;

    printf("-----Relatorio de Reservas-----\n");

    printf("Digite o CPF:");
    scanf("%d", &cpf2);

    for (int i = 0; i < total; i++) {
        if (clientes[i].cpf==cpf2) {
                printf("Quarto %d: Reservado para %s\n",clientes[i].quarto, clientes[i].nome);
                printf("Numero de noites: %d\n", clientes[i].noites);
                printf("Total pago: R$%.2f\n",clientes[i].precototal);
                achou=1;
                break;
        }
    }
if (!achou) {
        printf("Cliente nao encontrado!\n");
    }
}


int main () {
    int op;

    do {
        printf("\n");
        printf("-----Menu principal da pousada-----\n");
        printf("0-Sair do menu\n");
        printf("1-Cadastrar cliente\n");
        printf("2-Buscar cliente e seus dados cadastrados\n");
        printf("3-Reserva\n");
        printf("4-Alterar dados\n");
        printf("5-Excluir dados\n");
        printf("6-Imprimir relatorio\n");
        printf(":");
        scanf("%d",&op);
        printf("\n");

        system("cls");

        switch (op) {
            case 0:
                printf("Saindo do menu de reservas\n");
                break;
            case 1:
                cadastrarcliente();
                break;
            case 2:
                consultarcliente();
                break;
            case 3:
                reservacliente();
                break;
            case 4:
                alterarcliente();
                break;
            case 5:
                excluircliente();
                break;
            case 6:
                imprimirrelatorio();
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (op!=0);

    salvarclientes();
    if (clientes != NULL) {
    free(clientes);
    clientes = NULL;
}

    return 0;
}

#include <stdio.h>

typedef struct {
    int quantidade;
    char nome[50];
    float preco;
    char categoria[50];
} Produto;

typedef struct {
    char nome[50];
    int rg;
    int cpf;
    int dnascimento;
} Cliente;

typedef struct {
    int cpfCliente;
    char nomeProduto[50];
    float valorVenda;
    int vendidos;
} Venda;
 
typedef struct {
    int cpfCliente;
    char nomeProduto[50];
    int quantidade;
    float valorVenda;
} Compra; 

Cliente cadastrarpessoas[50];
Produto cadastrarprodutos[50];
Venda vendas[50];
Compra compras[1000];  

int numCompras = 0;   
int totalClientes = 0;
int totalProdutos = 0;
int totalVendas = 0;

#define CLIENTE_FILE "cliente.txt"
#define PRODUTO_FILE "produto.txt"
#define CAIXA_FILE "caixa.txt"
#define CAIXA_TOTAL_FILE "caixatotal.txt"

void cadastroproduto();
void consultarproduto();
void editarproduto();
void listarproduto();
void excluirproduto();

void cadastropessoa();
void consultarcliente();
void editarcliente();
void excluircliente();
void listarclientes();

void realizarvenda();
void totalPorCliente();
void vendasprodutos();
void listarCompras();

void carregarClientes();
void carregarProdutos();
void salvarProdutos();
void salvarClientes();

int main() {
    int opc1, opc2;
    do {
        printf("\n-- MENU PRINCIPAL --\n");
        printf("1-Produto\n2-Cliente\n3-Venda\n0-Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opc1);

        switch (opc1) {
            case 1:
                do {
                    printf("\n-- MENU PRODUTOS --\n");
                    printf("\n1-Cadastrar produto\n2-Consultar produto\n3-Editar produto\n4-Ecluir produto\n5-Listar produto\n0-Retornar ao menu principal\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opc2);

                    switch (opc2) {
                        case 1:
                            cadastroproduto();
                            break;
                        case 2:
                            consultarproduto();
                            break;
                        case 3:
                            editarproduto();
                            break;
                        case 4:
                            excluirproduto();
                            break; 
                        case 5:
                            listarproduto();
                            break;
                        case 0:
                            printf("Retornando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida.\n");
                    }
                } while (opc2 != 0);
                break;

            case 2:
                do {
                    printf("\n-- MENU CLIENTES --\n");
                    printf("1-Cadastrar cliente\n2-Consultar cliente\n3-Editar cliente\n4-Ecluir cliente\n5-Listar Clientes\n0-Retornar ao menu principal\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opc2);

                    switch (opc2) {
                        case 1:
                            cadastropessoa();
                            break;
                        case 2:
                            consultarcliente();
                            break;
                        case 3:
                            editarcliente();
                            break;
                        case 4:
                            excluircliente();
                            break;
                        case 5:
                            listarclientes();
                            break;
                        case 0:
                            printf("Retornando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida.\n");
                    }
                } while (opc2 != 0);
                break;

            case 3:
                do{
                    printf("\n-- MENU VENDAS --\n");
                    printf("1-Realizar venda\n2-Valor total em caixa\n3-Vendas realizadas\n4-Quantidade de produtos vendidos\n0-Retornar ao menu principal\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opc2);

                    switch (opc2)
                    {
                    case 1:
                        realizarvenda();
                        break;
                    case 2:
                        totalPorCliente();
                        break;
                    case 3:
                        listarCompras();
                        break;
                    case 4:
                        vendasprodutos();
                        break;
                    default:
                        break;
                    }
                } while (opc2 != 0);
                break;
            
            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opc1 != 0);

    return 0;
}

void cadastroproduto() {
    // Abre o arquivo para leitura. Se não encontrar o arquivo, apenas cria o arquivo para leitura/escrita posteriormente
    FILE *file = fopen("produto.txt", "r");
    if (!file) {
        // Caso não exista, cria o arquivo vazio para leitura e escrita depois
        file = fopen("produto.txt", "w");
        if (!file) {
            perror("Erro ao criar o arquivo produto.txt");
            return;
        }
        fclose(file);  // Fecha o arquivo após criá-lo
    }

    // Inicializa o total de produtos
    totalProdutos = 0;
    // Ler os produtos já existentes no arquivo e carregar no array
    while (fscanf(file, "Nome: %[^\n]\nCategoria: %[^\n]\nQuantidade: %d\nPreco: %f\n\n",
                  cadastrarprodutos[totalProdutos].nome,
                  cadastrarprodutos[totalProdutos].categoria,
                  &cadastrarprodutos[totalProdutos].quantidade,
                  &cadastrarprodutos[totalProdutos].preco) == 4) {
        totalProdutos++;  // Incrementa o número de produtos carregados
        if (totalProdutos >= 50) {
            printf("Limite de produtos cadastrados atingido!\n");
            break;
        }
    }

    fclose(file);  // Fecha o arquivo após leitura

    // Abre o arquivo para escrita (adicionar novos produtos)
    FILE *fileWrite = fopen("produto.txt", "a");
    if (!fileWrite) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    char q;
    do {
        if (totalProdutos >= 50) {
            printf("Limite de produtos cadastrados atingido!\n");
            break;
        }

        printf("\n-- CADASTRO DE PRODUTOS --\n");

        // Verificação de nome duplicado
        int aux;
        do {
            aux = 0;
            printf("Nome do produto: ");
            scanf(" %[^\n]s", cadastrarprodutos[totalProdutos].nome);

            // Verificar se o produto já existe no array carregado
            for (int i = 0; i < totalProdutos; i++) {
                int iguais = 1;  // Assume que as strings são iguais
                for (int j = 0; cadastrarprodutos[totalProdutos].nome[j] != '\0' || cadastrarprodutos[i].nome[j] != '\0'; j++) {
                    if (cadastrarprodutos[totalProdutos].nome[j] != cadastrarprodutos[i].nome[j]) {
                        iguais = 0;  // Strings são diferentes
                        break;
                    }
                }

                if (iguais) {
                    printf("O nome '%s' ja esta cadastrado. Tente novamente.\n", cadastrarprodutos[totalProdutos].nome);
                    aux = 1;
                    break;
                }
            }
        } while (aux);

        // Captura as informações do produto
        printf("Categoria: ");
        scanf(" %[^\n]s", cadastrarprodutos[totalProdutos].categoria);
        printf("Quantidade: ");
        scanf("%d", &cadastrarprodutos[totalProdutos].quantidade);
        printf("Preco do produto: ");
        scanf("%f", &cadastrarprodutos[totalProdutos].preco);

        // Grava as informações do novo produto no arquivo
        fprintf(fileWrite, "Nome: %s\nCategoria: %s\nQuantidade: %d\nPreco: %.2f\n\n",
                cadastrarprodutos[totalProdutos].nome,
                cadastrarprodutos[totalProdutos].categoria,
                cadastrarprodutos[totalProdutos].quantidade,
                cadastrarprodutos[totalProdutos].preco);

        totalProdutos++;  // Atualiza o total de produtos cadastrados

        printf("\nCadastrar outro produto (s/n)? ");
        scanf(" %c", &q);

    } while ((q == 's' || q == 'S'));

    fclose(fileWrite);  // Fecha o arquivo após salvar os dados
}

void consultarproduto() {
    char buscarprod[50];  
    char q;                
    do {
        printf("\n-- CONSULTAR PRODUTO --\n");
        printf("Digite o nome do produto: ");
        scanf(" %[^\n]s", buscarprod);  

        // Abre o arquivo "produto.txt" em modo leitura
        FILE *file = fopen("produto.txt", "r");
        if (!file) {
            perror("Erro ao abrir o arquivo");
            return;
        }

        int encontrado = 0;  // Variável para verificar se o produto foi encontrado
        char nome[100], categoria[100];
        int quantidade;
        float preco;

        // Lê os dados do arquivo "produto.txt" até o final
        while (fscanf(file, "Nome: %[^\n]\nCategoria: %[^\n]\nQuantidade: %d\nPreco: %f\n\n",
                      nome, categoria, &quantidade, &preco) == 4) {
            // Verifica se o nome do produto lido corresponde ao nome informado
            int iguais = 1;
            int j = 0;
            while (buscarprod[j] != '\0' || nome[j] != '\0') {
                if (buscarprod[j] != nome[j]) {
                    iguais = 0;
                    break;
                }
                j++;
            }

            // Se o produto foi encontrado
            if (iguais) {
                printf("\nProduto encontrado:\n");
                printf("Nome: %s\n", nome);
                printf("Categoria: %s\n", categoria);
                printf("Quantidade: %d\n", quantidade);
                printf("Preco: %.2f\n", preco);
                encontrado = 1;  // Marca que o produto foi encontrado
                break;  // Interrompe o laço, pois o produto foi encontrado
            }
        }

        fclose(file);  // Fecha o arquivo após a leitura

        if (!encontrado) {
            printf("Produto nao encontrado.\n");
        }

        printf("\nConsultar outro produto (s/n)? ");
        scanf(" %c", &q);
    } while (q == 's' || q == 'S');  
}

void editarproduto() {
    char buscarprod[50];  
    char q;               

    do {
        printf("\n-- EDITAR PRODUTO --\n");
        printf("Digite o nome do produto: ");
        scanf(" %[^\n]s", buscarprod);  

        // Abre o arquivo "produto.txt" em modo leitura
        FILE *file = fopen("produto.txt", "r");
        if (!file) {
            perror("Erro ao abrir o arquivo");
            return;
        }

        // Abre um arquivo temporário "temp.txt" em modo escrita
        FILE *tempFile = fopen("temp.txt", "w");
        if (!tempFile) {
            perror("Erro ao criar o arquivo temporário");
            fclose(file);
            return;
        }

        int encontrado = 0;  // Variável para verificar se o produto foi encontrado
        char nome[100], categoria[100];
        int quantidade;
        float preco;

        // Lê os dados do arquivo "produto.txt" até o final
        while (fscanf(file, "Nome: %[^\n]\nCategoria: %[^\n]\nQuantidade: %d\nPreco: %f\n\n",
                      nome, categoria, &quantidade, &preco) == 4) {
            // Verifica se o nome do produto lido corresponde ao nome informado
            int iguais = 1;
            int j = 0;
            while (buscarprod[j] != '\0' || nome[j] != '\0') {
                if (buscarprod[j] != nome[j]) {
                    iguais = 0;
                    break;
                }
                j++;
            }

            // Se o produto foi encontrado
            if (iguais) {
                printf("\nProduto encontrado:\n");
                printf("Novo Nome: ");
                scanf(" %[^\n]s", nome);
                printf("Nova Categoria: ");
                scanf(" %[^\n]s", categoria);
                printf("Nova Quantidade: ");
                scanf("%d", &quantidade);
                printf("Novo Preco: ");
                scanf("%f", &preco);

                // Escreve os dados atualizados no arquivo temporário
                fprintf(tempFile, "Nome: %s\nCategoria: %s\nQuantidade: %d\nPreco: %.2f\n\n",
                        nome, categoria, quantidade, preco);

                encontrado = 1;  // Marca que o produto foi encontrado e editado
            } else {
                // Se o produto não foi encontrado, copia os dados inalterados para o arquivo temporário
                fprintf(tempFile, "Nome: %s\nCategoria: %s\nQuantidade: %d\nPreco: %.2f\n\n",
                        nome, categoria, quantidade, preco);
            }
        }

        // Fecha ambos os arquivos após a leitura e escrita
        fclose(file);
        fclose(tempFile);

        // Se o produto foi editado, substitui o arquivo original pelo arquivo temporário
        if (encontrado) {
            remove("produto.txt");  // Remove o arquivo original
            rename("temp.txt", "produto.txt");  // Renomeia o arquivo temporário para o nome do arquivo original
            printf("\nProduto editado com sucesso!\n");
        } else {
            printf("Produto nao encontrado.\n");
        }

        printf("\nEditar outro produto (s/n)? ");
        scanf(" %c", &q);
    } while (q == 's' || q == 'S');  
}

void excluirproduto() {
    char buscarprod[50];
    char q;

    do {
        printf("\n-- EXCLUIR PRODUTO --\n");
        printf("Digite o nome do produto: ");
        scanf(" %[^\n]s", buscarprod);

        FILE *file = fopen("produto.txt", "r");
        if (!file) {
            perror("Erro ao abrir o arquivo");
            return;
        }

        FILE *tempFile = fopen("temp.txt", "w");
        if (!tempFile) {
            perror("Erro ao criar o arquivo temporário");
            fclose(file);
            return;
        }

        int encontrado = 0;
        char nome[100], categoria[100];
        int quantidade;
        float preco;

        // Loop para ler cada produto no arquivo
        while (fscanf(file, "Nome: %[^\n]\nCategoria: %[^\n]\nQuantidade: %d\nPreco: %f\n\n",
                      nome, categoria, &quantidade, &preco) == 4) {
            int iguais = 1;
            int j = 0;

            // Comparar as strings manualmente
            while (buscarprod[j] != '\0' && nome[j] != '\0') {
                if (buscarprod[j] != nome[j]) {
                    iguais = 0;
                    break;
                }
                j++;
            }

            // Certificar-se que as strings têm o mesmo tamanho
            if (buscarprod[j] != nome[j]) {
                iguais = 0;
            }

            // Se o nome for encontrado, não gravamos o produto no arquivo temporário
            if (iguais) {
                printf("\nProduto encontrado. Excluindo...\n");
                encontrado = 1;  // Marcar que o produto foi encontrado

                // Atualizar o vetor de produtos
                for (int i = 0; i < totalProdutos; i++) {
                    int j = 0;
                    // Comparar o nome do produto no vetor com o nome digitado
                    while (cadastrarprodutos[i].nome[j] != '\0' && buscarprod[j] != '\0') {
                        if (cadastrarprodutos[i].nome[j] != buscarprod[j]) {
                            break;
                        }
                        j++;
                    }
                    // Se o nome for igual, exclui o produto do vetor
                    if (cadastrarprodutos[i].nome[j] == '\0' && buscarprod[j] == '\0') {
                        // Deslocar os elementos para remover o produto
                        for (int k = i; k < totalProdutos - 1; k++) {
                            cadastrarprodutos[k] = cadastrarprodutos[k + 1];
                        }
                        totalProdutos--;  // Decrementar o total de produtos
                        break;
                    }
                }
            } else {
                // Se o nome não foi encontrado, grava no arquivo temporário
                fprintf(tempFile, "Nome: %s\nCategoria: %s\nQuantidade: %d\nPreco: %.2f\n\n",
                        nome, categoria, quantidade, preco);
            }
        }

        fclose(file);
        fclose(tempFile);

        if (encontrado) {
            // Se o produto foi encontrado, substituímos o arquivo original pelo temporário
            remove("produto.txt");
            rename("temp.txt", "produto.txt");
            printf("\nProduto excluido com sucesso!\n");
        } else {
            // Se o produto não foi encontrado, informa o usuário
            printf("Produto nao encontrado.\n");
        }

        printf("\nExcluir outro produto (s/n)? ");
        scanf(" %c", &q);
    } while (q == 's' || q == 'S');
}


void listarproduto() {
    printf("\n-- Listar Produto --\n");

    // Abre o arquivo "produto.txt" em modo leitura
    FILE *file = fopen("produto.txt", "r");
    if (!file) {
        // Se o arquivo não for encontrado ou não puder ser aberto, exibe um erro e retorna
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Declara variáveis para armazenar os dados de cada produto
    char nome[100], categoria[100];
    int quantidade;
    float preco;

    // Lê os dados do arquivo enquanto houver informações válidas
    while (fscanf(file, "Nome: %[^\n]\nCategoria: %[^\n]\nQuantidade: %d\nPreco: %f\n\n",
                  nome, categoria, &quantidade, &preco) == 4) {
        printf("Nome: %s\n", nome);
        printf("Categoria: %s\n", categoria);
        printf("Quantidade: %d\n", quantidade);
        printf("Preco: %.2f\n", preco);
        printf("--------------------------\n"); 
    }

    fclose(file);
}

void cadastropessoa() {
    FILE *file = fopen(CLIENTE_FILE, "a+"); // Usando "a+" para permitir leitura e escrita
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char q;
    do {
        if (totalClientes >= 50) {
            printf("Limite de clientes cadastrados atingido!\n");
            break;
        }

        printf("\n-- CADASTRO DE CLIENTES --\n");

        // Verificação de CPF duplicado
        int aux;
        int CPFEXISTE = 0;

        printf("Digite o seu nome: ");
        scanf(" %[^\n]s", cadastrarpessoas[totalClientes].nome);
        printf("Digite seu CPF: "); 
        scanf("%d", &aux);

        // Rewind do arquivo para garantir que vamos ler desde o início
        rewind(file);

        // Verifica se o CPF já existe no arquivo
        Cliente clienteAtual;
        while (fscanf(file, "Nome: %[^\n]\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n", 
                      clienteAtual.nome, &clienteAtual.cpf, &clienteAtual.rg, &clienteAtual.dnascimento) != EOF) {
            if (clienteAtual.cpf == aux) {
                printf("CPF %d ja esta cadastrado.\n", aux);
                CPFEXISTE = 1;
                break;
            }
        }

        if (CPFEXISTE) {
            continue;  // Se o CPF já existir, vai para a próxima iteração
        }

        // Dados do novo cliente
        cadastrarpessoas[totalClientes].cpf = aux;
        printf("Digite seu RG: ");
        scanf("%d", &cadastrarpessoas[totalClientes].rg);
        printf("Digite sua data de nascimento (DDMMAAAA): ");
        scanf("%d", &cadastrarpessoas[totalClientes].dnascimento);

        // Escreve no arquivo
        fprintf(file, "Nome: %s\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n",
                cadastrarpessoas[totalClientes].nome,
                cadastrarpessoas[totalClientes].cpf,
                cadastrarpessoas[totalClientes].rg,
                cadastrarpessoas[totalClientes].dnascimento);

        totalClientes++;  // Incrementa o número de clientes

        printf("\nRegistrar outro cliente (s/n)? ");
        scanf(" %c", &q);

    } while ((q == 's' || q == 'S'));

    fclose(file);  // Fecha o arquivo
}


void consultarcliente() {
    int aux;
    char q;

    do {
        // Abre o arquivo original "cliente.txt" em modo leitura
        FILE *file = fopen(CLIENTE_FILE, "r");
        if (!file) {
            // Caso o arquivo não possa ser aberto, exibe uma mensagem de erro e retorna
            perror("Erro ao abrir o arquivo");
            return;
        }

        printf("\n-- CONSULTAR CLIENTE --\n");
        printf("Digite o CPF do cliente: ");
        scanf("%d", &aux);
        int encontrado = 0;

        Cliente clienteAtual;
        // Lê os dados do arquivo original até o final
        while (fscanf(file, "Nome: %[^\n]\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n",
                      clienteAtual.nome,
                      &clienteAtual.cpf,
                      &clienteAtual.rg,
                      &clienteAtual.dnascimento) != EOF) {
            if (clienteAtual.cpf == aux) {
                // Exibe os dados do cliente encontrado
                printf("\nCliente encontrado:\n");
                printf("Nome: %s\nCPF: %d\nRG: %d\nData de Nascimento: %d\n",
                       clienteAtual.nome, clienteAtual.cpf, clienteAtual.rg, clienteAtual.dnascimento);
                encontrado = 1;
                break;
            }
        }

        fclose(file);

        if (!encontrado) {
            printf("CPF %d nao encontrado.\n", aux);
        }

        printf("\nConsultar outro cliente (s/n)? ");
        scanf(" %c", &q);
    } while ((q == 's' || q == 'S'));
}

void editarcliente() {
    int aux;
    char q;
    int encontrado;

    do {
        printf("\n-- Editar cliente --\n");
        printf("Digite o CPF do cliente: ");
        scanf("%d", &aux);

        FILE *file = fopen(CLIENTE_FILE, "r");
        if (!file) {
            perror("Erro ao abrir o arquivo");
            return;
        }

        // Cria um arquivo temporário para armazenar os clientes atualizados
        FILE *tempFile = fopen("temp.txt", "w");
        if (!tempFile) {
            perror("Erro ao criar arquivo temporario");
            fclose(file);
            return;
        }

        Cliente clienteAtual;
        encontrado = 0;

        while (fscanf(file, "Nome: %[^\n]\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n",
                      clienteAtual.nome,
                      &clienteAtual.cpf,
                      &clienteAtual.rg,
                      &clienteAtual.dnascimento) != EOF) {
            if (clienteAtual.cpf == aux) {
                printf("Cliente encontrado! Atualize os dados:\n");
                printf("Nome novo: ");
                scanf(" %[^\n]s", clienteAtual.nome);
                printf("CPF novo: ");
                scanf("%d", &clienteAtual.cpf);
                printf("RG novo: ");
                scanf("%d", &clienteAtual.rg);
                printf("Data de nascimento nova: ");
                scanf("%d", &clienteAtual.dnascimento);
                printf("Dados atualizados com sucesso!\n");
                encontrado = 1;
            }
            //Escreve os dados (atualizados ou não) no arquivo temporário
            fprintf(tempFile, "Nome: %s\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n",
                    clienteAtual.nome, clienteAtual.cpf, clienteAtual.rg, clienteAtual.dnascimento);
        }

        fclose(file);
        fclose(tempFile);

        if (!encontrado) {
            printf("CPF %d nao encontrado.\n", aux);
        } else {
            remove(CLIENTE_FILE); // Exclui o arquivo original
            rename("temp.txt", CLIENTE_FILE); // Renomeia o arquivo temporário para o nome do arquivo original
        }

        printf("\nDeseja editar outro cliente (s/n)? ");
        scanf(" %c", &q);
    } while ((q == 's' || q == 'S'));
}

void excluircliente() {
    int aux;
    char q;
    int encontrado;

    do {
        printf("\n-- Excluir Cliente --\n");
        printf("Digite o CPF do cliente: ");
        scanf("%d", &aux);

    // Abre o arquivo original "cliente.txt" em modo leitura
        FILE *file = fopen(CLIENTE_FILE, "r");
        if (!file) {
            perror("Erro ao abrir o arquivo");
            return;
        }

    // Cria um arquivo temporário para armazenar os clientes restantes
        FILE *tempFile = fopen("temp.txt", "w");
        if (!tempFile) {
            perror("Erro ao criar o arquivo temporario");
            fclose(file);
            return;
        }

        Cliente clienteAtual;
        encontrado = 0; // Inicializa a variável encontrado como 0 (não encontrado)

        while (fscanf(file, "Nome: %[^\n]\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n",
                      clienteAtual.nome,
                      &clienteAtual.cpf,
                      &clienteAtual.rg,
                      &clienteAtual.dnascimento) != EOF) {
            if (clienteAtual.cpf == aux) {
                // Exclui o cliente (não escreve no arquivo temporário)
                printf("Cliente com CPF %d encontrado. Excluindo...\n", aux);
                encontrado = 1;
                continue; 
            }
             // Se o cliente não for o desejado, escreve os dados no arquivo temporário
            fprintf(tempFile, "Nome: %s\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n",
                    clienteAtual.nome, clienteAtual.cpf, clienteAtual.rg, clienteAtual.dnascimento);
        }

        fclose(file);
        fclose(tempFile);

        if (!encontrado) {
            printf("CPF %d nao encontrado.\n", aux);
            remove("temp.txt"); 
        } else {
            remove(CLIENTE_FILE); // Exclui o arquivo original        
            rename("temp.txt", CLIENTE_FILE); // Renomeia o arquivo temporário para o nome do arquivo original
            printf("Cliente excluido com sucesso!\n");
        }

        printf("\nDeseja excluir outro cliente (s/n)? ");
        scanf(" %c", &q);
    } while ((q == 's' || q == 'S'));
}

void listarclientes() {
    FILE *file = fopen(CLIENTE_FILE, "r");
    
    // Verifica se o arquivo foi aberto corretamente
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Exibe o título da listagem de clientes
    printf("\n-- LISTAR CLIENTES --\n");

    // Declara uma variável para armazenar os dados de um cliente
    Cliente clienteAtual;

    // Lê os dados do arquivo até o final, enquanto o formato de leitura estiver correto
    while (fscanf(file, "Nome: %[^\n]\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n",
                  clienteAtual.nome,              
                  &clienteAtual.cpf,              
                  &clienteAtual.rg,               
                  &clienteAtual.dnascimento) == 4) { 
        // Exibe as informações do cliente
        printf("Nome: %s | CPF: %d | RG: %d | Data de Nascimento: %d\n",
               clienteAtual.nome,        
               clienteAtual.cpf,         
               clienteAtual.rg,          
               clienteAtual.dnascimento); 
    }

    fclose(file);
}


void salvarProdutos() {
    // Abre o arquivo "produto.txt" em modo escrita (substitui o conteúdo existente)
    FILE *file = fopen("produto.txt", "w");
    
    // Verifica se o arquivo foi aberto corretamente
    if (!file) {
        // Caso o arquivo não tenha sido aberto, exibe uma mensagem de erro
        perror("Erro ao salvar produto.txt");
        return;
    }

    // Itera sobre todos os produtos cadastrados
    for (int i = 0; i < totalProdutos; i++) {
        // Escreve os dados de cada produto no arquivo, formatados de acordo com o padrão
        fprintf(file, "Nome: %s\nCategoria: %s\nQuantidade: %d\nPreco: %.2f\n\n",
                cadastrarprodutos[i].nome,        
                cadastrarprodutos[i].categoria,   
                cadastrarprodutos[i].quantidade,  
                cadastrarprodutos[i].preco);     
    }

    fclose(file);
}

void salvarClientes() {
    // Abre o arquivo "cliente.txt" em modo escrita (substitui o conteúdo existente)
    FILE *file = fopen("cliente.txt", "w");
    
    // Verifica se o arquivo foi aberto corretamente
    if (!file) {
        // Caso o arquivo não tenha sido aberto, exibe uma mensagem de erro
        perror("Erro ao salvar cliente.txt");
        return;
    }

    // Itera sobre todos os clientes cadastrados
    for (int i = 0; i < totalClientes; i++) {
        // Escreve os dados de cada cliente no arquivo, formatados de acordo com o padrão
        fprintf(file, "Nome: %s\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n",
                cadastrarpessoas[i].nome,    
                cadastrarpessoas[i].cpf,    
                cadastrarpessoas[i].rg,     
                cadastrarpessoas[i].dnascimento); 
    }

    fclose(file);
}

void realizarvenda() {
    char buscarprod[50];   
    int cpfCliente;         
    int encontradoProduto = -1, encontradoCliente = -1; // Variáveis para verificar se o produto e o cliente foram encontrados
    char q;                 

    printf("\n-- REALIZAR VENDA --\n");

    // Carregar dados dos clientes e produtos antes de realizar vendas
    carregarClientes();
    carregarProdutos();

    do {
        // Solicita o nome do produto que o cliente deseja comprar
        printf("Digite o nome do produto que deseja comprar: ");
        scanf(" %[^\n]s", buscarprod);

        // Procura pelo produto digitado no estoque
        for (int i = 0; i < totalProdutos; i++) {
            int iguais = 1;
            // Compara cada caractere do nome do produto digitado com o nome do produto no estoque
            for (int j = 0; buscarprod[j] != '\0' || cadastrarprodutos[i].nome[j] != '\0'; j++) {
                if (buscarprod[j] != cadastrarprodutos[i].nome[j]) {
                    iguais = 0;  // Se não encontrar uma correspondência, define iguais como 0
                    break;
                }
            }
            if (iguais) {
                encontradoProduto = i; // Produto encontrado
                break;
            }
        }

        // Se o produto não for encontrado, exibe mensagem e retorna
        if (encontradoProduto == -1) {
            printf("\nProduto nao encontrado!\n");
            return;
        }

        // Verifica se há estoque suficiente do produto
        if (cadastrarprodutos[encontradoProduto].quantidade <= 0) {
            printf("\nEstoque insuficiente para o produto '%s'.\n", cadastrarprodutos[encontradoProduto].nome);
            return;
        }

        // Solicita o CPF do cliente
        printf("\nDigite o CPF do cliente: ");
        scanf("%d", &cpfCliente);

        // Procura o cliente pelo CPF
        for (int i = 0; i < totalClientes; i++) {
            if (cadastrarpessoas[i].cpf == cpfCliente) {
                encontradoCliente = i;  // Cliente encontrado
                break;
            }
        }

        // Se o cliente não for encontrado, oferece a opção de cadastro
        if (encontradoCliente == -1) {
            printf("Cliente nao encontrado!\n");
            printf("Deseja cadastrar o cliente? (s/n): ");
            scanf(" %c", &q);

            // Se o usuário optar por cadastrar, chama a função de cadastro de cliente
            if (q == 's' || q == 'S') {
                cadastropessoa();
                encontradoCliente = totalClientes - 1;  // Novo cliente é o último adicionado
            } else {
                return;  // Se não desejar cadastrar, sai da função
            }
        }

        // Atualiza a quantidade do produto após a venda
        cadastrarprodutos[encontradoProduto].quantidade -= 1;

        // Registra a venda
        vendas[totalVendas].cpfCliente = cpfCliente;
        vendas[totalVendas].valorVenda = cadastrarprodutos[encontradoProduto].preco;
        vendas[totalVendas].vendidos = 1;

        // Copia o nome do produto para a venda
        int j = 0;
        while (cadastrarprodutos[encontradoProduto].nome[j] != '\0') {
            vendas[totalVendas].nomeProduto[j] = cadastrarprodutos[encontradoProduto].nome[j];
            j++;
        }
        vendas[totalVendas].nomeProduto[j] = '\0';

        // Registra a venda no arquivo "caixa.txt"
        FILE *caixaFile = fopen("caixa.txt", "a");
        if (!caixaFile) {
            perror("Erro ao abrir caixa.txt");
            return;
        }

        // Escreve os detalhes da venda no arquivo
        fprintf(caixaFile, "Produto: %s\nCliente (CPF): %d\nQuantidade: %d\nValor: %.2f\n\n",
                vendas[totalVendas].nomeProduto,
                vendas[totalVendas].cpfCliente,
                vendas[totalVendas].vendidos,
                vendas[totalVendas].valorVenda);

        fclose(caixaFile);  
        totalVendas++;  // Incrementa o contador de vendas

        // Exibe os detalhes da venda realizada
        printf("Venda realizada com sucesso!\n");
        printf("\nProduto: %s\nCliente (CPF): %d\nPreco: %.2f\n", 
               cadastrarprodutos[encontradoProduto].nome, cpfCliente, cadastrarprodutos[encontradoProduto].preco);

        printf("\nFazer outra venda (s/n)? ");
        scanf(" %c", &q);

    } while ((q == 's' || q == 'S'));  
    // Salva os dados atualizados de produtos e clientes após as vendas
    salvarProdutos();
    salvarClientes();
}


void totalPorCliente() {
    int cpfLido, cpfCliente;
    float valorLido, total = 0.0;
    char q;

    do {
        total = 0.0; // Reiniciar o total para cada consulta
        printf("Digite o CPF do cliente para calcular o total: ");
        scanf("%d", &cpfCliente);

        FILE *caixaFile = fopen(CAIXA_FILE, "r");
        if (!caixaFile) {
            perror("Erro ao abrir o arquivo caixa.txt");
            return;
        }

        // Leitura e cálculo do total
        while (fscanf(caixaFile, "Produto: %*s\nCliente (CPF): %d\nQuantidade: %*d\nValor: %f\n\n", &cpfLido, &valorLido) != EOF) {
            if (cpfLido == cpfCliente) {
                total += valorLido;
            }
        }

        fclose(caixaFile);

        if (total > 0) {
            printf("\nO total a pagar para o cliente (CPF: %d) e: RS %.2f\n", cpfCliente, total);
        } else {
            printf("\nNenhuma venda encontrada para o cliente (CPF: %d).\n", cpfCliente);
        }

        printf("\nDeseja calcular para outro cliente? (s/n): ");
        scanf(" %c", &q);

    } while (q == 's' || q == 'S');
}

void listarCompras() {
    FILE *caixaFile = fopen("caixa.txt", "r");
    if (!caixaFile) {
        perror("Erro ao abrir o arquivo caixa.txt");
        return;
    }

    // Abrir o arquivo caixatotal.txt para gravar as compras
    FILE *caixaTotalFile = fopen("caixatotal.txt", "w");
    if (!caixaTotalFile) {
        perror("Erro ao abrir o arquivo caixatotal.txt");
        fclose(caixaFile);
        return;
    }

    // Escrever cabeçalho no arquivo caixatotal.txt
    fprintf(caixaTotalFile, "-- LISTA DE TODAS AS COMPRAS --\n");

    // Variáveis auxiliares para leitura do arquivo
    char nomeProduto[50];
    int cpfCliente, quantidade;
    float valorVenda;


    // Leitura e processamento das vendas
    while (fscanf(caixaFile, "Produto: %[^\n]\nCliente (CPF): %d\nQuantidade: %d\nValor: %f\n\n",
                  nomeProduto, &cpfCliente, &quantidade, &valorVenda) != EOF) {

        // Verificar se a compra já existe (mesmo produto e cliente)
        int encontrado = 0;
        for (int i = 0; i < numCompras; i++) {
            int igual = 1;
            for (int j = 0; compras[i].nomeProduto[j] != '\0' || nomeProduto[j] != '\0'; j++) {
                if (compras[i].nomeProduto[j] != nomeProduto[j]) {
                    igual = 0;
                    break;
                }
            }
            if (igual && compras[i].cpfCliente == cpfCliente) {
                compras[i].quantidade += quantidade;  // Soma a quantidade
                encontrado = 1;
                break;
            }
        }

        // Se não encontrou, adicionar uma nova compra
        if (!encontrado) {
            compras[numCompras].cpfCliente = cpfCliente;
            compras[numCompras].quantidade = quantidade;
            compras[numCompras].valorVenda = valorVenda;

            // Atribuir o nome do produto manualmente (sem strcpy)
            int i = 0;
            while (nomeProduto[i] != '\0') {
                compras[numCompras].nomeProduto[i] = nomeProduto[i];
                i++;
            }
            compras[numCompras].nomeProduto[i] = '\0';  // Terminar a string

            numCompras++;
        }
    }

    // Caso não haja compras registradas
    if (numCompras == 0) {
        fprintf(caixaTotalFile, "Nenhuma compra registrada ate o momento.\n");
        printf("Nenhuma compra registrada.\n");
    } else {
        // Escrever no arquivo e no terminal as compras
        for (int i = 0; i < numCompras; i++) {
            fprintf(caixaTotalFile, "Produto: %s\n", compras[i].nomeProduto);
            fprintf(caixaTotalFile, "Cliente (CPF): %d\n", compras[i].cpfCliente);
            fprintf(caixaTotalFile, "Quantidade: %d\n", compras[i].quantidade);
            fprintf(caixaTotalFile, "Valor: %.2f\n", compras[i].valorVenda);
            fprintf(caixaTotalFile, "------------------------------\n");

            // Também exibe no terminal
            printf("Produto: %s\n", compras[i].nomeProduto);
            printf("Cliente (CPF): %d\n", compras[i].cpfCliente);
            printf("Quantidade: %d\n", compras[i].quantidade);
            printf("Valor: %.2f\n", compras[i].valorVenda);
            printf("------------------------------\n");
        }
    }

    // Fechar os arquivos
    fclose(caixaFile);
    fclose(caixaTotalFile);

}

void vendasprodutos() {
    FILE *caixaFile = fopen("caixa.txt", "r");
    if (!caixaFile) {
        perror("Erro ao abrir o arquivo caixa.txt");
        return;
    }

    int cpfLido, quantidadeLida;
    float valorLido;
    int totalVendidos = 0;

    // Leitura do arquivo e somando as quantidades de produtos vendidos
    while (fscanf(caixaFile, "Produto: %*s\nCliente (CPF): %d\nQuantidade: %d\nValor: %f\n\n", &cpfLido, &quantidadeLida, &valorLido) != EOF) {
        totalVendidos += quantidadeLida;
    }

    fclose(caixaFile);

    // Exibir o total de produtos vendidos
    printf("\nTotal de produtos vendidos: %d\n", totalVendidos);
}

void carregarClientes() {
    // Abre o arquivo "cliente.txt" em modo leitura
    FILE *file = fopen("cliente.txt", "r");
    
    // Verifica se o arquivo foi aberto corretamente
    if (!file) {
        // Caso o arquivo não tenha sido aberto, exibe uma mensagem de erro
        perror("Erro ao abrir cliente.txt");
        return;
    }

    // Inicializa o contador de clientes
    totalClientes = 0;

    // Lê o conteúdo do arquivo até o final
    // A função fscanf vai ler as informações de cada cliente (nome, CPF, RG e data de nascimento)
    while (fscanf(file, "Nome: %[^\n]\nCPF: %d\nRG: %d\nData de Nascimento: %d\n\n",
                  cadastrarpessoas[totalClientes].nome,   
                  &cadastrarpessoas[totalClientes].cpf,    
                  &cadastrarpessoas[totalClientes].rg,     
                  &cadastrarpessoas[totalClientes].dnascimento) == 4) { 
        totalClientes++; // Incrementa o contador de clientes
    }

    // Fecha o arquivo após a leitura
    fclose(file);
}

void carregarProdutos() {
    // Abre o arquivo "produto.txt" em modo leitura
    FILE *file = fopen("produto.txt", "r");
    
    // Verifica se o arquivo foi aberto corretamente
    if (!file) {
        // Caso o arquivo não tenha sido aberto, exibe uma mensagem de erro
        perror("Erro ao abrir produto.txt");
        return;
    }

    // Inicializa o contador de produtos
    totalProdutos = 0;

    // Lê o conteúdo do arquivo até o final
    // A função fscanf vai ler as informações de cada produto (nome, categoria, quantidade e preço)
    while (fscanf(file, "Nome: %[^\n]\nCategoria: %[^\n]\nQuantidade: %d\nPreco: %f\n\n",
                  cadastrarprodutos[totalProdutos].nome,     
                  cadastrarprodutos[totalProdutos].categoria, 
                  &cadastrarprodutos[totalProdutos].quantidade, 
                  &cadastrarprodutos[totalProdutos].preco) == 4) { 
        totalProdutos++; // Incrementa o contador de produtos
    }

    fclose(file);
}
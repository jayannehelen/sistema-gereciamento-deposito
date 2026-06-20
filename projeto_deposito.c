#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct Produto{
    int codProduto;
    char nomeProduto[100];
    char descricaoProduto[100];
    float precoProduto;
    int qntProduto;

    struct Produto * prox;
    struct Produto *ant;

} Produto;

typedef struct Funcionario {
    char cpf[12]; 
    char nome_usuario[50];

    struct Funcionario *prox;
    struct Funcionario *ant;
} Funcionario;

Produto *inicioProduto = NULL;
Produto *fimProduto = NULL;
int qtdProdutosEstoque = 0;

Funcionario *inicio_funcionarios = NULL;
Funcionario *fim_funcionarios = NULL;
int qtdFuncionarios = 0;

int estoqueMinimo = 2;

// PRODUTO 
Produto * buscarProduto(int cod){
    Produto * aux = inicioProduto;
    while(aux != NULL){
        if(aux->codProduto == cod){
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

// RF001
void cadastrarProdutoEstoque(int cod, char *nome, char *descricao, float preco, int quantidade){
   
    printf("\n-------------------| ADICIONAR NO ESTOQUE |-------------------\n");

    if(preco > 0 && quantidade > 0 && cod > 0){

        Produto * novo = malloc(sizeof(Produto));
        novo->codProduto = cod;
        strcpy(novo->nomeProduto, nome);
        strcpy(novo->descricaoProduto, descricao);
        novo->precoProduto = preco;
        novo->qntProduto = quantidade;
        novo->prox = NULL;
        novo->ant = NULL;

        if(inicioProduto == NULL){ 
            inicioProduto = novo;
            fimProduto = novo;
            qtdProdutosEstoque++;

            printf("Produto de codigo %d adicionado no estoque!\n", novo->codProduto);
        }else{ 
            if (buscarProduto(cod) == NULL) {
                if (novo->codProduto < inicioProduto->codProduto) { //caso do inicio
                    inicioProduto->ant = novo; 
                    novo->ant = NULL;
                    novo->prox = inicioProduto;
                    inicioProduto = novo;

                } else if(novo->codProduto >= fimProduto->codProduto){ //caso do fim
                    fimProduto->prox = novo;
                    novo->prox = NULL;
                    novo->ant = fimProduto;
                    fimProduto = novo;

                }else{
                    //meio ...
                    Produto* aux = inicioProduto->prox;
                    while(aux != NULL && novo->codProduto >= aux->codProduto){
                        aux = aux->prox;
                    }

                    aux->ant->prox = novo;
                    novo->prox = aux;
                    novo->ant = aux->ant;
                    aux->ant = novo;
                }
                qtdProdutosEstoque++;

                printf("Produto de codigo %d adicionado no estoque!\n", novo->codProduto);

            } else {
                printf("Já existe um produto com esse codigo! Se quer alterar o estoque procure a opcao de alteracao.\n");
    };
        }
    } else {
        printf("Impossivel adicionar. Confira se o preco, quantidade ou codigo sao maiores que 0!\n");
    }
}

// RF002.1 (falta atualizacao - aumentar quantidade estoque)
void saidaEstoque(int cod){
    int qtdTemp;

    printf("\n-------------------| RETIRAR DO ESTOQUE |-------------------\n");
    Produto *aux = buscarProduto(cod);
    if (aux == NULL){
        printf("Produto %d inexistente no estoque.\n", cod);
    } else {
        
        printf("\n | PRODUTO | \n");
        printf("Codigo: %d \n", aux->codProduto);
        printf("Nome: %s \n", aux->nomeProduto);
        printf("Descricao: %s \n", aux->descricaoProduto);
        printf("Preco: R$ %.2lf \n", aux->precoProduto);
        printf("Quantidade: %d \n", aux->qntProduto);

        printf("\nDigite quantos desse produto voce deseja retirar: ");
        while (scanf("%d", &qtdTemp) != 1) {
            printf("\nErro: Digite apenas numeros.\n");

            while (getchar() != '\n');

            printf("Digite quantos desse produto voce deseja retirar: ");
        }

        if (qtdTemp > aux->qntProduto) {
            printf("AVISO: IMPOSSIVEL RETIRADA DE ESTOQUE!\n");
            printf("A quantidade de estoque do produto e maior que a quantidade selecionada.\n");
        } else {
            aux->qntProduto -= qtdTemp;
            // printf("Agora o estoque de %s e %d produtos\n", aux->nomeProduto, aux->qntProduto);

            printf("\n | PRODUTO | \n");
            printf("Codigo: %d \n", aux->codProduto);
            printf("Nome: %s \n", aux->nomeProduto);
            printf("Descricao: %s \n", aux->descricaoProduto);
            printf("Preco: R$ %.2lf \n", aux->precoProduto);
            printf("Quantidade: %d \n", aux->qntProduto);

            // RF005
            if (aux->qntProduto <= estoqueMinimo){
                printf("\n-------------------| AVISO IMPORTANTE |-------------------\n");
                printf("Ponto minimo de reabastecimento alcancado!\n");
                printf("Produto %s (codigo %d) com apenas %d em estoque.\n", aux->nomeProduto, aux->codProduto, aux->qntProduto);
            }
            
        }
    }
}

void atualizarEstoqueProduto(int codTemp){
    printf("\n-------------------| ATUALIZAR ESTOQUE |-------------------\n");
    
    int qtdTemp;
    
    Produto * aux = buscarProduto(codTemp);

    if (aux == NULL) {
        printf("Produto %d inexistente no estoque.\n", codTemp);
    } else {
        
        printf("\n | PRODUTO | \n");
        printf("Codigo: %d \n", aux->codProduto);
        printf("Nome: %s \n", aux->nomeProduto);
        printf("Descricao: %s \n", aux->descricaoProduto);
        printf("Preco: R$ %.2lf \n", aux->precoProduto);
        printf("Quantidade: %d \n", aux->qntProduto);

        printf("\nDigite quantas unidades voce deseja adicionar: ");
        while (scanf("%d", &qtdTemp) != 1) {
            printf("\nErro: Digite apenas numeros.\n");

            while (getchar() != '\n');

            printf("Digite quantas unidades voce deseja adicionar: ");
        }

        aux->qntProduto += qtdTemp;

        printf("Estoque atualizado com sucesso!\n");

        printf("\n | PRODUTO | \n");
        printf("Codigo: %d \n", aux->codProduto);
        printf("Nome: %s \n", aux->nomeProduto);
        printf("Descricao: %s \n", aux->descricaoProduto);
        printf("Preco: R$ %.2lf \n", aux->precoProduto);
        printf("Quantidade: %d \n", aux->qntProduto);
    }
}

// Listar por filtro
void listarTodosProdutos(){
    Produto * aux = inicioProduto;

    printf("\n-------------------| VER PRODUTOS |-------------------\n");
    while(aux != NULL){
        printf("Codigo: %d \n", aux->codProduto);
        printf("Nome: %s \n", aux->nomeProduto);
        printf("Descricao: %s \n", aux->descricaoProduto);
        printf("Preco: R$ %.2lf \n", aux->precoProduto);
        printf("Quantidade: %d \n", aux->qntProduto);
        printf("\n");
        //... fazer os demais dados
        aux = aux->prox;
    }
    if (inicioProduto == NULL){
        printf("Nao ha produtos cadastrados.\n");
    }
    
}

void listarProdutosDisponiveisPreco(double limiteI, double limiteS){
    printf("\n-------------------| VER PRODUTOS |-------------------\n");
    printf("Filtrado por Preco: R$ %.2lf - %.2lf\n", limiteI, limiteS);

    Produto * aux = inicioProduto;
    int contador=0;

    while(aux != NULL){
        if (aux->precoProduto >= limiteI && aux->precoProduto <= limiteS) {
            contador += 1;
            printf("Codigo: %d \n", aux->codProduto);
            printf("Nome: %s \n", aux->nomeProduto);
            printf("Descricao: %s \n", aux->descricaoProduto);
            printf("Preco: R$ %.2lf \n", aux->precoProduto);
            printf("Quantidade: %d \n", aux->qntProduto);
            printf("\n");
        }
        
        aux = aux->prox;
    }

    if (contador == 0) {
        printf("\nNao existe nenhum produto nessa faixa de preco!\n");
    }
}

void listarProdutosDisponiveisCodigo(int codMenor, int codMaior){
    printf("\n-------------------| VER PRODUTOS |-------------------\n");
    printf("Filtrado por codigo: %d - %d\n", codMenor, codMaior);

    Produto * aux = inicioProduto;
    int contador=0;

    while(aux != NULL){
        if (aux->codProduto >= codMenor && aux->codProduto <= codMaior) {
            contador += 1;
            printf("Codigo: %d \n", aux->codProduto);
            printf("Nome: %s \n", aux->nomeProduto);
            printf("Descricao: %s \n", aux->descricaoProduto);
            printf("Preco: R$ %.2lf \n", aux->precoProduto);
            printf("Quantidade: %d \n", aux->qntProduto);
            printf("\n");
        }
        
        aux = aux->prox;
    }

    if (contador == 0) {
        printf("\nNao existe nenhum produto nessa faixa de codigo!\n");
    }
}

// RF003
void consultarProdutoCodigo(int cod){
    printf("\n-------------------| CONSULTA DE PRODUTO |-------------------\n");
    printf("Consulta por codigo: %d\n\n", cod);

    Produto * aux = buscarProduto(cod);
    if (aux == NULL) {
       printf("Produto inexistente.\n");

    } else {
        printf("Codigo: %d \n", aux->codProduto);
        printf("Nome: %s \n", aux->nomeProduto);
        printf("Descricao: %s \n", aux->descricaoProduto);
        printf("Preco: R$ %.2lf \n", aux->precoProduto);
        printf("Quantidade: %d \n", aux->qntProduto);
    }
}

void consultarProdutoNome(char *nome){
    printf("\n-------------------| CONSULTA DE PRODUTO |-------------------\n");
    printf("Consulta por nome: %s\n\n", nome);

    Produto *aux = inicioProduto;
    int existe = 0;

    while(aux != NULL){
        if(strstr(aux->nomeProduto, nome) != NULL){
            printf("Codigo: %d\n", aux->codProduto);
            printf("Nome: %s\n", aux->nomeProduto);
            printf("Preco: %.2f\n", aux->precoProduto);
            printf("Quantidade: %d\n\n", aux->qntProduto);

            existe = 1;
        }
        aux = aux->prox;
    }
    if(!existe){
        printf("Nenhum produto encontrado.\n");
    }
}

// FUNCIONARIO
int cpfValido(char *cpf) {
    if (strlen(cpf) != 11)
        return 0;

    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i]))
            return 0;
    }

    return 1;
}

Funcionario *buscarPorCPF(char *cpf) {
    Funcionario *aux = inicio_funcionarios;

    while (aux != NULL) {
        if (strcmp(aux->cpf, cpf) == 0){
            return aux;
        }

        aux = aux->prox;
    }

    return NULL;
}

void addFuncionarios(char *cpf, char *nome_usuario) {

    if (cpfValido(cpf) && buscarPorCPF(cpf) == NULL) {
        Funcionario *novo = malloc(sizeof(Funcionario));
        strcpy(novo->cpf, cpf);
        strcpy(novo->nome_usuario, nome_usuario);
        novo->prox = NULL;
        novo->ant = NULL;

        if (inicio_funcionarios == NULL) { 
            inicio_funcionarios = novo;
            fim_funcionarios = novo;
        } else { 
            novo->ant = fim_funcionarios;
            fim_funcionarios->prox = novo;
            fim_funcionarios = novo;
        }
        
        qtdFuncionarios++;
        printf(">>> Cadastro realizado com sucesso! <<<\n");
    } else {
        printf("\nAVISO: Impossivel cadastrar usuario\n");
        printf("CPF invalido ou usuario ja cadastrado com esse CPF! Verifique e tente novamente.\n");
    }
}

void removerPorCPF(char *cpfBusca) {

    if (inicio_funcionarios != NULL) {
        Funcionario *aux = buscarPorCPF(cpfBusca);
        
        if (aux == NULL) {
            printf("Impossivel remover. Nao existe nenhum usuario com esse cpf!\n");
        } else {
            int confirmacao;
            printf("\nFuncionario encontrado: %s\n", aux->nome_usuario);
            printf("Tem certeza que deseja apagar este registro? (1 para Sim / 0 para Nao): ");
            scanf("%d", &confirmacao);

            if (confirmacao != 1) {
                printf("Acao cancelada. O(a) funcionario(a) %s nao foi apagado(a).\n", aux->nome_usuario);
            } else {
                if (inicio_funcionarios == aux){
                    inicio_funcionarios = aux->prox;

                    if(qtdFuncionarios == 1){
                        fim_funcionarios = NULL;
                    } else {
                        inicio_funcionarios->ant = NULL;
                    }
                } else if (fim_funcionarios == aux){
                    fim_funcionarios = aux->ant;
                    fim_funcionarios->prox = NULL;
                } else {
                    aux->ant->prox = aux->prox; 
                    aux->prox->ant = aux->ant;  
                }

                Funcionario *lixo = aux;

                free(lixo);
                qtdFuncionarios--;
                printf("\n\nFuncionario com CPF %s removido com sucesso!\n", cpfBusca);
            }
        }
    } else {
        printf("\nERRO: A lista de funcionarios esta vazia.\n");
    }
}

void listar_funcionarios(){

    Funcionario *aux = inicio_funcionarios;
    
    if (aux == NULL) {
        printf("\n\nNenhum funcionario cadastrado.\n");
    } else {
        while (aux != NULL) {
            printf("\nCPF: %s | Nome: %s\n", aux->cpf, aux->nome_usuario);
            aux = aux->prox;
        }
    }
}

void gerenciamentoFuncionarios(){

    int escolha;
    // gerenciamento de funcionarios
    char cpfTemp[12];
    char nomeTemp[50];
    do {
        printf("\n-------------------| GERENCIAMENTO DE FUNCIONARIOS |-------------------\n");
        printf("1. Cadastrar Funcionario\n");
        printf("2. Remover Funcionario (por CPF)\n");
        printf("3. Listar Funcionarios\n");
        printf("0. Voltar\n\n");
        printf("Escolha uma opcao: ");
        while (scanf("%d", &escolha) != 1) {
            printf("\nErro: Digite apenas numeros.\n");

            while (getchar() != '\n');

            printf("Escolha uma opcao: ");
        }

        switch (escolha) {
            case 1:
            printf("\n-------------------| CADASTRAR FUNCIONARIO |-------------------\n");
                printf("Digite o CPF (apenas numeros, max 11): ");
                scanf("%11s", cpfTemp); 
                
                printf("Digite o nome: ");
                scanf(" %49[^\n]", nomeTemp); 
                
                addFuncionarios(cpfTemp, nomeTemp);
                break;

            case 2:
                printf("\n-------------------| REMOVER FUNCIONARIO |-------------------\n");

                    printf("Digite o CPF do funcionario a ser removido: ");
                    scanf("%11s", cpfTemp);
                    removerPorCPF(cpfTemp);
                
                break;

            case 3:
                printf("\n-------------------| LISTAR FUNCIONARIOS |-------------------\n");
                listar_funcionarios();

                break;

            case 0:
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;

            default:
                printf("\nErro: escolha invalida! Escolha um numero de 0 a 3.\n");
                break;
        }

    } while (escolha != 0);

};

void gerenciamentoProdutos(){
    int escolha, subEscolha;
    
    do {
        printf("\n-------------------| GERENCIAMENTO DE PRODUTOS |-------------------\n");
        printf("1. Listar Produtos\n");
        printf("2. Cadastrar Produto\n");
        printf("3. Consultar Produto\n");
        printf("4. Adicionar Estoque\n");
        printf("5. Saida de Estoque\n");
        printf("6. Relatorio de inventario\n");
        printf("7. Produtos com estoque baixo\n");
        printf("8. Remover produto permanentemente\n");
        printf("0. Voltar\n\n");
        printf("Escolha uma opcao: ");
        while (scanf("%d", &escolha) != 1) {
            printf("\nErro: Digite apenas numeros.\n");

            while (getchar() != '\n');

            printf("Escolha uma opcao: ");
        }

        switch (escolha)
        {
        case 1:{
            do {
                printf("\n-------------------| LISTAGEM DE PRODUTOS |-------------------\n");
                printf("1. Listar todos os produtos\n");
                printf("2. Filtrar por faixa de preco\n");
                printf("3. Filtrar por faixa de codigo\n");
                printf("0. Voltar\n\n");
                printf("Escolha uma opcao: ");
                while (scanf("%d", &subEscolha) != 1) {
                    printf("\nErro: Digite apenas numeros.\n");

                    while (getchar() != '\n');

                    printf("Escolha uma opcao: ");
                }

                switch (subEscolha)
                {
                    int limInferior, limSuperior;
                    case 1:
                        listarTodosProdutos();
                        break;

                    case 2:
                        do {
                            printf("Digite o preco menor: ");
                            if (scanf("%d", &limInferior) != 1) {
                                printf("Erro: Digite apenas numeros.\n");

                                while (getchar() != '\n'); // limpa o buffer
                                limInferior = -1;          // força repetir o loop
                            }
                        } while (limInferior <=0);
                        
                        do {  
                            printf("Digite o preco maior: ");
                            if (scanf("%d", &limSuperior) != 1) {
                                printf("Erro: Digite apenas numeros.\n");

                                while (getchar() != '\n'); // limpa o buffer
                                limSuperior = -1;          // força repetir o loop
                            }
                        } while (limSuperior <=0 || limSuperior < limInferior);

                        listarProdutosDisponiveisPreco(limInferior, limSuperior);
                        limInferior = 0, limSuperior = 0, subEscolha = -1;
                        break;

                    case 3: 
                        do {
                            printf("Digite o codigo menor: ");
                            if (scanf("%d", &limInferior) != 1) {
                                printf("Erro: Digite apenas numeros.\n");

                                while (getchar() != '\n'); // limpa o buffer
                                limInferior = -1;          // força repetir o loop
                            }
                        } while (limInferior <=0);
                        
                        do {  
                            printf("Digite o codigo maior: ");
                            if (scanf("%d", &limSuperior) != 1) {
                                printf("Erro: Digite apenas numeros.\n");

                                while (getchar() != '\n'); 
                                limSuperior = -1;          
                            }
                        } while (limSuperior <=0 || limSuperior < limInferior);

                        listarProdutosDisponiveisCodigo(limInferior, limSuperior);
                        limInferior = 0;
                        limSuperior = 0;
                        break;
                        
                    default:
                        printf("\nErro: escolha invalida! Escolha um numero de 0 a 3.\n");
                        break;
                }
            } while (subEscolha != 0);
            }
            break;
        case 2: {
            int codTemp, qtdTemp;
            char nomeTemp[100];
            char descricaoTemp[100];
            float precoTemp;

            printf("\n-------------------| CADASTRAR PRODUTOS |-------------------\n");
            // cod
            while (1) {
                printf("Digite o codigo do produto: ");

                if (scanf("%d", &codTemp) == 1 && codTemp > 0) {
                    break; 
                }

                printf("Erro: Digite apenas numeros inteiros positivos.\n");

                while (getchar() != '\n'); 
            }
            
            // nome e descricao
            while (getchar() != '\n'); 

            printf("Digite o nome do produto: ");
            fgets(nomeTemp, sizeof(nomeTemp), stdin);
            nomeTemp[strcspn(nomeTemp, "\n")] = '\0';

            printf("Digite a descricao do produto: ");
            fgets(descricaoTemp, sizeof(descricaoTemp), stdin);
            descricaoTemp[strcspn(descricaoTemp, "\n")] = '\0';   

            // preco
            while (1) {
                printf("Digite o preco do produto (R$): ");

                if (scanf("%f", &precoTemp) == 1 && precoTemp >= 0) {
                    while (getchar() != '\n');
                    break;
                }

                printf("Erro: Digite um preco valido.\n");

                while (getchar() != '\n');
            }

            // quantidade
            while (1) {
                printf("Digite a quantidade do produto: ");

                if (scanf("%d", &qtdTemp) == 1 && qtdTemp >= 0) {
                    while (getchar() != '\n');
                    break;
                }

                printf("Erro: Digite uma quantidade valida.\n");

                while (getchar() != '\n');
            }

            cadastrarProdutoEstoque(codTemp, nomeTemp, descricaoTemp, precoTemp, qtdTemp);
        }
            break;
        
        case 3: {
            // consultar produto
            int codTemp;
            char buscaTemp[50];

            do {
                    printf("\n-------------------| CONSULTA DE PRODUTOS |-------------------\n");
                    printf("1. Pesquisar produtos\n");
                    printf("2. Consultar por codigo\n");
                    printf("0. Voltar\n\n");
                    printf("Escolha uma opcao: ");
                    while (scanf("%d", &subEscolha) != 1) {
                        printf("\nErro: Digite apenas numeros.\n");

                        while (getchar() != '\n');

                        printf("Escolha uma opcao: ");
                    }

                    while (getchar() != '\n');

                    switch (subEscolha)
                    {
                        case 1:
                            printf("Pesquisar por: ");
                            fgets(buscaTemp, sizeof(buscaTemp), stdin);
                            buscaTemp[strcspn(buscaTemp, "\n")] = '\0';

                            consultarProdutoNome(buscaTemp);
                            subEscolha = -1;
                            break;

                        case 2:
                            do {
                                printf("Digite o codigo: ");
                                if (scanf("%d", &codTemp) != 1) {
                                    printf("Erro: Digite apenas numeros.\n");

                                    while (getchar() != '\n'); // limpa o buffer
                                    codTemp = -1;          // força repetir o loop
                                }
                            } while (codTemp <=0);

                            consultarProdutoCodigo(codTemp);
                            codTemp = 0, subEscolha = -1;

                            break;

                        default:
                            printf("\nErro: escolha invalida! Escolha um numero de 0 a 2.\n");
                            break;
                    }
                } while (subEscolha != 0);
            }
            break;
        
        case 4: {
        // atualizar estoque
            printf("\n-------------------| ATUALIZACAO DE ESTOQUE |-------------------\n");
            int codTemp;

            printf("\nDigite o codigo do produto que pretende alterar a quantidade: ");
            while (scanf("%d", &codTemp) != 1) {
                printf("\nErro: Digite apenas numeros.\n");

                while (getchar() != '\n');

                printf("Digite o codigo do produto que pretende alterar a quantidade: ");
            }

            atualizarEstoqueProduto(codTemp);
            }
            break;

        case 5: {
        // saida de estoque
            printf("\n-------------------| SAIDA DE ESTOQUE |-------------------\n");

            int codTemp;
 
            printf("\nDigite o codigo do produto que deseja retirar: ");
            while (scanf("%d", &codTemp) != 1) {
                printf("\nErro: Digite apenas numeros.\n");

                while (getchar() != '\n');

                printf("Digite o codigo do produto que deseja retirar: ");
            }
            saidaEstoque(codTemp);
        }
            break;

        case 6:
        // relatorio de inventario
            break;

        case 7: 
        // produtos com estoque baixo
            break;

        case 8:
        // remover produto permanentemente
            break;

        default:
            printf("\nErro: escolha invalida! Escolha um numero de 0 a 8.\n");
            break;
        }
    } while (escolha != 0);
    
    // testes 
    // cadastrarProdutoEstoque(101, "Refrigerante Coca Cola", "1L", 8.0, 12);
    // cadastrarProdutoEstoque(101, "Refrigerante Coca Cola", "250ml", 3.5, 15);
    // cadastrarProdutoEstoque(103, "Energetico Monster Energy", "473ml", 8.99, 24);
    // cadastrarProdutoEstoque(105, "Energetico Red Bull", "473ml", 18.90, 5);
    // cadastrarProdutoEstoque(102, "Refrigerante Antarctica Guarana", "2L", 10.99, 6);
    // cadastrarProdutoEstoque(104, "Agua Mineral sem Gas", "200ml", 3.3, 10);

    // listarTodosProdutos();
    // listarProdutosDisponiveisPreco(7.0, 12);
    // listarProdutosDisponiveisCodigo(101, 105);
    // saidaEstoque(103, 10);

    // consultarProdutoCodigo(110);
    // consultarProdutoNome("Z");
};

int main() {
    int opcao;

    do {
        printf("\n-------------------| MENU SISTEMA |-------------------\n");
        printf("1. Gerenciar produtos\n");
        printf("2. Gerenciar funcionarios\n");
        printf("0. Sair\n\n");

        printf("Escolha uma opcao: ");
        while (scanf("%d", &opcao) != 1) {
            printf("\nErro: Digite apenas numeros.\n");

            while (getchar() != '\n');

            printf("Escolha uma opcao: ");
        }

        switch (opcao) {
        case 1:
            // gerenciar produtos (fazer a parte do usuario)
            gerenciamentoProdutos();
            break;
        case 2:
            // gerenciar usuarios
            gerenciamentoFuncionarios();
            break;
        case 0:
            printf("\nSistema sendo encerrado. Ate breve!\n");
            break;
        default:
            printf("\nErro: escolha invalida! Escolha um numero de 0 a 2.\n");
            break;
        }
    } while (opcao != 0);
    
    return 0;
}
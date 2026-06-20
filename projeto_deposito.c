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

// --- PROTOTIPOS DE ARQUIVO ---
void salvarArquivo();
void carregarArquivo();

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

// CRUD
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
            salvarArquivo(); // [ IMPLEMENTACAO AQUI ]
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
                salvarArquivo(); // [ IMPLEMENTACAO AQUI ]

            } else {
                printf("Ja existe um produto com esse codigo! Se quer alterar o estoque procure a opcao de alteracao.\n");
            };
        }
    } else {
        printf("Impossivel adicionar. Confira se o preco, quantidade ou codigo sao maiores que 0!\n");
    }
}

void saidaEstoque(int codTemp){
    int qtdTemp;

    printf("\n-------------------| RETIRAR DO ESTOQUE |-------------------\n");
    Produto *aux = buscarProduto(codTemp);
    if (aux == NULL){
        printf("Produto %d inexistente no estoque.\n", codTemp);
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

            printf("Estoque do produto de codigo %d atualizado com sucesso!", codTemp);
            salvarArquivo(); // [ IMPLEMENTACAO AQUI ]

            printf("\n | PRODUTO | \n");
            printf("Codigo: %d \n", aux->codProduto);
            printf("Nome: %s \n", aux->nomeProduto);
            printf("Descricao: %s \n", aux->descricaoProduto);
            printf("Preco: R$ %.2lf \n", aux->precoProduto);
            printf("Quantidade: %d \n", aux->qntProduto);

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
        salvarArquivo(); // [ IMPLEMENTACAO AQUI ]

        printf("Estoque atualizado com sucesso!\n");

        printf("\n | PRODUTO | \n");
        printf("Codigo: %d \n", aux->codProduto);
        printf("Nome: %s \n", aux->nomeProduto);
        printf("Descricao: %s \n", aux->descricaoProduto);
        printf("Preco: R$ %.2lf \n", aux->precoProduto);
        printf("Quantidade: %d \n", aux->qntProduto);
    }
}

void removerProdutoPermanentemente(int codTemp){
    printf("\n-------------------| REMOVER PRODUTO |-------------------\n");

    Produto *aux = buscarProduto(codTemp);

    if (aux == NULL) {
        printf("Produto inexistente.\n");
    } else{
        if (aux->qntProduto > 0) {
            printf("Ainda existem %d unidades em estoque.\n", aux->qntProduto);
            printf("Zere o estoque antes de remover.\n");

        } else {
            printf("Produto encontrado: %s (codigo %d)\n", aux->nomeProduto, aux->codProduto);

            int confirmacao;
            printf("Tem certeza que deseja apagar este registro? (1 para Sim / 0 para Nao): ");
            scanf("%d", &confirmacao);

            if (confirmacao != 1) {
                printf("Acao cancelada. O produto %s nao foi apagado(a).\n", aux->nomeProduto);

            } else {
                if (inicioProduto == aux){
                    inicioProduto = aux->prox;

                    if(qtdProdutosEstoque == 1){
                        fimProduto = NULL;
                    } else {
                        inicioProduto->ant = NULL;
                    }
                } else if (aux == fimProduto) {
                    //fim
                    fimProduto = aux->ant;
                    fimProduto->prox = NULL;
                } else {
                    // meio
                    aux->ant->prox = aux->prox;
                    aux->prox->ant = aux->ant;
                }

                free(aux);
                qtdProdutosEstoque--;
                salvarArquivo();
                printf("Produto de codigo %d removido com sucesso!\n", codTemp);
            }
        }
    }
};

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

void relatorioInventario(){
    printf("\n-------------------| RELATORIO DE INVENTARIO |-------------------\n");

    Produto * aux = inicioProduto;
    int totalItens = 0;
    int totalQuantidade = 0;
    float valorTotal = 0;

    while(aux != NULL){
        printf("Codigo: %d \n", aux->codProduto);
        printf("Nome: %s \n", aux->nomeProduto);
        printf("Quantidade: %d \n", aux->qntProduto);
        printf("Preco: R$ %.2lf \n", aux->precoProduto);
        printf("Valor em estoque: R$ %.2lf \n", aux->precoProduto * aux->qntProduto);
        printf("\n");

        totalItens += 1;
        totalQuantidade += aux->qntProduto;
        valorTotal += aux->precoProduto * aux->qntProduto;

        aux = aux->prox;
    }

    if (totalItens == 0) {
        printf("Nao ha produtos cadastrados.\n");
    } else {
        printf("-------------------------------------------------\n");
        printf("Total de produtos cadastrados: %d \n", totalItens);
        printf("Total de itens em estoque: %d \n", totalQuantidade);
        printf("Valor total do estoque: R$ %.2lf \n", valorTotal);
    }
}

void produtosEstoqueBaixo(){
    printf("\n-------------------| PRODUTOS COM ESTOQUE BAIXO |-------------------\n");
    printf("Estoque minimo: %d\n\n", estoqueMinimo);

    Produto * aux = inicioProduto;
    int contador = 0;

    while(aux != NULL){
        if (aux->qntProduto <= estoqueMinimo) {
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
        printf("Nao ha produtos com estoque baixo.\n");
    }
}

// RF003
void consultarProdutoCodigo(int codTemp){
    printf("\n-------------------| CONSULTA DE PRODUTO |-------------------\n");
    printf("Consulta por codigo: %d\n\n", codTemp);

    Produto * aux = buscarProduto(codTemp);
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
    int encontrouAlgum = 0;

    char buscaMin[100];
    strcpy(buscaMin, nome);

    for(int i = 0; buscaMin[i] != '\0'; i++){
        buscaMin[i] = tolower((unsigned char)buscaMin[i]);
    }

    while(aux != NULL){

        char nomeProdutoMin[100];
        strcpy(nomeProdutoMin, aux->nomeProduto);

        for(int i = 0; nomeProdutoMin[i] != '\0'; i++){
            nomeProdutoMin[i] = tolower((unsigned char)nomeProdutoMin[i]);
        }

        int encontrouProduto = 0;

        char copiaNome[100];
        strcpy(copiaNome, nomeProdutoMin);

        char *palavra = strtok(copiaNome, " ");

        while(palavra != NULL){

            if(strncmp(palavra, buscaMin, strlen(buscaMin)) == 0){
                encontrouProduto = 1;
                break;
            }

            palavra = strtok(NULL, " ");
        }

        if(encontrouProduto){
            printf("Codigo: %d\n", aux->codProduto);
            printf("Nome: %s\n", aux->nomeProduto);
            printf("Preco: R$ %.2f\n", aux->precoProduto);
            printf("Quantidade: %d\n\n", aux->qntProduto);

            encontrouAlgum = 1;
        }

        aux = aux->prox;
    }

    if(!encontrouAlgum){
        printf("Nenhum produto encontrado com '%s'.\n", nome);
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

void removerFuncionario(char *cpfBusca) {

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

                free(aux);
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

// --- FUNCOES DE ARQUIVO IMPLEMENTADAS AQUI ---

// RF006 - Leitura do Arquivo
void carregarArquivo() {
    FILE *arquivo = fopen("inventario.txt", "r");

    if (arquivo == NULL) {
        printf("\n[AVISO] Arquivo 'inventario.txt' nao encontrado. O sistema iniciara com o estoque vazio.\n");
        return; 
    }

    int cod, quantidade;
    char nome[100], descricao[100];
    float preco;

    while (fscanf(arquivo, "%d;%99[^;];%99[^;];%f;%d\n", &cod, nome, descricao, &preco, &quantidade) == 5) {
        
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
        }else{ 
            if (novo->codProduto < inicioProduto->codProduto) { 
                inicioProduto->ant = novo; 
                novo->prox = inicioProduto;
                inicioProduto = novo;
            } else if(novo->codProduto >= fimProduto->codProduto){ 
                fimProduto->prox = novo;
                novo->ant = fimProduto;
                fimProduto = novo;
            }else{ 
                Produto* aux = inicioProduto->prox;
                while(aux != NULL && novo->codProduto >= aux->codProduto){
                    aux = aux->prox;
                }
                aux->ant->prox = novo;
                novo->prox = aux;
                novo->ant = aux->ant;
                aux->ant = novo;
            }
        }
        qtdProdutosEstoque++;
    }

    fclose(arquivo);
    printf("\n>>> Inventario carregado com sucesso! <<<\n");
}

// RF007 - Escrita do Arquivo
void salvarArquivo() {
    FILE *arquivo = fopen("inventario.txt", "w");

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo inventario.txt para salvar!\n");
        return;
    }

    Produto *aux = inicioProduto;

    while (aux != NULL) {
        fprintf(arquivo, "%d;%s;%s;%.2f;%d\n", 
                aux->codProduto, 
                aux->nomeProduto, 
                aux->descricaoProduto, 
                aux->precoProduto, 
                aux->qntProduto);
        
        aux = aux->prox;
    }

    fclose(arquivo);
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
                    removerFuncionario(cpfTemp);
                
                break;

            case 3:
                printf("\n-------------------| LISTAR FUNCIONARIOS |-------------------\n");
                listar_funcionarios();

                break;

            case 0:
                printf("\nVoltando ao menu anterior...\n");
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
                printf("4. Retirar produto do estoque\n");
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

                                while (getchar() != '\n'); 
                                limInferior = -1;          
                            }
                        } while (limInferior <=0);
                        
                        do {  
                            printf("Digite o preco maior: ");
                            if (scanf("%d", &limSuperior) != 1) {
                                printf("Erro: Digite apenas numeros.\n");

                                while (getchar() != '\n'); 
                                limSuperior = -1;          
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
                        
                    case 4:{
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

                    default:
                        printf("\nErro: escolha invalida! Escolha um numero de 0 a 4.\n");
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
                    printf("3. Retirar produto do estoque\n");
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
                        case 3:{
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

                        default:
                            printf("\nErro: escolha invalida! Escolha um numero de 0 a 3.\n");
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
            relatorioInventario();
            break;

        case 7:
        // produtos com estoque baixo
            produtosEstoqueBaixo();
            break;

        case 8:{
        // remover produto permanentemente
            int codTemp;
                
            printf("Digite o codigo do produto que deseja remover permanentemente: ");
            while (scanf("%d", &codTemp) != 1) {
                printf("\nErro: Digite apenas numeros.\n");

                while (getchar() != '\n');

                printf("Digite o codigo do produto que deseja remover permanentemente: ");
            }
            removerProdutoPermanentemente(codTemp);
        }
            break;

        default:
            printf("\nErro: escolha invalida! Escolha um numero de 0 a 8.\n");
            break;
        }
    } while (escolha != 0);
    
};

int main() {
    int opcao;

    carregarArquivo(); 

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
            // gerenciar produtos 
            gerenciamentoProdutos();
            break;
        case 2:
            // gerenciar usuarios
            gerenciamentoFuncionarios();
            break;
        case 0:
            salvarArquivo(); 
            printf("\nSistema sendo encerrado. Ate breve!\n");
            break;
        default:
            printf("\nErro: escolha invalida! Escolha um numero de 0 a 2.\n");
            break;
        }
    } while (opcao != 0);
    
    return 0;
}
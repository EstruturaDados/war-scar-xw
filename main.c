// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================

// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

#define MAX_STRING 50
#define MAX_TERRIRORIO 5
#define TRUE 1
#define FALSE 0
#define MAX_MISSAO 10
#define MAX_TROPA 20


// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

typedef struct {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int numeroTropas;
} territorio;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa.

territorio* alocarMapa();
void liberarMemoria(territorio *mapa);
void inicializarTerritorios(int *quantiaDeTerritorios,territorio *mapa);
void exibirMapa(territorio *mapa,int quantiaDeTerritorios);
void limparBuffer();



// --- Função Principal (main) ---
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    int quantiaDeTerritorios = 0;
    territorio *mapa = alocarMapa();
    inicializarTerritorios(&quantiaDeTerritorios,mapa);
    exibirMapa(mapa,quantiaDeTerritorios);



    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
    liberarMemoria(mapa);

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
territorio* alocarMapa() {
    territorio *mapa = (territorio *) calloc(MAX_TERRIRORIO,sizeof(territorio));

    if (mapa == NULL) {
        printf("Erro no memoria\n");
        exit(1);
    }
    return mapa;
}

// liberarMemoria():
//Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(territorio *mapa) {
    free(mapa);
}

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).  

void inicializarTerritorios(int *quantiaDeTerritorios,territorio *mapa) {
    printf("----------- WAR -------------\n");
    printf("Preencha os dados iniciais de cada territorio: \n");
    printf("-----------------------------\n\n");

    for (int i = 0; i < MAX_TERRIRORIO; i++) {
        printf("TERRITORIO %d:", i + 1);

        printf("\nNome:"); // O \n aqui garante que comece em linha nova após o título
        fgets(mapa[i].nome, MAX_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("cor:");
        fgets(mapa[i].cor, MAX_STRING, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Numero de tropas:");
        scanf("%d", &mapa[i].numeroTropas);
        limparBuffer();

        (*quantiaDeTerritorios)++;
    }
}
// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void exibirMapa(territorio *mapa,int quantiaDeTerritorios) {
    printf("\n-------------- MAPA DOS TERRITORIOS -----------");
    for (int i = 0; i < quantiaDeTerritorios; i++) {
        printf("\n-------- TERRITORIO %d --------", i + 1);
        printf("\nNome: %s", mapa[i].nome);
        printf("\nCor: %s", mapa[i].cor);
        printf("\nQuantidade de tropas: %d", mapa[i].numeroTropas);
    }
}



// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
void limparBuffer() {
        int c;
        while (( c = getchar()) != '\n' && c != EOF);
    }

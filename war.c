// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

#include <stdio.h>
#include <string.h>

// Estrutura (struct) que guarda as informações de um território
struct Territorio {
    char nome[30];   // nome do território
    char cor[10];    // cor do exército
    int tropas;      // quantidade de tropas
};

int main() {

    // Cria um vetor com 5 territórios
    struct Territorio territorios[5];

    int i; // variável para o laço

    printf("===== CADASTRO DE TERRITORIOS =====\n\n");

    // Cadastro dos 5 territórios
    for (i = 0; i < 5; i++) {
        printf("Digite o nome do territorio %d: ", i + 1);
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do exercito do territorio %d: ", i + 1);
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas do territorio %d: ", i + 1);
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // pular linha entre cadastros
    }

    // Exibição dos territórios cadastrados
    printf("===== LISTA DE TERRITORIOS CADASTRADOS =====\n\n");

    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exercito: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("------------------------------\n");
    }

    return 0;
}

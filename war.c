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
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};


void cadastrarTerritorios(struct Territorio *mapa, int qtd) {
    int i;
    for (i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


void exibirTerritorios(struct Territorio *mapa, int qtd) {
    int i;
    printf("\n===== TERRITORIOS ATUAIS =====\n");
    for (i = 0; i < qtd; i++) {
        printf("%d - Nome: %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}


void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- ATAQUE EM ANDAMENTO ---\n");
    printf("%s (cor %s) rolou: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("%s (cor %s) rolou: %d\n", defensor->nome, defensor->cor, dadoDefensor);

    
    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu a batalha!\n");

        
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; 
        atacante->tropas = atacante->tropas / 2; 

    } else {
        printf("O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1; 
    }
}


void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}

int main() {
    srand(time(NULL)); 

    int qtd;
    printf("Digite quantos territorios voce quer cadastrar: ");
    scanf("%d", &qtd);

    struct Territorio *mapa = (struct Territorio*) malloc(qtd * sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    exibirTerritorios(mapa, qtd);

    int a, d;
    printf("\nEscolha o numero do territorio atacante: ");
    scanf("%d", &a);

    printf("Escolha o numero do territorio defensor: ");
    scanf("%d", &d);

    if (a == d) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
    } else if (strcmp(mapa[a - 1].cor, mapa[d - 1].cor) == 0) {
        printf("Voce nao pode atacar um territorio da mesma cor!\n");
    } else {
        atacar(&mapa[a - 1], &mapa[d - 1]);
    }

    exibirTerritorios(mapa, qtd);

    liberarMemoria(mapa);

    return 0;
}

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
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


void exibirMapa(struct Territorio *mapa, int qtd) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}


void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- BATALHA ---\n");
    printf("%s (%s) rolou: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("%s (%s) rolou: %d\n", defensor->nome, defensor->cor, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu e conquistou o territorio!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas / 2;
    } else {
        printf("O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }
}


void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}


void exibirMissao(char *missao) {
    printf("\nSua missão é: %s\n", missao);
}


int verificarMissao(char *missao, struct Territorio *mapa, int tamanho) {
    
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0) contador++;
        }
        if (contador >= 3) return 1; 
    }

    if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        int achouVermelho = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0) achouVermelho = 1;
        }
        if (!achouVermelho) return 1;
    }

    
    return 0; 
}


void liberarMemoria(struct Territorio *mapa, char *missao1, char *missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
    printf("\nMemoria liberada com sucesso!\n");
}

int main() {
    srand(time(NULL));

    int qtd;
    printf("Digite o numero de territorios do jogo: ");
    scanf("%d", &qtd);

    
    struct Territorio *mapa = (struct Territorio *) malloc(qtd * sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    
    cadastrarTerritorios(mapa, qtd);
    exibirMapa(mapa, qtd);

    
    char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Ter mais de 15 tropas no total",
        "Conquistar 2 territorios da cor azul",
        "Dominar todos os territorios verdes"
    };
    int totalMissoes = 5;

    
    char *missaoJogador1 = (char *) malloc(100 * sizeof(char));
    char *missaoJogador2 = (char *) malloc(100 * sizeof(char));

    
    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\n--- JOGADOR 1 ---");
    exibirMissao(missaoJogador1);
    printf("\n--- JOGADOR 2 ---");
    exibirMissao(missaoJogador2);

    
    int turno = 1;
    while (1) {
        printf("\n===== TURNO %d =====\n", turno);
        exibirMapa(mapa, qtd);

        int atacante, defensor;
        printf("Escolha territorio atacante: ");
        scanf("%d", &atacante);
        printf("Escolha territorio defensor: ");
        scanf("%d", &defensor);

        if (atacante == defensor) {
            printf("Um territorio nao pode atacar a si mesmo!\n");
        } else if (strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0) {
            printf("Voce nao pode atacar um territorio da mesma cor!\n");
        } else {
            atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
        }

        
        if (verificarMissao(missaoJogador1, mapa, qtd)) {
            printf("\n🎉 Jogador 1 venceu! Missao cumprida: %s\n", missaoJogador1);
            break;
        }
        if (verificarMissao(missaoJogador2, mapa, qtd)) {
            printf("\n🎉 Jogador 2 venceu! Missao cumprida: %s\n", missaoJogador2);
            break;
        }

        turno++;
        if (turno > 20) { 
            printf("\nJogo encerrado por limite de turnos.\n");
            break;
        }
    }

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);

    return 0;
}


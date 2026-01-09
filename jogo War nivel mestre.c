#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---------- STRUCT ---------- */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ---------- FUNÇÕES ---------- */

// Sorteia e copia missão para o jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibe a missão apenas uma vez
void exibirMissao(char* missao, int jogador) {
    printf("\nMissão do Jogador %d: %s\n", jogador, missao);
}

// Ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque inválido! Territórios da mesma cor.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque: %s (%d) x %s (%d)\n",
           atacante->nome, dadoAtacante,
           defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    } else {
        printf("Defensor venceu!\n");
        atacante->tropas--;
        if (atacante->tropas < 1)
            atacante->tropas = 1;
    }
}

// Verificação simples de missão
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    int contador = 0;

    if (strstr(missao, "Conquistar 3 territórios")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                contador++;
        }
        return contador >= 3;
    }

    if (strstr(missao, "Eliminar todas as tropas vermelhas")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0)
                return 0;
        }
        return 1;
    }

    return 0;
}

// Exibe mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n----- MAPA -----\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s | Cor: %s | Tropas: %d\n",
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Libera memória
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
}

/* ---------- MAIN ---------- */
int main() {
    srand(time(NULL));

    // Missões estratégicas
    char* missoes[] = {
        "Conquistar 3 territórios",
        "Eliminar todas as tropas vermelhas",
        "Dominar territórios consecutivos",
        "Eliminar um jogador inimigo",
        "Conquistar a maioria do mapa"
    };

    int totalMissoes = 5;

    // Alocação das missões dos jogadores
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    exibirMissao(missaoJogador1, 1);
    exibirMissao(missaoJogador2, 2);

    // Alocação do mapa
    int totalTerritorios = 5;
    Territorio* mapa = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));

    // Inicialização do mapa
    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "Azul");
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Argentina");
    strcpy(mapa[1].cor, "Vermelho");
    mapa[1].tropas = 4;

    strcpy(mapa[2].nome, "Chile");
    strcpy(mapa[2].cor, "Vermelho");
    mapa[2].tropas = 3;

    strcpy(mapa[3].nome, "Peru");
    strcpy(mapa[3].cor, "Azul");
    mapa[3].tropas = 4;

    strcpy(mapa[4].nome, "Colômbia");
    strcpy(mapa[4].cor, "Neutro");
    mapa[4].tropas = 2;

    // Simulação de turno
    exibirMapa(mapa, totalTerritorios);
    atacar(&mapa[0], &mapa[1]);
    exibirMapa(mapa, totalTerritorios);

    // Verificação de vitória
    if (verificarMissao(missaoJogador1, mapa, totalTerritorios)) {
        printf("\n🏆 Jogador 1 venceu ao cumprir sua missão!\n");
    } else if (verificarMissao(missaoJogador2, mapa, totalTerritorios)) {
        printf("\n🏆 Jogador 2 venceu ao cumprir sua missão!\n");
    } else {
        printf("\nNenhuma missão concluída ainda.\n");
    }

    // Liberação de memória
    liberarMemoria(mapa, missaoJogador1, missaoJogador2);

    return 0;
}

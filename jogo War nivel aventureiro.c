#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* Função para cadastrar territórios */
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/* Função para exibir territórios */
void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/* Função de ataque */
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Não é permitido atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n❌ O atacante não possui tropas suficientes para atacar!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Dado do atacante: %d", dadoAtacante);
    printf("\n🎲 Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n✅ O atacante venceu a batalha!\n");

        int tropasTransferidas = atacante->tropas / 2;
        atacante->tropas -= tropasTransferidas;

        defensor->tropas = tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);
    } else {
        printf("\n❌ O defensor venceu a batalha!\n");
        atacante->tropas -= 1;
    }
}

/* Função para liberar memória */
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    int qtd;
    int atacante, defensor;

    srand(time(NULL));

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    Territorio *mapa = (Territorio *)calloc(qtd, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        exibirTerritorios(mapa, qtd);

        printf("\nEscolha o índice do território atacante: ");
        scanf("%d", &atacante);

        printf("Escolha o índice do território defensor: ");
        scanf("%d", &defensor);

        if (atacante < 0 || atacante >= qtd || defensor < 0 || defensor >= qtd) {
            printf("\n❌ Índices inválidos!\n");
        } else {
            atacar(&mapa[atacante], &mapa[defensor]);
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    }

    liberarMemoria(mapa);
    printf("\n🧹 Memória liberada. Fim do jogo!\n");

    return 0;
}

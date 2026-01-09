#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estrutura do território */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* Protótipos das funções */
void cadastrarTerritorios(Territorio *mapa, int qtd);
void exibirTerritorios(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa);

int main() {
    int qtd, atacante, defensor;

    srand(time(NULL)); // Garante aleatoriedade

    printf("Informe a quantidade de territorios: ");
    scanf("%d", &qtd);

    /* Alocação dinâmica */
    Territorio *mapa = (Territorio *)calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        exibirTerritorios(mapa, qtd);

        printf("\nEscolha o territorio ATACANTE (indice): ");
        scanf("%d", &atacante);

        printf("Escolha o territorio DEFENSOR (indice): ");
        scanf("%d", &defensor);

        /* Validações */
        if (atacante < 0 || atacante >= qtd || defensor < 0 || defensor >= qtd) {
            printf("Indice invalido!\n");
        } else if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
            printf("Nao e permitido atacar um territorio da mesma cor!\n");
        } else {
            atacar(&mapa[atacante], &mapa[defensor]);
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    }

    liberarMemoria(mapa);
    return 0;
}

/* Cadastro dos territórios */
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d\n", i);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/* Exibição dos territórios */
void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/* Função de ataque */
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque em andamento...\n");
    printf("Dado Atacante: %d\n", dadoAtacante);
    printf("Dado Defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");

        /* Transfere o controle */
        strcpy(defensor->cor, atacante->cor);

        /* Transfere metade das tropas */
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    } else {
        printf("Defensor resistiu!\n");

        /* Atacante perde uma tropa */
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

/* Liberação de memória */
void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}

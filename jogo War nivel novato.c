#include <stdio.h>
#include <string.h>

/*
    Definição da struct Territorio
    Agrupa informações relacionadas a um território
*/
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
};

int main() {

    // Declaração de um vetor de 5 territórios
    struct Territorio territorios[5];

    printf("=== Cadastro de Territorios ===\n\n");

    // Laço para entrada de dados
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove '\n'

        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Limpa o buffer do teclado

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n=== Territorios Cadastrados ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}

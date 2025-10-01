#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORY 5

struct territory
{
    char name[30];
    char color[10];
    int troops;
};

void clearEntryBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    struct territory territory[MAX_TERRITORY];

    printf("================================\n");
    printf("    WAR\n");
    printf("================================\n");
    printf("Cadastre os %d territorios inicias\n", MAX_TERRITORY);

    for (int index = 0; index < MAX_TERRITORY; index++) {
        printf("\n<<< Cadastrando Territorio %d >>>\n", index + 1);
        printf("Nome: ");
        fgets(territory[index].name, 30, stdin);
        printf("Cor: ");
        fgets(territory[index].color, 10, stdin);
        printf("Quantidade de tropas: ");
        scanf("%d", &territory[index].troops);

        territory[index].name[strcspn(territory[index].name, "\n")] = '\0';
        territory[index].color[strcspn(territory[index].color, "\n")] = '\0';
        clearEntryBuffer();
    }

    printf("\nCadastros finalizado!\n");

    printf("\n================================\n");
    printf("    Estado atual do mundo\n");
    printf("================================\n");

    for (int index = 0; index < MAX_TERRITORY; index++) {
        printf("\nTerritorio %d\n", index + 1);
        printf("    - Nome: %s\n", territory[index].name);
        printf("    - Cor da Tropa: %s\n", territory[index].color);
        printf("    - Qtde. Tropas: %d\n", territory[index].troops);
    }

    return 0;
}

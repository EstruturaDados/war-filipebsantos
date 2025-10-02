#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct Territory
{
    char name[30];
    char armyColor[10];
    int troops;
};

void clearEntryBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void unloadHeapMemory(struct Territory *vector)
{
    free(vector);
    return;
}

void showCurrentWorld(struct Territory *territoryVector, int maxTerritory)
{
    printf("\n================================\n");
    printf("    WAR - Status Atual\n");
    printf("================================\n");

    for (int index = 0; index < maxTerritory; index++)
    {
        printf("\n%d. %s (Exercito %s - Tropas %d)", index + 1, territoryVector[index].name, territoryVector[index].armyColor, territoryVector[index].troops);
    }
    printf("\n================================\n");

    return;
}

void createTerritories(struct Territory *territoryVector, int maxTerritory)
{
    for (int index = 0; index < maxTerritory; index++)
    {
        printf("\n<<< Cadastrando Territorio %d >>>\n", index + 1);
        printf("Nome: ");
        fgets(territoryVector[index].name, 30, stdin);
        printf("Cor do Exercito: ");
        fgets(territoryVector[index].armyColor, 10, stdin);
        printf("Quantidade de tropas: ");
        scanf("%d", &territoryVector[index].troops);

        territoryVector[index].name[strcspn(territoryVector[index].name, "\n")] = '\0';
        territoryVector[index].armyColor[strcspn(territoryVector[index].armyColor, "\n")] = '\0';
        clearEntryBuffer();
    }

    printf("\nTerritorios cadastrados!\n");

    return;
}

int rollDice()
{
    return (rand() % 6) + 1;
}

void battle(struct Territory *territoryVector, int maxTerritory, int attackerIndex, int defenserIndex)
{
    // Check if indexes are in range
    if (attackerIndex <= 0 || attackerIndex > maxTerritory) {
        printf("\nAtacante invalido!\n");
        return;
    }

    if (defenserIndex <= 0 || defenserIndex > maxTerritory) {
        printf("\nDefensor invalido!\n");
        return;
    }

    // Check if attacker isn't attacker him self
    if (attackerIndex == defenserIndex) {
        printf("\nO atacante nao pode atacar a si proprio!\n");
        return;        
    }

    attackerIndex--;
    defenserIndex--;

    // Check if defense territory is already owned by attacker
    if (strcmp(territoryVector[defenserIndex].armyColor, territoryVector[attackerIndex].armyColor) == 0) {
        printf("\nO territorio %s ja percente ao Exercito %s!\n", territoryVector[defenserIndex].name, territoryVector[attackerIndex].armyColor);
        return;          
    }

    // Roll dices
    int attackerDice = rollDice();
    int defenserDice = rollDice();

    printf("\n%s rolou o dado e tirou %d.\n", territoryVector[attackerIndex].name, attackerDice);
    printf("%s rolou o dado e tirou %d.\n", territoryVector[defenserIndex].name, defenserDice);

    if (attackerDice == defenserDice) {
        printf("Empatou! Ambos pederam uma tropa!\n");
        territoryVector[attackerIndex].troops--;
        territoryVector[defenserIndex].troops--;
        return;
    }

    if (attackerDice > defenserDice) {
        // Attacker Wins
        printf("\nVitoria para %s! %s perdeu uma tropa.", territoryVector[attackerIndex].name, territoryVector[defenserIndex].name);
        
        if (territoryVector[defenserIndex].troops - 1 > 0) {
            territoryVector[defenserIndex].troops--;
        } else {
            printf("\nTERRITORIO CONQUISTADO! %s agora percente ao Exercito %s!\n", territoryVector[defenserIndex].name, territoryVector[attackerIndex].armyColor);
            strcpy(territoryVector[defenserIndex].armyColor, territoryVector[attackerIndex].armyColor);

            /* Move half troops to new territory. But if winners has only 1 troop? */
            if (territoryVector[attackerIndex].troops > 1) {
                territoryVector[defenserIndex].troops = round(territoryVector[attackerIndex].troops / 2);
                territoryVector[attackerIndex].troops = territoryVector[attackerIndex].troops - round(territoryVector[attackerIndex].troops / 2);
            }
        }
    } else {
        // Attacker Loses
        printf("\nVitoria para %s! %s perdeu uma tropa.\n", territoryVector[defenserIndex].name, territoryVector[attackerIndex].name);

        if (territoryVector[attackerIndex].troops - 1 > 0) {
            territoryVector[attackerIndex].troops--;
        } else {
            sprintf("\nTERRITORIO PERDIDO! %s agora percente ao Exercito %s!\n", territoryVector[defenserIndex].name, territoryVector[attackerIndex].armyColor);
            strcpy(territoryVector[attackerIndex].armyColor, territoryVector[defenserIndex].armyColor);

            /* Move half troops to new territory. But if winners has only 1 troop? */
            if (territoryVector[defenserIndex].troops > 1) {
                territoryVector[attackerIndex].troops = round(territoryVector[defenserIndex].troops / 2);
                territoryVector[defenserIndex].troops = territoryVector[defenserIndex].troops - round(territoryVector[defenserIndex].troops / 2);
            }
        }        
    }

    return;
}

int main()
{
    // Initialize random seed
    srand(time(NULL));

    int maxTerritory;
    struct Territory *territory;

    printf("================================\n");
    printf("                WAR\n");
    printf("================================\n");
    printf("Informe a quantidade de territorios: \n");
    scanf("%d", &maxTerritory);
    clearEntryBuffer();

    territory = (struct Territory *)malloc(maxTerritory * sizeof(struct Territory));
    if (territory == NULL) return 1; // End with error if can't allocate heap memory

    createTerritories(territory, maxTerritory);
    showCurrentWorld(territory, maxTerritory);

    // Battle loop
    int attacker;
    int defenser;

    do
    {
        printf("\n<<< FASE DE ATAQUE  >>>\n");
        printf("Selecione o atacante (0 para sair): ");
        scanf("%d", &attacker);

        if (attacker == 0) break;

        printf("Selecione quem vai atacar: ");
        scanf("%d", &defenser);

        clearEntryBuffer();
        battle(territory, maxTerritory, attacker, defenser);

        printf("\nPress Enter to continue...\n");
        getchar();

        showCurrentWorld(territory, maxTerritory);
    } while (1);
    
    unloadHeapMemory(territory);
    return 0;
}

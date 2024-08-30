#include <stdio.h>
#include <stdlib.h>

#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

// Struct para armazenar o placar
typedef struct {
    int vitoriasX;
    int vitoriasO;
    int empate;
} Placar;

void inicializar_tabuleiro(char tab[3][3]) {
    char inicio[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tab[i][j] = inicio[i][j];
        }
    }
}

void mostrar_tab(char tab[3][3]) {
    printf("%c | %c | %c\n", tab[0][0], tab[0][1], tab[0][2]);
    printf("---------\n");
    printf("%c | %c | %c\n", tab[1][0], tab[1][1], tab[1][2]);
    printf("---------\n");
    printf("%c | %c | %c\n", tab[2][0], tab[2][1], tab[2][2]);
}

char verificar_vencedor(char tab[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2]) {
            return tab[i][0];
        }
        if (tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i]) {
            return tab[0][i];
        }
    }
    if (tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2]) {
        return tab[0][0];
    }
    if (tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0]) {
        return tab[0][2];
    }
    return 0;
}

void exibir_placar(Placar *placar) {
    printf(CYAN);
    printf("----------------------------\n");
    printf("----   PLACAR DO JOGO   ----\n");
    printf("----------------------------\n");
    printf("  Vitorias X: %d       \n", placar->vitoriasX);
    printf("  Vitorias O: %d       \n", placar->vitoriasO);
    printf("----------------------------\n");
    printf(RESET);
}

int menu() {
    int escolha;
    printf("---------------------------\n");
    printf("------ JOGO DA VELHA ------\n");
    printf("---------------------------\n");
    printf("\n------ MENU DE OPCOES -----\n\n");
    printf("1 - INICIAR JOGO\n");
    printf("0 - SAIR\n>> ");
    scanf("%d", &escolha);
    while (escolha != 1 && escolha != 0) {
        printf("Opção invalida, digite novamente: ");
        scanf("%d", &escolha);
    }
    return escolha;
}

void jogar_partida(char tab[3][3], Placar *placar) {
    int lin, col, posicao;

    for (int cont = 0; cont < 9; cont++) {
        system("cls");
        exibir_placar(placar);
        mostrar_tab(tab);

        char marcador = (cont % 2 == 0) ? 'X' : 'O';

        printf("\n\nJogador %c, escolha uma posicao [1-9]: ", marcador);
        scanf("%d", &posicao);

        switch (posicao) {
            case 1: lin = 0; col = 0; break;
            case 2: lin = 0; col = 1; break;
            case 3: lin = 0; col = 2; break;
            case 4: lin = 1; col = 0; break;
            case 5: lin = 1; col = 1; break;
            case 6: lin = 1; col = 2; break;
            case 7: lin = 2; col = 0; break;
            case 8: lin = 2; col = 1; break;
            case 9: lin = 2; col = 2; break;
            default: printf(RED"Posição inválida!"RESET); cont--; continue;
        }

        if (tab[lin][col] == 'X' || tab[lin][col] == 'O') {
            printf(RED"Posição já ocupada! Tente novamente.\n"RESET);
            cont--;
            system("pause");
            continue;
        }

        tab[lin][col] = marcador;

        char vencedor = verificar_vencedor(tab);
        if (vencedor) {
            system("cls");
            mostrar_tab(tab);
            printf(GREEN"\nJogador %c venceu!\n"RESET, vencedor);
            if (vencedor == 'X') placar->vitoriasX++;
            else placar->vitoriasO++;
            break;
        } else if (cont == 8) {
            system("cls");
            mostrar_tab(tab);
            printf("\nEmpate!\n");
            placar->empate++;
            break;
        }
    }
}

void rodada_desempate(char tab[3][3], Placar *placar) {
    printf(GREEN"\nIniciando rodada de desempate!\n"RESET);
    inicializar_tabuleiro(tab);

    for (int cont = 0; cont < 9; cont++) {
        system("cls");
        printf("---- RODADA DE DESEMPATE ----\n\n");
        mostrar_tab(tab);

        char marcador = (cont % 2 == 0) ? 'X' : 'O';
        int posicao;
        printf("\n\nJogador %c, escolha uma posicao [1-9]: ", marcador);
        scanf("%d", &posicao);

        int lin, col;
        switch (posicao) {
            case 1: lin = 0; col = 0; break;
            case 2: lin = 0; col = 1; break;
            case 3: lin = 0; col = 2; break;
            case 4: lin = 1; col = 0; break;
            case 5: lin = 1; col = 1; break;
            case 6: lin = 1; col = 2; break;
            case 7: lin = 2; col = 0; break;
            case 8: lin = 2; col = 1; break;
            case 9: lin = 2; col = 2; break;
            default: printf(RED"Posição inválida!"RESET); cont--; continue;
        }

        if (tab[lin][col] == 'X' || tab[lin][col] == 'O') {
            printf(RED"Posição já ocupada! Tente novamente.\n"RESET);
            cont--;
            system("pause");
            continue;
        }

        tab[lin][col] = marcador;

        char vencedor = verificar_vencedor(tab);
        if (vencedor) {
            system("cls");
            mostrar_tab(tab);
            printf(GREEN"\nJogador '%c' venceu a rodada de desempate e é o vencedor final!\n"RESET, vencedor);
            return;
        } else if (cont == 8) {
            system("cls");
            mostrar_tab(tab);
            printf(RED"\nA rodada de desempate terminou em empate! O jogo finaliza empatado.\n"RESET);
            return;
        }
    }
}

int main() {
    Placar placar = {0, 0, 0};  // Inicializando o placar
    char tab[3][3];  // Tabuleiro do jogo

    int opcao = menu();

    if (opcao == 0) {
        printf("SAINDO DO JOGO");
        return 0;
    }

    for (int contadorpartidas = 1; contadorpartidas <= 4; contadorpartidas++) {
        inicializar_tabuleiro(tab);
        jogar_partida(tab, &placar);
    }

    // Após as quatro partidas, verifica se há empate
    if (placar.vitoriasX == placar.vitoriasO) {
        rodada_desempate(tab, &placar);
    } else if (placar.vitoriasX > placar.vitoriasO) {
        printf(GREEN"\nJogador X é o vencedor final!\n"RESET);
    } else {
        printf(GREEN"\nJogador O é o vencedor final!\n"RESET);
    }

    printf("\nFIM DE JOGO...\n");
    return 0;
}

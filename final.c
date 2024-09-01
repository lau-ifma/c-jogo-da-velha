#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

typedef struct {
    int vitoriasX;
    int vitoriasO;
    int empate;
    int rodadaAtual;
} Placar;

void inicializar_tabuleiro(char tab[3][3]) {
    char inicio[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    int i;
    for (i = 0; i < 3; i++) {
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
    int i;
    for (i = 0; i < 3; i++) {
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
    printf("------------------------------------\n");
    printf("--------   PLACAR DO JOGO   --------\n");
    printf("------------------------------------\n");
    printf("  Jogador x: %d       \n", placar->vitoriasX);
    printf("  Jogador o: %d       \n", placar->vitoriasO);
    printf("------------------------------------\n");
    printf(RESET);
}

int menu() {
    int escolha;
    printf("-----------------------------------\n");
    printf("---------- JOGO DA VELHA ----------\n");
    printf("-----------------------------------\n");
    printf("\n---------- MENU DE OPCOES ---------\n\n");
    printf("1 - INICIAR JOGO\n");
    printf("0 - SAIR\n>> ");
    scanf("%d", &escolha);
    while (escolha != 1 && escolha != 0) {
        printf("Opcao invalida, digite novamente: ");
        scanf("%d", &escolha);
    }
    return escolha;
}

void jogar_partida(char tab[3][3], Placar *placar) {
    int lin, col, posicao, cont;
    for (cont = 0; cont < 9; cont++) {
        system("cls");
        printf("---------- RODADA %d de 4 -----------\n", (placar->rodadaAtual + 1));
        exibir_placar(placar);
        mostrar_tab(tab);

        char marcador = (cont % 2 == 0) ? 'x' : 'o';

        printf("\n\nJogador '%c', escolha uma posicao livre [1-9]: ", marcador);
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
            default: printf(RED"Posicao invalida!"RESET); cont--; continue;
        }

        if (tab[lin][col] == 'x' || tab[lin][col] == 'o') {
            printf(RED"Posicao ja ocupada! Tente novamente.\n"RESET);
            cont--;
            system("pause");
            continue;
        }

        tab[lin][col] = marcador;

        char vencedor = verificar_vencedor(tab);
        if (vencedor) {
            system("cls");
            printf(GREEN"\nJogador '%c' venceu!\n"RESET, vencedor);
            if (vencedor == 'x') {placar->vitoriasX++;}
            else {placar->vitoriasO++;}
            exibir_placar(placar);
            mostrar_tab(tab);
            printf("\nPressione qualquer tecla para avancar\npara a proxima rodada >> "); getch();
            break;

        } else if (cont == 8) {
            system("cls");
            printf(GREEN"\nEmpate!\n"RESET);
            placar->empate++;
            exibir_placar(placar);
            mostrar_tab(tab);
            printf("\nPressione qualquer tecla para avancar\npara a proxima rodada >> ");getch();
            break;
        }
    }
    placar->rodadaAtual++;
}

void rodada_desempate(char tab[3][3], Placar *placar) {
    inicializar_tabuleiro(tab);
    int cont;
    for (cont = 0; cont < 9; cont++) {
        system("cls");
        printf(CYAN"-------- RODADA DE DESEMPATE --------\n\n"RESET);
        mostrar_tab(tab);

        char marcador = (cont % 2 == 0) ? 'x' : 'o';
        int posicao;
        printf("\n\nJogador '%c', escolha uma posicao livre [1-9]: ", marcador);
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
            default: printf(RED"Posicao invalida!"RESET); cont--; continue;
        }

        if (tab[lin][col] == 'x' || tab[lin][col] == 'o') {
            printf(RED"Posicao ja ocupada! Tente novamente.\n"RESET);
            cont--;
            system("pause"); continue;
        }

        tab[lin][col] = marcador;

        char vencedor = verificar_vencedor(tab);
        if (vencedor) {
            system("cls");
            mostrar_tab(tab);
            printf(GREEN"\nJogador '%c' venceu a rodada de desempate \nE eh o vencedor final!\n"RESET, vencedor);
            vencedor == 'x' ? placar->vitoriasX++ : placar->vitoriasO++;
            printf("\n---------- PLACAR FINAL ----------\n");
            printf("  Vitorias x: %d       \n", placar->vitoriasX);
            printf("  Vitorias o: %d       \n", placar->vitoriasO);
            return;
        } else if (cont == 8) {
            system("cls");
            mostrar_tab(tab);
            printf(CYAN"\nA rodada de desempate terminou em empate!\nO jogo finaliza empatado.\n"RESET);
            printf("\n---------- PLACAR FINAL ----------\n");
            printf("  Vitorias x: %d       \n", placar->vitoriasX);
            printf("  Vitorias o: %d       \n", placar->vitoriasO);
            return;
        }
    }
}

int main() {
    Placar placar = {0, 0, 0, 0};  // inicializando o placar zerado
    char tab[3][3];  // tabuleiro do jogo

    int opcao = menu();
    if (opcao == 0) {
        printf("FIM DE JOGO.");
        return 0;
    }
    int contador_partidas;
    for (contador_partidas = 1; contador_partidas <= 4; contador_partidas++) {
        inicializar_tabuleiro(tab);
        jogar_partida(tab, &placar);
    }

    // depois das quatro partidas, verificando cso de empate
    if (placar.vitoriasX == placar.vitoriasO) {
        rodada_desempate(tab, &placar);
    } else if (placar.vitoriasX > placar.vitoriasO) {
        printf(GREEN"\nJogador 'x' eh o vencedor final!\n"RESET);
        printf("\n---------- PLACAR FINAL ----------\n");
        printf("  Vitorias x: %d       \n", placar.vitoriasX);
        printf("  Vitorias o: %d       \n", placar.vitoriasO);
    } else {
        printf(GREEN"\nJogador 'o' eh o vencedor final!\n"RESET);
        printf("\n---------- PLACAR FINAL ----------\n");
        printf("  Vitorias x: %d       \n", placar.vitoriasX);
        printf("  Vitorias o: %d       \n", placar.vitoriasO);
    }
    printf("\nFIM DE JOGO.\n");
    return 0;
}

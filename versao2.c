#include <stdio.h>
#include <stdlib.h>

#define CYAN    "\033[36m" // Cor ciano
#define GREEN   "\033[32m" // Cor verde
#define RED     "\033[31m" // Cor vermelha
#define RESET   "\033[0m"  // Resetar cor para padrão

int vitoriasX = 0;
int vitorias0 = 0;
int empate = 0;

void mostrar_tab(char tab[3][3]) {
    printf("%c | %c | %c", tab[0][0], tab[0][1], tab[0][2]);
    printf("\n---------\n");
    printf("%c | %c | %c", tab[1][0], tab[1][1], tab[1][2]);
    printf("\n---------\n");
    printf("%c | %c | %c", tab[2][0], tab[2][1], tab[2][2]);
    printf("\n");
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

int menu(){
    int escolha;
    printf("===========================\n");
    printf("====== JOGO DA VELHA ======\n");
    printf("===========================\n");
    printf("\n------MENU DE OPCOES-------\n\n");
    printf("1 - INICIAR JOGO\n");
    printf("0 - SAIR\n>> ");
    scanf("%d", &escolha);
    while(escolha !=1 && escolha !=0){
        printf("Opção invalida, digite novamente: ");
        scanf("%d", &escolha);
    }
    return escolha;
}

int main() {
    int cont, lin, col, posicao;
    int contadorpartidas = 0;
    int opcao = menu();

    if (opcao == 0){
        printf("SAINDO DO JOGO");
        return 0;
    }

    while (contadorpartidas < 4) { // Joga até 4 partidas
        char matriz[3][3] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
        };

        for (cont = 0; cont < 9; cont++) {
            system("cls");
            printf("------ R0DADA %d de 4 -------\n\n", cont+1);
            mostrar_tab(matriz);

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

            if (matriz[lin][col] == 'X' || matriz[lin][col] == 'O') {
                printf(RED"Posição já ocupada! Tente novamente.\n"RESET);
                cont--;
                system("pause");
                continue;
            }

            matriz[lin][col] = marcador;

            char vencedor = verificar_vencedor(matriz);
            if (vencedor) {
                system("cls");
                mostrar_tab(matriz);
                printf(GREEN"\nJogador %c venceu!\n"RESET, vencedor);
                if (vencedor == 'X') vitoriasX++;
                else vitorias0++;
                break;
            } else if (cont == 8) {
                system("cls");
                mostrar_tab(matriz);
                printf("\nEmpate!\n");
                empate++;
                break;
            }
        }

        contadorpartidas++;
        printf(GREEN"\nEstatisticas: X: %d vitorias | O: %d vitorias | Empates: %d\n"RESET, vitoriasX, vitorias0, empate);
        system("pause");
    }

    // Após as quatro partidas, verifica o vencedor geral
    if (vitoriasX > vitorias0) {
        printf(GREEN"\nJogador X é o vencedor final!\n"RESET);
    } else if (vitorias0 > vitoriasX) {
        printf(GREEN"\nJogador O é o vencedor final!\n"RESET);
    } else {
        //Iniciando rodada de desempate

        char matriz[3][3] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
        };

        for (cont = 0; cont < 9; cont++) {
            system("cls");
            printf("---- RODADA DE DESEMPATE ----\n");
            mostrar_tab(matriz);

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

            if (matriz[lin][col] == 'X' || matriz[lin][col] == 'O') {
                printf(RED"Posicao ja ocupada! Tente novamente.\n"RESET);
                cont--;
                system("pause");
                continue;
            }

            matriz[lin][col] = marcador;

            char vencedor = verificar_vencedor(matriz);
            if (vencedor) {
                system("cls");
                mostrar_tab(matriz);
                printf(GREEN"\nJogador %c venceu a rodada de desempate e eh o vencedor final!\n"RESET, vencedor);
                break;
            } else if (cont == 8) {
                system("cls");
                mostrar_tab(matriz);
                printf(RED"\nA rodada de desempate terminou em empate! O jogo finaliza empatado.\n"RESET);
                break; // Finaliza o jogo em empate
            }
        }
    }

    printf("SAINDO DO JOGO\n");
    return 0;
}

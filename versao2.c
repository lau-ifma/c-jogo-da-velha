#include <stdio.h>

#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

#define CYAN    "\033[36m" // Cor ciano
#define GREEN   "\033[32m" // Cor verde
#define BLUE    "\033[34m" // Cor azul
#define RED     "\033[31m" // Cor vermelha
#define RESET   "\033[0m"  // Resetar cor para padrão

// Função para mostrar o tabuleiro
void mostrar_tab (char tab[3][3]){
    printf(CYAN"%c | %c | %c"RESET, tab[0][0], tab[0][1],  tab[0][2] );
    printf(CYAN"\n---------\n"RESET);
    printf(CYAN"%c | %c | %c"RESET, tab[1][0], tab[1][1],  tab[1][2] );
    printf(CYAN"\n---------\n"RESET);
    printf(CYAN"%c | %c | %c"RESET, tab[2][0], tab[2][1],  tab[2][2] );
    printf("\n");
}
// quatros jogadas, se empate mais uma
//contador

// Função para verificar se há um vencedor
int verificar_vencedor(char tab[3][3]) {
    // Verifica as linhas
    if (tab[0][0] == tab[0][1] && tab[0][1] == tab[0][2]) {
        return 1;
    }
    if (tab[1][0] == tab[1][1] && tab[1][1] == tab[1][2]) {
        return 1;
    }
    if (tab[2][0] == tab[2][1] && tab[2][1] == tab[2][2]) {
        return 1;
    }

    // Verifica as colunas
    if (tab[0][0] == tab[1][0] && tab[1][0] == tab[2][0]) {
        return 1;
    }
    if (tab[0][1] == tab[1][1] && tab[1][1] == tab[2][1]) {
        return 1;
    }
    if (tab[0][2] == tab[1][2] && tab[1][2] == tab[2][2]) {
        return 1;
    }
   
    // Verifica as diagonais
    if (tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2]) {
        return 1;
    }
    if (tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0]) {
        return 1;
    }
    return 0;
}

int menu(){
    int escolha;

        printf("====== MENU ======\n");
        printf("Digite 1 para Jogar\n");
        printf("Digite 0 para Sair\n");
        printf("==================\n");
        scanf("%d", &escolha);
         // VALIDEI SE É DIFERENTE
        while(escolha !=1 && escolha !=0){
             printf("Opção invalida, digite novamente: ");
             scanf("%d", &escolha);
        }
        return escolha;
    }

int main() {
    int cont, lin, col, posicao;
    // chama o meu e decide se o jogo começa
    int opcao = menu();
    if (opcao == 0){
        printf("SAINDO DO JOGO");
        return 0;
    }
                      //se for 1 passa pra cá
    int contadorpartidas = 0;
   
    while (contadorpartidas<5){
        char matriz[3][3] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
        };
   
   
        for (cont = 0; cont < 9; cont++){
            system("cls");
            mostrar_tab(matriz);
        
            char marcador = (cont % 2 == 0) ? 'X' : 'O';
            printf("\n\nJogador %c, escolha uma posicao [1-9]: ", marcador);
            scanf("%d", &posicao);
            // Converte a posição para linha e col
            switch(posicao) {
                case 1: lin = 0; col = 0; break;
                case 2: lin = 0; col = 1; break;
                case 3: lin = 0; col = 2; break;
                case 4: lin = 1; col = 0; break;
                case 5: lin = 1; col = 1; break;
                case 6: lin = 1; col = 2; break;
                case 7: lin = 2; col = 0; break;
                case 8: lin = 2; col = 1; break;
                case 9: lin = 2; col = 2; break;
                default: printf("Posição inválida!"); return 1;
            }
        
            if (matriz[lin][col] == 'X' || matriz[lin][col] == 'O') {
                printf(RED"Posicao ja ocupada! Tente novamente.\n"RESET);
                cont--;
                system("pause");
                continue;
            }
        
            matriz[lin][col] = marcador;
            if (verificar_vencedor(matriz)) {
                mostrar_tab(matriz);
                printf(GREEN"\nJogador %c venceu!\n"RESET, marcador);
                break;
            }
            contadorpartidas ++;
            system("pause");
        }
        mostrar_tab(matriz);
        printf(BLUE"\nEmpate!\n");

        return 0;
}}

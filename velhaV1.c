#include <stdio.h>
#define CYAN    "\033[36m" // Cor ciano
#define GREEN   "\033[32m" // Cor verde
#define BLUE    "\033[34m" // Cor azul
#define RED     "\033[31m" // Cor vermelha
#define RESET   "\033[0m"  // Resetar cor para padrão
/*
#define RESET   "\033[0m"  // Resetar cor para padrão
#define RED     "\033[31m" // Cor vermelha
#define GREEN   "\033[32m" // Cor verde
#define YELLOW  "\033[33m" // Cor amarela
#define BLUE    "\033[34m" // Cor azul
#define MAGENTA "\033[35m" // Cor magenta
#define CYAN    "\033[36m" // Cor ciano
#define WHITE   "\033[37m" // Cor branca

    - Exemplo de uso das cores
    printf(RED "Texto em vermelho\n" RESET);
    printf(GREEN "Texto em verde\n" RESET);
    printf(YELLOW "Texto em amarelo\n" RESET);
    printf(BLUE "Texto em azul\n" RESET);
    printf(MAGENTA "Texto em magenta\n" RESET);
    printf(CYAN "Texto em ciano\n" RESET);
    printf(WHITE "Texto em branco\n" RESET);
*/

// Função para mostrar o tabuleiro
void mostrar_tab (char tab[3][3]){
    printf(CYAN"%c | %c | %c"RESET, tab[0][0], tab[0][1],  tab[0][2] );
    printf(CYAN"\n---------\n"RESET);
    printf(CYAN"%c | %c | %c"RESET, tab[1][0], tab[1][1],  tab[1][2] );
    printf(CYAN"\n---------\n"RESET);
    printf(CYAN"%c | %c | %c"RESET, tab[2][0], tab[2][1],  tab[2][2] );
    printf("\n");
}

// Função para verificar se há um vencedor
int verificar_vencedor(char tab[3][3]) {
    for (int i = 0; i < 3; i++) {
        // Verifica as linhas
        if (tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2]) {
            return 1;
        }
        // Verifica as colunas
        if (tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i]) {
            return 1;
        }
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

int main() {
    char matriz[3][3] = {
        {'1', '2', '3'}, 
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    
    int cont, lin, col, posicao;
    
    for (cont = 0; cont < 9; cont++){
        system("cls");
        mostrar_tab(matriz);
        // Alterna entre X e O
        char marcador = (cont % 2 == 0) ? 'X' : 'O';
        
        // Recebe a posição diretamente do usuário
        printf("\n\nJogador %c, escolha uma posicao [1-9]: ", marcador);
        scanf("%d", &posicao);
        // Converte a posição para linha e coluna usando switch
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
            return 0;
        }
    }
    
    mostrar_tab(matriz);
    printf(BLUE"\nEmpate!\n");

    return 0;
}

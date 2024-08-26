#include <stdio.h>

// Função para mostrar o tabuleiro
void mostrar_tab (char tab[3][3]){
    printf("%c | %c | %c", tab[0][0], tab[0][1],  tab[0][2] );
    printf("\n---------\n");
    printf("%c | %c | %c", tab[1][0], tab[1][1],  tab[1][2] );
    printf("\n---------\n");
    printf("%c | %c | %c", tab[2][0], tab[2][1],  tab[2][2] );
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
        printf("\n\nJogador %c, escolha uma posição [1-9]: ", marcador);
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
            printf("Posição já ocupada! Tente novamente.\n");
            cont--;
            continue;
        }
        
        matriz[lin][col] = marcador;
        
        if (verificar_vencedor(matriz)) {
            mostrar_tab(matriz);
            printf("\nJogador %c venceu!\n", marcador);
            return 0;
        }
    }
    
    mostrar_tab(matriz);
    printf("\nEmpate!\n");

    return 0;
}
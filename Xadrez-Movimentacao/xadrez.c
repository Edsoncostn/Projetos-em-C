#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Simulacao textual de movimentos, sem tabuleiro ou capturas. */

static int ler_opcao(const char *mensagem, int minimo, int maximo, int *saida) {
    char linha[80], *fim;
    long valor;
    int ch;

    for (;;) {
        printf("%s", mensagem);
        fflush(stdout);
        if (!fgets(linha, sizeof linha, stdin)) return 0;
        if (!strchr(linha, '\n') && !feof(stdin)) {
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            puts("Entrada muito longa. Tente novamente.");
            continue;
        }

        errno = 0;
        valor = strtol(linha, &fim, 10);
        while (*fim == ' ' || *fim == '\t' || *fim == '\r' || *fim == '\n') fim++;
        if (errno == 0 && fim != linha && *fim == '\0'
            && valor >= minimo && valor <= maximo
            && valor >= INT_MIN && valor <= INT_MAX) {
            *saida = (int)valor;
            return 1;
        }
        printf("Entrada invalida. Escolha um numero de %d a %d.\n", minimo, maximo);
    }
}

/* Uma chamada recursiva para cada casa: exercicio de recursividade. */
static void mover_recursivamente(const char *peca, const char *direcao, int casas) {
    if (casas <= 0) return;
    printf("%s se moveu %s\n", peca, direcao);
    mover_recursivamente(peca, direcao, casas - 1);
}

static void mover_cavalo(int direcao) {
    static const char *vertical[] = {"para cima", "para baixo"};
    static const char *horizontal[] = {"para a direita", "para a esquerda"};
    int sentido_vertical, sentido_horizontal;

    /* 1-4: dois passos verticais e um horizontal;
       5-8: dois horizontais e um vertical.
       Sao representacoes textuais; o cavalo salta no xadrez real. */
    if (direcao <= 4) {
        sentido_vertical = (direcao - 1) / 2;
        sentido_horizontal = (direcao - 1) % 2;
        for (int i = 0; i < 2; i++)
            printf("O cavalo se moveu %s\n", vertical[sentido_vertical]);
        printf("O cavalo se moveu %s\n", horizontal[sentido_horizontal]);
    } else {
        int orientacao = direcao - 5;
        sentido_horizontal = orientacao / 2;
        sentido_vertical = orientacao % 2;
        for (int i = 0; i < 2; i++)
            printf("O cavalo se moveu %s\n", horizontal[sentido_horizontal]);
        printf("O cavalo se moveu %s\n", vertical[sentido_vertical]);
    }
}

int main(void) {
    static const char *nomes[] = {"O bispo", "A torre", "A rainha"};
    static const int limite[] = {5, 5, 8};
    static const char *direcoes_bispo[] = {
        "na diagonal superior esquerda", "na diagonal superior direita",
        "na diagonal inferior esquerda", "na diagonal inferior direita"
    };
    static const char *direcoes_torre[] = {
        "para cima", "para baixo", "para a esquerda", "para a direita"
    };
    static const char *direcoes_rainha[] = {
        "para cima", "para baixo", "para a esquerda", "para a direita",
        "na diagonal superior esquerda", "na diagonal superior direita",
        "na diagonal inferior esquerda", "na diagonal inferior direita"
    };
    static const char *direcoes_cavalo[] = {
        "duas para cima e uma para a direita",
        "duas para cima e uma para a esquerda",
        "duas para baixo e uma para a direita",
        "duas para baixo e uma para a esquerda",
        "duas para a direita e uma para cima",
        "duas para a direita e uma para baixo",
        "duas para a esquerda e uma para cima",
        "duas para a esquerda e uma para baixo"
    };

    int peca, casas, direcao;
    const char *const *direcoes;
    int quantidade_direcoes;

    puts("Simulador textual de movimentos de xadrez");
    puts("1 - Bispo\n2 - Torre\n3 - Rainha\n4 - Cavalo");
    if (!ler_opcao("Escolha a peca (1-4): ", 1, 4, &peca)) return 1;

    if (peca == 4) {
        puts("\nO cavalo se move em L (duas casas em um eixo, uma no outro).");
        for (int i = 0; i < 8; i++)
            printf("%d - %s\n", i + 1, direcoes_cavalo[i]);
        if (!ler_opcao("Escolha uma direcao (1-8): ", 1, 8, &direcao)) return 1;
        mover_cavalo(direcao);
        return 0;
    }

    printf("\n%s: ate %d casas por movimento nesta simulacao.\n",
           nomes[peca - 1], limite[peca - 1]);
    if (!ler_opcao("Quantas casas deseja mover? ", 1,
                   limite[peca - 1], &casas)) return 1;

    if (peca == 1) {
        direcoes = direcoes_bispo;
        quantidade_direcoes = 4;
    } else if (peca == 2) {
        direcoes = direcoes_torre;
        quantidade_direcoes = 4;
    } else {
        direcoes = direcoes_rainha;
        quantidade_direcoes = 8;
    }

    puts("Direcoes disponiveis:");
    for (int i = 0; i < quantidade_direcoes; i++)
        printf("%d - %s\n", i + 1, direcoes[i]);

    if (!ler_opcao("Escolha a direcao: ", 1,
                   quantidade_direcoes, &direcao)) return 1;
    mover_recursivamente(nomes[peca - 1], direcoes[direcao - 1], casas);
    return 0;
}

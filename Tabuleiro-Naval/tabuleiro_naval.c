#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5
#define TAMANHO_NAVIO 3

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define NAVIO_DESTRUIDO 7
#define QUANTIDADE_NAVIOS 2

static int ler_inteiro(const char *mensagem, int *saida) {
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
            && valor >= -2147483647L - 1 && valor <= 2147483647L) {
            *saida = (int)valor;
            return 1;
        }
        puts("Informe um numero inteiro valido.");
    }
}

static void iniciar_tabuleiro(int mapa[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                             int ids[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            mapa[i][j] = AGUA;
            ids[i][j] = 0;
        }
    }
}

/* direcao: 0 horizontal, 1 vertical, 2 diagonal ascendente, 3 descendente. */
static void deslocamento(int direcao, int passo, int *dx, int *dy) {
    static const int direcoes[4][2] = {
        {0, 1}, {1, 0}, {-1, 1}, {1, 1}
    };
    *dx = direcoes[direcao][0] * passo;
    *dy = direcoes[direcao][1] * passo;
}

static int posicionar_navio(int mapa[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                           int ids[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                           int identificador) {
    int linha, coluna, direcao, valido;

    for (;;) {
        printf("\nPosicionamento do navio %d (%d celulas):\n",
               identificador, TAMANHO_NAVIO);
        if (!ler_inteiro("Linha inicial (1 a 10): ", &linha)
            || !ler_inteiro("Coluna inicial (1 a 10): ", &coluna)
            || !ler_inteiro("Direcao (0 horizontal, 1 vertical, "
                            "2 diagonal ascendente, 3 descendente): ", &direcao)) {
            return 0;
        }

        if (linha < 1 || linha > TAMANHO_TABULEIRO
            || coluna < 1 || coluna > TAMANHO_TABULEIRO
            || direcao < 0 || direcao > 3) {
            puts("Coordenada ou direcao fora dos limites. Tente novamente.");
            continue;
        }
        linha--;
        coluna--;
        valido = 1;

        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            int dx, dy, x, y;
            deslocamento(direcao, i, &dx, &dy);
            x = linha + dx;
            y = coluna + dy;
            if (x < 0 || x >= TAMANHO_TABULEIRO
                || y < 0 || y >= TAMANHO_TABULEIRO || mapa[x][y] != AGUA) {
                valido = 0;
                break;
            }
        }

        if (!valido) {
            puts("Navio fora do tabuleiro ou sobreposto. Tente novamente.");
            continue;
        }

        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            int dx, dy, x, y;
            deslocamento(direcao, i, &dx, &dy);
            x = linha + dx;
            y = coluna + dy;
            mapa[x][y] = NAVIO;
            ids[x][y] = identificador;
        }
        return 1;
    }
}

static void criar_matriz_habilidade(
    int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int tipo) {
    const int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (tipo == 0) {  /* Cone */
                matriz[i][j] = (j >= centro - i && j <= centro + i);
            } else if (tipo == 1) {  /* Cruz */
                matriz[i][j] = (i == centro || j == centro);
            } else {  /* Losango (octaedro projetado) */
                matriz[i][j] = (abs(i - centro) + abs(j - centro) <= centro);
            }
        }
    }
}

static void aplicar_habilidade(
    int mapa[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
    int ids[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int mascara[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int origem_x = rand() % TAMANHO_TABULEIRO;
    int origem_y = rand() % TAMANHO_TABULEIRO;
    int tipo = rand() % 3;
    int atingidos[QUANTIDADE_NAVIOS + 1] = {0};
    const char *nomes[] = {"Cone", "Cruz", "Losango"};

    criar_matriz_habilidade(mascara, tipo);
    printf("\nHabilidade %s em (%d, %d):\n",
           nomes[tipo], origem_x + 1, origem_y + 1);

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int x = origem_x + i - TAMANHO_HABILIDADE / 2;
            int y = origem_y + j - TAMANHO_HABILIDADE / 2;
            if (x < 0 || x >= TAMANHO_TABULEIRO
                || y < 0 || y >= TAMANHO_TABULEIRO || !mascara[i][j]) continue;

            if (mapa[x][y] == NAVIO) {
                atingidos[ids[x][y]] = 1;
            } else if (mapa[x][y] == AGUA) {
                mapa[x][y] = HABILIDADE;
            }
        }
    }

    /* Somente os navios atingidos sao marcados como destruidos. */
    int algum = 0;
    for (int navio = 1; navio <= QUANTIDADE_NAVIOS; navio++) {
        if (!atingidos[navio]) continue;
        algum = 1;
        for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
                if (ids[i][j] == navio) mapa[i][j] = NAVIO_DESTRUIDO;
            }
        }
        printf("Navio %d atingido e marcado como destruido.\n", navio);
    }
    if (!algum) puts("Nenhum navio atingido.");
}

static void mostrar_tabuleiro(
    int mapa[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    puts("\nLegenda: 0 agua | 3 navio | 5 ataque na agua | 7 navio destruido");
    printf("    ");
    for (int coluna = 1; coluna <= TAMANHO_TABULEIRO; coluna++)
        printf("%2d ", coluna);
    putchar('\n');
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d: ", i + 1);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
            printf("%2d ", mapa[i][j]);
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    int mapa[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int ids[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    unsigned int semente = (unsigned int)time(NULL);

    if (argc == 3 && strcmp(argv[1], "--seed") == 0) {
        char *fim;
        unsigned long valor;
        errno = 0;
        valor = strtoul(argv[2], &fim, 10);
        if (errno != 0 || argv[2][0] == '-' || fim == argv[2]
            || *fim != '\0' || valor > 4294967295UL) {
            fputs("Semente invalida.\n", stderr);
            return 1;
        }
        semente = (unsigned int)valor;
    } else if (argc != 1) {
        fprintf(stderr, "Uso: %s [--seed NUMERO]\n", argv[0]);
        return 1;
    }
    srand(semente);

    iniciar_tabuleiro(mapa, ids);
    for (int i = 1; i <= QUANTIDADE_NAVIOS; i++) {
        if (!posicionar_navio(mapa, ids, i)) {
            fputs("\nEntrada encerrada antes de posicionar os navios.\n", stderr);
            return 1;
        }
    }

    puts("\nTabuleiro inicial:");
    mostrar_tabuleiro(mapa);
    for (int i = 1; i <= 2; i++) {
        printf("\nAtivando habilidade %d...\n", i);
        aplicar_habilidade(mapa, ids);
        mostrar_tabuleiro(mapa);
    }
    return 0;
}

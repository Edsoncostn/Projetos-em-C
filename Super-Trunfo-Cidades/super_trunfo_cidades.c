#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Super Trunfo: cadastro e comparacao de duas cidades. */
typedef struct {
    char estado;
    char codigo[4];          /* Ex.: A01 */
    char nome[50];
    unsigned long habitantes;
    double area_km2;
    double pib;
    unsigned int pontos_turisticos;
    double pib_per_capita;
    double densidade;
    double super_poder;
} Cidade;

static const char *ATRIBUTOS[] = {
    "Numero de habitantes", "Area (km2)", "PIB",
    "Pontos turisticos", "PIB per capita",
    "Densidade demografica (menor vence)", "Super Poder"
};

/* Le a linha inteira, descarta entradas maiores que o buffer e aceita
   nomes de cidade com espacos. Retorna 0 em EOF. */
static int ler_texto(const char *mensagem, char *destino, size_t tamanho) {
    char *inicio;
    size_t n;
    int ch;

    for (;;) {
        printf("%s", mensagem);
        fflush(stdout);
        if (!fgets(destino, (int)tamanho, stdin)) {
            return 0;
        }
        n = strcspn(destino, "\n");
        if (destino[n] == '\n') {
            destino[n] = '\0';
        } else if (!feof(stdin)) {
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            puts("Entrada muito longa. Tente novamente.");
            continue;
        }
        inicio = destino;
        while (isspace((unsigned char)*inicio)) inicio++;
        memmove(destino, inicio, strlen(inicio) + 1);
        n = strlen(destino);
        while (n > 0 && isspace((unsigned char)destino[n - 1])) {
            destino[--n] = '\0';
        }
        if (n != 0) return 1;
        puts("Digite um valor nao vazio.");
    }
}

static int ler_ulong(const char *mensagem, unsigned long minimo,
                     unsigned long maximo, unsigned long *saida) {
    char linha[80], *fim, *p;
    unsigned long valor;
    for (;;) {
        if (!ler_texto(mensagem, linha, sizeof linha)) return 0;
        p = linha;
        if (*p == '-') {
            puts("Informe um numero nao negativo.");
            continue;
        }
        errno = 0;
        valor = strtoul(p, &fim, 10);
        while (isspace((unsigned char)*fim)) fim++;
        if (errno == 0 && fim != p && *fim == '\0'
            && valor >= minimo && valor <= maximo) {
            *saida = valor;
            return 1;
        }
        puts("Numero invalido ou fora dos limites. Tente novamente.");
    }
}

static int ler_double(const char *mensagem, int deve_ser_positivo, double *saida) {
    char linha[80], *fim;
    double valor;
    for (;;) {
        if (!ler_texto(mensagem, linha, sizeof linha)) return 0;
        errno = 0;
        valor = strtod(linha, &fim);
        while (isspace((unsigned char)*fim)) fim++;
        if (errno == 0 && fim != linha && *fim == '\0'
            && isfinite(valor) && (deve_ser_positivo ? valor > 0.0 : valor >= 0.0)) {
            *saida = valor;
            return 1;
        }
        puts("Valor invalido. Use ponto para decimais (ex.: 12.5).");
    }
}

static int cadastrar(Cidade *c, int numero) {
    char entrada[8];
    unsigned long pontos;
    printf("\n--- Carta %d ---\n", numero);

    for (;;) {
        if (!ler_texto("Inicial do estado (A-H): ", entrada, sizeof entrada)) return 0;
        if (strlen(entrada) == 1) {
            c->estado = (char)toupper((unsigned char)entrada[0]);
            if (c->estado >= 'A' && c->estado <= 'H') break;
        }
        puts("Estado invalido. Escolha uma letra de A ate H.");
    }
    for (;;) {
        if (!ler_texto("Codigo da carta (ex.: A01 a A04): ",
                       entrada, sizeof entrada)) return 0;
        entrada[0] = (char)toupper((unsigned char)entrada[0]);
        if (strlen(entrada) == 3 && entrada[0] == c->estado
            && entrada[1] == '0' && entrada[2] >= '1' && entrada[2] <= '4') {
            strcpy(c->codigo, entrada);
            break;
        }
        puts("Codigo invalido: use a letra do estado e 01, 02, 03 ou 04.");
    }

    if (!ler_texto("Nome da cidade: ", c->nome, sizeof c->nome)) return 0;
    if (!ler_ulong("Numero de habitantes (>0): ", 1, ULONG_MAX,
                   &c->habitantes)) return 0;
    if (!ler_double("Area da cidade em km2 (>0): ", 1, &c->area_km2)) return 0;
    if (!ler_double("PIB da cidade (>=0): ", 0, &c->pib)) return 0;
    if (!ler_ulong("Numero de pontos turisticos (>=0): ", 0, UINT_MAX,
                   &pontos)) return 0;
    c->pontos_turisticos = (unsigned int)pontos;

    c->pib_per_capita = c->pib / (double)c->habitantes;
    c->densidade = (double)c->habitantes / c->area_km2;
    c->super_poder = (double)c->habitantes + c->area_km2 + c->pib
                     + (double)c->pontos_turisticos + c->pib_per_capita
                     + 1.0 / c->densidade;
    return 1;
}

static void mostrar_cidade(const Cidade *c) {
    printf("\n%s (%s), estado %c\n", c->nome, c->codigo, c->estado);
    printf("  Habitantes: %lu\n", c->habitantes);
    printf("  Area: %.2f km2\n", c->area_km2);
    printf("  PIB: %.2f\n", c->pib);
    printf("  Pontos turisticos: %u\n", c->pontos_turisticos);
    printf("  PIB per capita: %.4f\n", c->pib_per_capita);
    printf("  Densidade demografica: %.4f hab/km2\n", c->densidade);
    printf("  Super Poder (indice didatico): %.4f\n", c->super_poder);
}

static double atributo(const Cidade *c, int opcao) {
    switch (opcao) {
        case 1: return (double)c->habitantes;
        case 2: return c->area_km2;
        case 3: return c->pib;
        case 4: return (double)c->pontos_turisticos;
        case 5: return c->pib_per_capita;
        case 6: return c->densidade;
        default: return c->super_poder;
    }
}

/* 1: primeira carta; -1: segunda; 0: empate.
   A menor densidade demografica tem vantagem. */
static int comparar(const Cidade *a, const Cidade *b, int opcao) {
    double v1 = atributo(a, opcao);
    double v2 = atributo(b, opcao);
    int resultado = (v1 > v2) - (v1 < v2);
    return opcao == 6 ? -resultado : resultado;
}

static void menu(void) {
    puts("\nEscolha o atributo para comparar:");
    for (int i = 0; i < 7; i++) {
        printf("%d - %s\n", i + 1, ATRIBUTOS[i]);
    }
    puts("8 - Todos os atributos");
}

static int ler_opcao(const char *mensagem, int *opcao) {
    unsigned long valor;
    if (!ler_ulong(mensagem, 1, 8, &valor)) return 0;
    *opcao = (int)valor;
    return 1;
}

static void pontuar(const Cidade *a, const Cidade *b, int opcao,
                    int *placar_a, int *placar_b) {
    int resultado = comparar(a, b, opcao);
    printf("%s: ", ATRIBUTOS[opcao - 1]);
    if (resultado > 0) {
        (*placar_a)++;
        printf("venceu %s\n", a->nome);
    } else if (resultado < 0) {
        (*placar_b)++;
        printf("venceu %s\n", b->nome);
    } else {
        (*placar_a)++;
        (*placar_b)++;
        puts("empate; ambas recebem 1 ponto");
    }
}

int main(void) {
    Cidade cidades[2];
    int primeira, segunda, placar1 = 0, placar2 = 0;

    puts("Bem-vindo ao Super Trunfo de Cidades!");
    puts("Cadastre duas cartas para comparar seus atributos.");
    if (!cadastrar(&cidades[0], 1) || !cadastrar(&cidades[1], 2)) {
        fputs("\nEntrada encerrada antes de concluir o cadastro.\n", stderr);
        return 1;
    }

    mostrar_cidade(&cidades[0]);
    mostrar_cidade(&cidades[1]);

    menu();
    if (!ler_opcao("Primeira opcao (1-8): ", &primeira)) return 1;
    if (primeira == 8) {
        for (int i = 1; i <= 7; i++) {
            pontuar(&cidades[0], &cidades[1], i, &placar1, &placar2);
        }
    } else {
        pontuar(&cidades[0], &cidades[1], primeira, &placar1, &placar2);
        do {
            menu();
            if (!ler_opcao("Segunda opcao (1-7, diferente da primeira): ",
                           &segunda)) return 1;
            if (segunda == primeira || segunda == 8) {
                puts("Escolha outro atributo entre 1 e 7.");
            }
        } while (segunda == primeira || segunda == 8);
        pontuar(&cidades[0], &cidades[1], segunda, &placar1, &placar2);
    }

    printf("\nPlacar final: %s %d x %d %s\n",
           cidades[0].nome, placar1, placar2, cidades[1].nome);
    if (placar1 > placar2) printf("Vencedora: %s\n", cidades[0].nome);
    else if (placar2 > placar1) printf("Vencedora: %s\n", cidades[1].nome);
    else puts("Resultado: empate entre as cartas.");
    return 0;
}

#ifndef JOGO_H
#define JOGO_H

#include "cobra.h"

typedef struct { // Estrutura para representar o estado do jogo
    Cobra cobra; // Estrutura que representa a cobra no jogo

    float macaX; // Posição X da maçã
    float macaY; // Posição Y da maçã

    int pontuacao; // Pontuação do jogador
    int crescer; // Indica se a cobra deve crescer no próximo movimento
    int jogoIniciado; // Indica se o jogo foi iniciado
    int jogoEncerrado; // Indica se o jogo foi encerrado
    int jogoPausado; // Indica se o jogo está pausado
    int direcaoAlterada; // Indica se a direção da cobra foi alterada na mesma atualização para evitar múltiplas alterações

    int intervalo; // Intervalo de tempo usado para controlar a velocidade progressiva do jogo
    int macasComidas; // Contador de maçãs comidas, usado para aumentar a velocidade do jogo a cada 5 maçãs comidas

    char Texto[100];
} Jogo;

#endif
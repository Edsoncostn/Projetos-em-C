#ifndef JOGO_H
#define JOGO_H

#include "cobra.h"

typedef struct {
    Cobra cobra;

    float macaX;
    float macaY;

    int pontuacao;
    int crescer;
    int jogoIniciado;
    int jogoEncerrado;
    int jogoPausado;
    int direcaoAlterada;

    int intervalo;
    int macasComidas;

    char Texto[100];
} Jogo;

#endif
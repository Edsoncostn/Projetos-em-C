#include "cobra.h"

void cobra_iniciar(Cobra *cobra){ // Função para inicializar a cobra

    cobra -> tamanho = 3;

    cobra -> x[0] = 315.0f;    // Cabeça da cobra
    cobra -> y[0] = 315.0f;  

    cobra -> x[1] = 285.0f;   // Corpo 1 da cobra
    cobra -> y[1] = 315.0f;

    cobra -> x[2] = 255.0f;   // Corpo 2 da cobra
    cobra -> y[2] = 315.0f;

    cobra -> direcaoX = 0.0f; // Direção inicial da cobra (parada)
    cobra -> direcaoY = 0.0f;

}

#define PASSO 30.0f

void cobra_mover(Cobra *cobra, int cresce){

    if(cresce && cobra -> tamanho < MAX_SEGMENTOS){  // Verifica se a cobra deve crescer e se não atingiu o tamanho máximo
        cobra -> tamanho++;
    }

    if(cobra -> direcaoX == 0.0f && cobra -> direcaoY == 00.0f){ // Verifica se a cobra está parada

        return;
    }

     for (int i = cobra->tamanho - 1; i > 0; i--) { // Move cada segmento da cobra para a posição do segmento anterior
        cobra->x[i] = cobra->x[i - 1];
        cobra->y[i] = cobra->y[i - 1];
    }

    cobra->x[0] += cobra->direcaoX * PASSO; // Move a cabeça da cobra na direção atual
    cobra->y[0] += cobra->direcaoY * PASSO;

}

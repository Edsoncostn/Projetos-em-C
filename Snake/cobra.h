#ifndef COBRA_H
#define COBRA_H

#define MAX_SEGMENTOS 400 // Define o tamanho máximo da cobra

typedef struct { // Estrutura para representar a cobra

    int tamanho;

    float direcaoX;
    float direcaoY;

    
    float x[MAX_SEGMENTOS];
    float y[MAX_SEGMENTOS];

} Cobra;

void cobra_iniciar(Cobra *cobra); // Função para inicializar a cobra

void cobra_mover(Cobra *cobra,int cresce); // Função para mover a cobra, com parâmetro para indicar se deve crescer

#endif
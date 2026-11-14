
#include <GL/freeglut.h>
#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGURA 600.0f
#define ALTURA 600.0f
#define RAIO 15.0f

Jogo jogo;

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < jogo.cobra.tamanho; i++) { // Desenha cada segmento da cobra

        if (i == 0) {
            glColor3f(0.0f, 0.6f, 0.0f);
        } else if (i%2 == 0){
            glColor3f(0.0f, 0.8f, 0.0f);
        } else {
            glColor3f(0.0f, 0.7f, 0.0f);
        }

        glBegin(GL_QUADS); // Desenha um quadrado para cada segmento da cobra

            glVertex2f(jogo.cobra.x[i] - RAIO, jogo.cobra.y[i] - RAIO);
            glVertex2f(jogo.cobra.x[i] + RAIO, jogo.cobra.y[i] - RAIO);
            glVertex2f(jogo.cobra.x[i] + RAIO, jogo.cobra.y[i] + RAIO);
            glVertex2f(jogo.cobra.x[i] - RAIO, jogo.cobra.y[i] + RAIO);

        glEnd();
    }

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS); // Desenha a maçã

        glVertex2f(jogo.macaX - RAIO, jogo.macaY - RAIO);
        glVertex2f(jogo.macaX + RAIO, jogo.macaY - RAIO);
        glVertex2f(jogo.macaX + RAIO, jogo.macaY + RAIO);
        glVertex2f(jogo.macaX - RAIO, jogo.macaY + RAIO);

    glEnd();

    glutSwapBuffers();
}

void teclado(unsigned char tecla, int mouseX, int mouseY){ // Função para lidar com eventos de teclado
 
    

    if (tecla == 27){ // Verifica se a tecla pressionada é ESC
        
        exit(0);
    }

    if(jogo.jogoEncerrado){ // Se o jogo estiver encerrado, não faz nada
        return;

    }

    if(tecla == ' ' && !jogo.jogoIniciado){ // Verifica se a tecla pressionada é ESPACO e se o jogo não foi iniciado

        jogo.jogoIniciado = 1;

        jogo.cobra.direcaoX = 1.0f;
        jogo.cobra.direcaoY = 0.0f;

        snprintf(jogo.Texto, sizeof(jogo.Texto), "Jogo da Cobra | Score: %02d | Pressione P para pausar e ESC para sair", jogo.pontuacao);
        glutSetWindowTitle(jogo.Texto);

    }

    if((tecla == 'p' || tecla == 'P')&& jogo.jogoIniciado){  // Verifica se a tecla pressionada é P ou p e se o jogo foi iniciado
        jogo.jogoPausado = !jogo.jogoPausado;
      
        if(jogo.jogoPausado){
            snprintf(jogo.Texto, sizeof(jogo.Texto), "Jogo Pausado | Score: %02d | Pressione P para continuar", jogo.pontuacao);
            glutSetWindowTitle(jogo.Texto);
        } else{
            snprintf(jogo.Texto, sizeof(jogo.Texto), "Jogo da Cobra | Score: %02d | Pressione P para pausar e ESC para sair", jogo.pontuacao);
            glutSetWindowTitle(jogo.Texto);
        }
    }
}

void gerarMaca(){ // Função para gerar a posição da maçã de forma aleatória

    int ocupada;

    do{

        jogo.macaX = 15.0f + (rand() % 20) * 30.0f; // Gera uma posição aleatória para a maçã dentro da tela, garantindo que esteja alinhada com a grade
        jogo.macaY = 15.0f + (rand() % 20) * 30.0f;

        ocupada = 0; // Inicializa a variável ocupada como 0 (não ocupada)

        for(int i = 0; i < jogo.cobra.tamanho; i++){ // Verifica se a posição gerada para a maçã está ocupada por algum segmento da cobra
            if(jogo.cobra.x[i] == jogo.macaX && jogo.cobra.y[i] == jogo.macaY){
                ocupada = 1;
                break;
            }
        }
    } while(ocupada); // Garante que a maçã não seja gerada em uma posição ocupada pela cobra
}

void iniciarJogo(){

    cobra_iniciar(&jogo.cobra); // Inicializa a cobra

    jogo.jogoIniciado = 0;
    jogo.jogoEncerrado = 0;
    jogo.jogoPausado = 0;

    jogo.pontuacao = 0;
    jogo.crescer = 0;
    jogo.direcaoAlterada = 0;

    jogo.intervalo = 120;
    jogo.macasComidas = 0;

}

void mouse(int botao, int estado, int mouseX, int mouseY){ // Função para lidar com eventos do mouse

    if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && jogo.jogoEncerrado){ // Verifica se o botão pressionado é o esquerdo do mouse, se o estado é pressionado e se o jogo está encerrado

        iniciarJogo(); // Reinicia o jogo
        gerarMaca(); // Gera uma nova posição para a maçã

        snprintf(jogo.Texto, sizeof(jogo.Texto), "Jogo da Cobra | Score: %02d |Pressione ESPACO para continuar e ESC para sair", jogo.pontuacao);
        glutSetWindowTitle(jogo.Texto);

        glutPostRedisplay();
    }
}



void atualizar(int valor) { // Função para atualizar o jogo a cada intervalo de tempo

    if (jogo.jogoIniciado && !jogo.jogoEncerrado && !jogo.jogoPausado) { 

        cobra_mover(&jogo.cobra, jogo.crescer);
        jogo.crescer = 0;
        jogo.direcaoAlterada = 0; // Reseta a variável direcaoAlterada para permitir que a direção seja alterada novamente

        for (int i = 1; i < jogo.cobra.tamanho; i++) { // Verifica se a cabeça da cobra colidiu com algum segmento do corpo
            if (jogo.cobra.x[0] == jogo.cobra.x[i] && jogo.cobra.y[0] == jogo.cobra.y[i]) {
                jogo.jogoEncerrado = 1;// Indica que o jogo foi encerrado devido a uma colisão com o próprio corpo da cobra
                snprintf(jogo.Texto, sizeof(jogo.Texto), "Game Over | Score: %02d | Pressione o botao esquerdo do mouse para reiniciar", jogo.pontuacao);
                glutSetWindowTitle(jogo.Texto);
                break;
            }
        }


        if (jogo.cobra.x[0] - RAIO < 0 ||  // Verifica se a cabeça da cobra colidiu com as bordas da tela
            jogo.cobra.x[0] + RAIO > LARGURA ||
            jogo.cobra.y[0] - RAIO < 0 ||
            jogo.cobra.y[0] + RAIO > ALTURA) {

            jogo.jogoEncerrado = 1; // Indica que o jogo foi encerrado devido a uma colisão com as bordas da tela
            snprintf(jogo.Texto, sizeof(jogo.Texto), "Game Over | Score: %02d | Pressione o botao esquerdo do mouse para reiniciar", jogo.pontuacao);
            glutSetWindowTitle(jogo.Texto);
        }

         if (!jogo.jogoEncerrado && jogo.cobra.x[0] == jogo.macaX && jogo.cobra.y[0] == jogo.macaY){ // Verifica se a cabeça da cobra colidiu com a maçã
            
            
            jogo.crescer = 1; // Indica que a cobra deve crescer no próximo movimento
            jogo.pontuacao += 10; // Incrementa a pontuação em 10 pontos
            gerarMaca(); // Gera uma nova posição para a maçã
            snprintf(jogo.Texto, sizeof(jogo.Texto), "Jogo da Cobra | Score: %02d | Pressione P para pausar e ESC para sair", jogo.pontuacao);
            glutSetWindowTitle(jogo.Texto);
        }

    }



    glutPostRedisplay();

    glutTimerFunc(120, atualizar, 0);
}



void tecladoEspecial(int tecla, int mouseX, int mouseY) { // Função para lidar com eventos de teclado especial

    if(!jogo.jogoIniciado || jogo.jogoEncerrado || jogo.jogoPausado || jogo.direcaoAlterada){ // verifica se o jogo não foi iniciado, se o jogo está encerrado, se o jogo está pausado ou se a direção já foi alterada na mesma atualização
        return;

    }

    else if (tecla == GLUT_KEY_RIGHT && jogo.cobra.direcaoX != -1.0f) { // Verifica se a tecla pressionada é a seta para a direita e se a cobra não está indo para a esquerda
        jogo.cobra.direcaoX = 1.0f; 
        jogo.cobra.direcaoY = 0.0f;
        jogo.direcaoAlterada = 1; // Indica que a direção foi alterada para evitar múltiplas alterações na mesma atualização
    }

    else if (tecla == GLUT_KEY_LEFT && jogo.cobra.direcaoX != 1.0f) { // Verifica se a tecla pressionada é a seta para a esquerda e se a cobra não está indo para a direita
        jogo.cobra.direcaoX = -1.0f;
        jogo.cobra.direcaoY = 0.0f;
        jogo.direcaoAlterada = 1;
    }

    else if (tecla == GLUT_KEY_UP && jogo.cobra.direcaoY != -1.0f) { // Verifica se a tecla pressionada é a seta para cima e se a cobra não está indo para baixo
        jogo.cobra.direcaoX = 0.0f; 
        jogo.cobra.direcaoY = 1.0f;
        jogo.direcaoAlterada = 1;
    }

    else if (tecla == GLUT_KEY_DOWN && jogo.cobra.direcaoY != 1.0f) { // Verifica se a tecla pressionada é a seta para baixo e se a cobra não está indo para cima
        jogo.cobra.direcaoX = 0.0f;
        jogo.cobra.direcaoY = -1.0f;
        jogo.direcaoAlterada = 1;
    }



    glutPostRedisplay();
}


void reshape(int novaLargura, int novaAltura) { // Função para lidar com eventos de redimensionamento da janela

    int lado = (novaLargura < novaAltura) ? novaLargura : novaAltura; // Define o lado do viewport como o menor valor entre a largura e a altura da janela

    int posX = (novaLargura - lado) / 2; 
    int posY = (novaAltura - lado) / 2;

    glViewport(posX, posY, lado, lado); // Define o viewport para ser um quadrado centralizado na janela

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();

    glOrtho(0, 600, 0, 600, -1, 1);

    glMatrixMode(GL_MODELVIEW);
}




int main(int argc, char **argv) { // Função principal

    iniciarJogo(); // Inicializa o jogo

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Define o modo de exibição para usar buffer duplo e cores RGB

    glutInitWindowSize((int)LARGURA, (int)ALTURA); // Define o tamanho inicial da janela

    glutInitWindowPosition(100, 100); // Define a posição inicial da janela

    glutCreateWindow("Jogo da Cobra | Pressione ESPACO para iniciar");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Define a cor de fundo da janela como preto

    // chamada das funções
    glutDisplayFunc(display);
    glutSpecialFunc(tecladoEspecial);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);

    glutTimerFunc(120, atualizar, 0); // Define a função de atualização para ser chamada

    srand((unsigned int)time(NULL)); // Inicializa a semente para a geração de números aleatórios

    gerarMaca(); // Gera a posição inicial da maçã

    glutMainLoop(); // Inicia o loop principal do GLUT, que aguarda eventos e chama as funções de callback apropriadas

    return 0;
}

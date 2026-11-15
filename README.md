# Projetos em C

Portfólio de projetos e exercícios desenvolvidos durante meus estudos de Engenharia de Computação. Reúne aplicações em **C**, um protótipo com **Arduino/C++** e um jogo com interface gráfica usando **OpenGL/FreeGLUT**, explorando lógica de programação, estruturas, matrizes, modularização e sistemas embarcados.

## Projetos

| Projeto | Descrição | Tecnologias e conceitos |
| --- | --- | --- |
| **[Snake — Jogo da Cobra](./Snake/)** | Jogo gráfico com movimentação automática, maçãs, pontuação, colisões, pausa, reinício e aceleração progressiva. | C, FreeGLUT/OpenGL, `struct`, ponteiros, módulos e callbacks |
| **[Super Trunfo de Cidades](./Super-Trunfo-Cidades/)** | Cadastro e comparação de indicadores de duas cidades, com validação de entradas e tratamento de empates. | C, `struct`, funções e operações numéricas |
| **[Tabuleiro Naval](./Tabuleiro-Naval/)** | Simulador de posicionamento de navios e ataques especiais em um tabuleiro 10 × 10. | C, matrizes, máscaras e validação |
| **[Movimentação de Xadrez](./Xadrez-Movimentacao/)** | Simulação textual de movimentos de peças de xadrez. | C, recursão, laços e validação |
| **[Exaustor Inteligente](./Exaustor-Inteligente-Arduino/)** | Protótipo de controle de ventoinha por temperatura ou ajuste manual, com informações em LCD. | Arduino/C++, TMP36, PWM, Timer1 e I2C |

## Organização

Cada projeto fica em sua própria pasta. Os arquivos-fonte, instruções e limitações específicas devem ser consultados nas respectivas pastas.

## Compilação e execução

### Exercícios de terminal em C

Entre na pasta do exercício e compile com GCC:

```bash
gcc -std=c11 -Wall -Wextra nome_do_arquivo.c -o programa
./programa
```

No Windows, gere `programa.exe` e execute-o. Para o **Super Trunfo**, acrescente `-lm` ao comando de compilação.

### Snake — C com FreeGLUT

O Snake utiliza **OpenGL e FreeGLUT** e exige que os cabeçalhos e as bibliotecas estejam configurados no compilador. Na pasta `Snake/`, em um ambiente Windows com GCC e FreeGLUT disponíveis:

```powershell
gcc -std=c99 -Wall main.c cobra.c -o Snake.exe -lfreeglut -lopengl32 -lglu32
.\Snake.exe
```

**Controles:** setas para direcionar a cobra, **P** para pausar/continuar, **ESC** para sair e **clique esquerdo** para reiniciar após o fim da partida.

### Exaustor Inteligente — Arduino

Abra o arquivo `ExaustorInteligente.ino` na Arduino IDE e consulte o [README do projeto](./Exaustor-Inteligente-Arduino/README.md) para montagem, componentes e configuração.

## Testes

O script [`tests/testes.sh`](./tests/testes.sh) compila e executa cenários básicos dos três exercícios em C de terminal (Super Trunfo, Tabuleiro Naval e Movimentação de Xadrez), em Linux ou WSL:

```bash
bash tests/testes.sh
```

O Snake e o protótipo Arduino não fazem parte desse script.

## Sobre

Os projetos têm finalidade educacional e variam de exercícios de lógica a aplicações gráficas e protótipos embarcados. Funcionalidades e limitações específicas estão descritas na documentação de cada projeto, quando disponível.

**Autor:** Edson Costa das Neves — Engenharia de Computação.

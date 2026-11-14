# Projetos em C

Portfólio de exercícios e protótipos desenvolvidos durante meus estudos de Engenharia de Computação, com foco em programação C, estruturas de dados, lógica, matrizes e sistemas embarcados.

## Projetos

| Projeto | Tecnologias e conceitos | Código e documentação |
| --- | --- | --- |
| **Super Trunfo de Cidades** | C, structs, indicadores e comparação de cartas | [Abrir projeto](./Super-Trunfo-Cidades/) |
| **Tabuleiro Naval** | C, matrizes 10×10, posicionamento de navios e ataques | [Abrir projeto](./Tabuleiro-Naval/) |
| **Movimentação de Xadrez** | C, recursão, laços e validação de movimentos | [Abrir projeto](./Xadrez-Movimentacao/) |
| **Exaustor Inteligente** | Arduino/C++, sensor TMP36, PWM, Timer1 e LCD I2C | [Abrir projeto](./Exaustor-Inteligente-Arduino/) |

## Organização

Cada projeto fica em **sua própria pasta**, com um código-fonte e um `README.md` que explica funcionalidades, montagem/execução e limitações. As cópias antigas dos três exercícios da raiz foram removidas para evitar divergências entre arquivos.

## Executando exercícios em C

Entre na pasta do projeto e use GCC:

```bash
gcc -std=c11 -Wall -Wextra nome_do_arquivo.c -o programa
./programa
```

Para o Super Trunfo, adicione `-lm` ao comando de compilação. No Windows, gere `programa.exe` e execute esse arquivo.

## Testes

O script [`tests/testes.sh`](./tests/testes.sh) compila os três projetos e executa cenários básicos de entrada, validação e saída. Em Linux ou WSL:

```bash
bash tests/testes.sh
```

## Sobre os projetos

Os exercícios em C são **demonstrações de programação**, não jogos completos. Os READMEs individuais descrevem as regras simplificadas e as limitações restantes.

**Autor:** Edson Costa das Neves — Engenharia de Computação.

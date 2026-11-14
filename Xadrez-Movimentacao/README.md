# Movimentação de Peças de Xadrez em C

Exercício de programação em C que **imprime movimentos textuais** de peças de xadrez no terminal. Pratica recursão, `switch`, condicionais e laços; **não implementa um tabuleiro nem as regras completas do xadrez**.

## Funcionalidades implementadas

- Menu para selecionar **bispo, torre, rainha ou cavalo**.
- O bispo, a torre e a rainha imprimem um passo por chamada de função recursiva, conforme direção e número de casas selecionados.
- Limites definidos no código: bispo até cinco casas, torre até cinco e rainha até oito.
- O cavalo usa laços para imprimir um percurso em “L”, com duas etapas verticais e uma horizontal, dentre quatro direções oferecidas.

## Como compilar e executar

```bash
gcc -std=c11 -Wall -Wextra xadrez.c -o xadrez
./xadrez
```

No Windows, use `-o xadrez.exe` e execute o programa. Escolha uma peça no menu, informe o número de casas solicitado e depois a direção que o programa apresenta.

## Conceitos praticados

Funções recursivas e condição de parada; `switch/case`; `for` aninhado; validação parcial de intervalo; menu e entrada pelo terminal.

## Limitações conhecidas e melhorias recomendadas

- **Erro lógico no cavalo:** `else if (i = cavalo_move)` faz **atribuição**, não comparação, e força `i` a 3; deveria avaliar `i == cavalo_move` se essa for a regra pretendida.
- A condição `if (i < 0 && i <= 2)` aceita valores negativos, em vez de verificar o intervalo positivo pretendido.
- O movimento do cavalo oferece apenas quatro das oito possibilidades de deslocamento em “L”.
- As funções recursivas imprimem “direção inválida” várias vezes quando `direcao` está fora das opções, em vez de rejeitá-la antes de iniciar.
- As funções não rastreiam coordenadas, capturas, peças bloqueadoras ou limites do tabuleiro.
- Entradas `scanf` não são verificadas e não existe repetição do menu.

**Status:** exercício de lógica de programação; código-fonte preservado sem correções nesta revisão documental.

# Movimentação de Peças de Xadrez em C

Exercício em C que simula **movimentos textuais** de bispo, torre, rainha e cavalo. Seu foco é praticar funções recursivas, laços, menus e validação de entradas. **Não é um motor de xadrez nem um jogo completo.**

## Funcionalidades

- **Bispo:** imprime de 1 a 5 passos na direção diagonal escolhida (4 possibilidades).
- **Torre:** imprime de 1 a 5 passos na direção horizontal ou vertical (4 possibilidades).
- **Rainha:** imprime de 1 a 8 passos em uma das 8 direções.
- **Cavalo:** imprime uma representação de movimento em “L” para **qualquer uma das 8 orientações** (duas casas em um eixo e uma no outro).
- Todas as opções numéricas possuem verificação de faixa e rejeitam texto inválido.

Os passos do cavalo são uma **representação didática de deslocamento**; na partida real, o cavalo salta e não percorre fisicamente cada casa intermediária.

## Como compilar e executar

\`\`\`bash
gcc -std=c11 -Wall -Wextra xadrez.c -o xadrez
./xadrez
\`\`\`

No Windows, utilize \`-o xadrez.exe\` e execute o arquivo.

## Como usar

1. Escolha a peça pelo número \`1\` (bispo), \`2\` (torre), \`3\` (rainha) ou \`4\` (cavalo).
2. Para bispo, torre ou rainha, escolha de 1 até o limite de casas exibido e a direção.
3. Para o cavalo, escolha diretamente uma das **8 orientações possíveis**. O deslocamento em “L” tem três unidades de movimento representadas em texto.

## Conceitos praticados

- Recursão com condição de parada, para bispo, torre e rainha.
- Laços \`for\` para representar a movimentação do cavalo.
- Arrays de strings, seleção por \`if\` e validação de menus.
- Leitura segura de inteiros com \`fgets\` e \`strtol\`.

## Limitações

- Não há tabuleiro, coordenadas de origem e destino, colisões, capturas, xeque ou xeque-mate.
- O limite de casas de bispo/torre/rainha é **uma escolha do exercício**, não uma validação do movimento real a partir de uma posição do tabuleiro.
- Cada execução simula uma peça e termina; não mantém uma partida.

**Status:** versão corrigida, incluindo as oito orientações do cavalo e remoção das condições defeituosas de comparação/atribuição.

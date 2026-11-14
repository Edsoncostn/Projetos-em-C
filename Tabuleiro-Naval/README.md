# Tabuleiro Naval — Matrizes e habilidades em C

Simulador didático em terminal com tabuleiro **10 × 10**, dois navios e ataques especiais com formas geométricas. O código foi revisado para identificar cada navio e não apagar o navio que **não** foi atingido.

## Funcionalidades

- Dois navios de **três células**, posicionados pelo usuário.
- Direções válidas: \`0\` horizontal; \`1\` vertical; \`2\` diagonal ascendente; \`3\` diagonal descendente.
- Validação de coordenadas, direção, sobreposição e limites do tabuleiro.
- Dois ataques pseudoaleatórios com máscaras 5 × 5: **cone, cruz ou losango**.
- Se o ataque atingir uma célula de um navio, **somente aquele navio** é marcado como destruído.
- Exibição do tabuleiro e legenda após o posicionamento e cada habilidade.

## Legenda

| Valor | Significado |
| --- | --- |
| 0 | Água |
| 3 | Navio ainda ativo |
| 5 | Área de habilidade sobre a água |
| 7 | Navio destruído |

## Compilação e execução

\`\`\`bash
gcc -std=c11 -Wall -Wextra tabuleiro_naval.c -o tabuleiro_naval
./tabuleiro_naval
\`\`\`

No Windows, compile com \`-o tabuleiro_naval.exe\` e execute o arquivo.

Você deve informar as coordenadas de **1 a 10** e uma direção de **0 a 3** para cada um dos dois navios. O programa rejeita valores inválidos e pede novas coordenadas.

Para reproduzir os mesmos ataques durante testes, passe uma semente:

\`\`\`bash
./tabuleiro_naval --seed 42
\`\`\`

Sem \`--seed\`, a semente é baseada no relógio.

## Conceitos praticados

Matrizes, funções, laços aninhados, limites de índices, controle de colisão, máscaras geométricas, \`rand()\` e validação de entradas com \`fgets\` e \`strtol\`.

## Limitações

- Trata-se de uma demonstração de **posicionamento e ataques especiais**, não de um jogo de dois jogadores.
- Não possui turnos, pontuação, escolha manual de alvo ou condição de vitória.
- O ataque pode ficar parcialmente fora do tabuleiro quando sorteado perto da borda.
- O acerto destrói **imediatamente todo o navio identificado**, por regra simplificada do exercício.
- O tabuleiro mostra a localização de todos os navios, inclusive antes dos ataques.

**Status:** versão corrigida, com ataques reprodutíveis via \`--seed\`.

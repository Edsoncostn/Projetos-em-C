# Tabuleiro Naval — Matrizes e ataques especiais em C

Simulação de batalha naval no terminal para praticar **matrizes bidimensionais**, vetores de deslocamento, funções e geração de números pseudoaleatórios. Não é um jogo completo de batalha naval com turnos de dois jogadores.

## Funcionalidades implementadas

- Cria uma matriz de **10 × 10** preenchida com água (valor 0).
- Solicita posicionamento de **dois navios de três células**, nas direções horizontal, vertical ou diagonais.
- Verifica se as células do navio ficariam fora do tabuleiro ou sobre outro navio.
- Gera **dois ataques aleatórios** com máscaras de **5 × 5** em formato de cone, cruz ou losango (chamado de “octaedro” no código).
- Mostra o tabuleiro numérico antes e depois das habilidades.

## Compilar e executar

```bash
gcc -std=c11 -Wall -Wextra tabuleiro_naval.c -o tabuleiro_naval
./tabuleiro_naval
```

No Windows, compile com `-o tabuleiro_naval.exe` e execute o arquivo. Informe linha e coluna de 1 a 10 e direção de 0 a 3 para **cada um dos dois navios**. As habilidades são sorteadas automaticamente após o posicionamento.

## Legenda do tabuleiro

| Valor | Significado |
| --- | --- |
| `0` | Água ou célula livre |
| `3` | Navio |
| `5` | Área atingida por habilidade, quando não havia navio |

## Conceitos praticados

Laços aninhados, arrays bidimensionais, funções que modificam matrizes, limites de índices, operador ternário, `rand()`, `srand()` e geração algorítmica de máscaras geométricas.

## Limitações conhecidas

- A direção fornecida não é validada explicitamente: um valor diferente de 0 a 3 pode gerar três células no mesmo ponto, tornando a colocação incorreta.
- `scanf` não tem verificação de sucesso. Entradas não numéricas podem causar comportamento imprevisível ou repetição do prompt.
- Se qualquer célula de navio for atingida, o programa **apaga todas as células de todos os navios** do tabuleiro; não há identificação individual nem controle de dano por navio.
- A origem aleatória pode ficar perto da borda e parte da máscara fica fora do tabuleiro, por decisão da lógica atual.
- Não existe sistema de pontuação, turnos, condição de vitória ou entrada manual de ataques.

**Status:** demonstração educacional. Código-fonte original mantido sem alterações nesta revisão documental.

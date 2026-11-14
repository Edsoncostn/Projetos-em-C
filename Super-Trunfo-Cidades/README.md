# Super Trunfo de Cidades (C)

Projeto educacional em **C** que cadastra duas cartas de cidades e compara indicadores por meio de um menu. Foi atualizado para validar entradas, evitar divisões por zero e tratar empates corretamente.

## O que o programa faz

- Cadastra duas cidades com **estado (A–H)**, código (ex.: `A01`), nome, população, área, PIB e pontos turísticos.
- Aceita nomes de cidades com espaços.
- Calcula PIB per capita, densidade demográfica e um índice didático chamado **Super Poder**.
- Permite comparar **dois atributos diferentes** (opções 1–7) ou **todos os sete atributos** (opção 8).
- Concede **1 ponto** à carta vencedora em cada atributo. Nos empates, **ambas recebem 1 ponto**.
- Na comparação de densidade demográfica, **vence o menor valor**.
- Informa o placar e a carta vencedora ou o empate geral.

## Compilação

Entre na pasta `Super-Trunfo-Cidades`:

```bash
gcc -std=c11 -Wall -Wextra super_trunfo_cidades.c -lm -o super_trunfo
./super_trunfo
```

No Windows, utilize `-o super_trunfo.exe` e execute `super_trunfo.exe`.

## Exemplo de cadastro

| Campo | Carta 1 | Carta 2 |
| --- | --- | --- |
| Estado | A | B |
| Código | A01 | B02 |
| Cidade | Rio de Janeiro | Sao Paulo |
| Habitantes | 1000 | 500 |
| Área (km²) | 10 | 20 |
| PIB | 2000 | 1000 |
| Pontos turísticos | 10 | 4 |

Depois do cadastro, escolha `8` para comparar todos os atributos. Também é possível escolher `1` e depois `2` para comparar somente habitantes e área.

## Conceitos de programação

`struct`, funções, operadores relacionais, `switch`, vetores de atributos, entrada com `fgets`, conversão numérica com `strtoul`/`strtod`, validação e tratamento de empates.

## Limites do exercício

- O **PIB per capita** usa a mesma unidade informada para o PIB; escolha a unidade de entrada de maneira consistente.
- O **Super Poder** soma grandezas de unidades e magnitudes diferentes; é um índice **fictício**, criado para o exercício.
- O exercício compara apenas duas cartas e não mantém um baralho persistente.
- Não há interface gráfica nem leitura de dados reais de municípios.

**Status:** versão corrigida; inclui tratamento de erro para entradas inválidas e fim inesperado da entrada.

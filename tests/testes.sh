#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="$(mktemp -d)"
trap 'rm -rf "$BUILD"' EXIT
cd "$ROOT"

echo "Compilando com avisos tratados como erros..."
gcc -std=c11 -Wall -Wextra -Werror -pedantic \
  Super-Trunfo-Cidades/super_trunfo_cidades.c -lm -o "$BUILD/super_trunfo"
gcc -std=c11 -Wall -Wextra -Werror -pedantic \
  Tabuleiro-Naval/tabuleiro_naval.c -o "$BUILD/tabuleiro_naval"
gcc -std=c11 -Wall -Wextra -Werror -pedantic \
  Xadrez-Movimentacao/xadrez.c -o "$BUILD/xadrez"

echo "Testando Super Trunfo (todas as comparacoes)..."
printf 'A\nA01\nRio de Janeiro\n1000\n10\n2000\n10\nB\nB02\nSao Paulo\n500\n20\n1000\n4\n8\n' \
  | "$BUILD/super_trunfo" > "$BUILD/super_todos.txt"
grep -Fq 'Rio de Janeiro (A01)' "$BUILD/super_todos.txt"
grep -Fq 'Placar final:' "$BUILD/super_todos.txt"
grep -Fq 'Vencedora: Rio de Janeiro' "$BUILD/super_todos.txt"

echo "Testando Super Trunfo (entradas invalidas e empate)..."
printf 'A\nA01\nRio de Janeiro\n1000\n10\n2000\n10\nB\nB02\nSao Paulo\n500\n20\n1000\n4\n9\n1\n1\n2\n' \
  | "$BUILD/super_trunfo" > "$BUILD/super_empate.txt"
grep -Fq 'Numero invalido' "$BUILD/super_empate.txt"
grep -Fq 'Escolha outro atributo' "$BUILD/super_empate.txt"
grep -Fq 'Resultado: empate entre as cartas.' "$BUILD/super_empate.txt"

echo "Testando Tabuleiro Naval (direcoes invalidas e sobreposicao)..."
printf '11\n1\n9\n1\n1\n0\n1\n1\n0\n2\n1\n0\n' \
  | "$BUILD/tabuleiro_naval" --seed 42 > "$BUILD/tabuleiro.txt"
grep -Fq 'Coordenada ou direcao fora dos limites' "$BUILD/tabuleiro.txt"
grep -Fq 'Navio fora do tabuleiro ou sobreposto' "$BUILD/tabuleiro.txt"
grep -Fq 'Tabuleiro inicial:' "$BUILD/tabuleiro.txt"
grep -Fq 'Ativando habilidade 2' "$BUILD/tabuleiro.txt"

echo "Testando Xadrez (recursao do bispo)..."
printf '1\n3\n2\n' | "$BUILD/xadrez" > "$BUILD/bispo.txt"
[ "$(grep -c 'O bispo se moveu na diagonal superior direita' "$BUILD/bispo.txt")" -eq 3 ]

echo "Testando Xadrez (todas as orientacoes do cavalo)..."
for direcao in 1 2 3 4 5 6 7 8; do
  printf '4\n%s\n' "$direcao" | "$BUILD/xadrez" > "$BUILD/cavalo.txt"
  [ "$(grep -c '^O cavalo se moveu ' "$BUILD/cavalo.txt")" -eq 3 ]
done

echo "Testando Xadrez (opcoes invalidas)..."
printf 'texto\n4\n9\n8\n' | "$BUILD/xadrez" > "$BUILD/xadrez_invalido.txt"
grep -Fq 'Entrada invalida' "$BUILD/xadrez_invalido.txt"

echo "Verificando se os arquivos da raiz foram removidos..."
for arquivo in super_trunfo_cidades.c tabuleiro_naval.c xadrez.c; do
  if [ -e "$ROOT/$arquivo" ]; then
    echo "ERRO: arquivo duplicado na raiz: $arquivo" >&2
    exit 1
  fi
done

echo "OK: os tres projetos passaram pelos testes automatizados."

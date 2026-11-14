# Super Trunfo de Cidades (C)

Projeto de terminal em C para cadastrar **duas cidades** como cartas e comparar características socioeconômicas. É um exercício de entrada e saída, operadores, expressões aritméticas, condições e `switch`.

## Funcionalidades implementadas

- Cadastro de duas cartas com estado, código, cidade, população, área, PIB e pontos turísticos.
- Cálculo de PIB per capita, densidade demográfica, inverso da densidade e um índice composto chamado **Super Poder**.
- Comparação por habitantes, área, PIB, pontos turísticos, PIB per capita, densidade demográfica (menor ganha) ou Super Poder.
- Opção de comparar todos os sete atributos, atribuindo um ponto a cada carta por atributo com valor maior (na densidade, menor); empates dão um ponto para ambas.
- Fluxo de escolha de dois atributos, com restrição a repetir o mesmo atributo.

## Como compilar e executar

Requer GCC ou compilador C compatível:

```bash
gcc -std=c11 -Wall -Wextra super_trunfo_cidades.c -o super_trunfo
./super_trunfo
```

No Windows, execute `super_trunfo.exe` após compilar com `-o super_trunfo.exe`.

**Entrada:** digite os valores solicitados no terminal. Use nomes de cidade sem espaços na versão atual (a leitura usa `scanf("%s", ...)`). Escolha a opção 8 no primeiro menu para ver a classificação por todos os atributos e encerrar.

## Conceitos praticados

Tipos de dados e formatação (`printf`/`scanf`), operadores relacionais, operador ternário, `switch`, cálculo de indicadores e agregação de pontuações.

## Limitações conhecidas e melhorias recomendadas

- **Problema grave na segunda escolha:** o código usa `scanf("%d", opcao2)` sem `&`, causando comportamento indefinido; **não escolha as opções 1–7 esperando um fluxo estável até que isso seja corrigido**.
- As entradas com `%s` não limitam o tamanho: nomes ou códigos longos podem exceder os vetores (`Codigo1[4]`, `Cidade1[50]`, etc.). Usar limites em `scanf` ou `fgets`.
- Não há verificação do retorno de `scanf`; população ou área igual a zero geram divisões inválidas.
- O PIB per capita depende da unidade escolhida para o PIB, e o “Super Poder” soma grandezas de unidades e escalas diferentes: é uma métrica **didática**, não um índice científico.
- Comparações individuais não tratam explicitamente empates e o fluxo de opção inválida pode deixar `resultado1` sem inicialização.
- Recomenda-se representar cada cidade por uma `struct`, extrair funções e criar testes para empates, limites e entradas inválidas.

**Status:** exercício acadêmico/protótipo de lógica. O código-fonte foi preservado sem correções nesta revisão documental.

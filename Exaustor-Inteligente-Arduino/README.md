# Exaustor de solda inteligente — Arduino Uno

Protótipo acadêmico desenvolvido em 2026 nas disciplinas de microprocessadores/microcontroladores do curso de Engenharia de Computação. O objetivo é controlar uma ventoinha de exaustão de bancada por temperatura ou por ajuste manual, com indicação do estado em um display LCD I2C.

## Funcionalidades

- **Modo automático:** lê o sensor analógico TMP36 e ajusta o PWM da ventoinha de acordo com a temperatura.
  - Até **25 °C**: motor desligado.
  - De **25 °C a 45 °C**: PWM cresce de forma aproximadamente linear, com faixa útil mapeada de 80 a 255.
  - A partir de **45 °C**: PWM máximo (255).
- **Modo manual:** potenciômetro em A0 define o PWM de 0 a 255; valores inferiores a 40 são tratados como desligado.
- **Botão:** alterna os modos manual e automático, com debounce de 50 ms.
- **Display LCD 16×2 por I2C:** mostra modo, temperatura e percentual do comando PWM.
- **Redução do ruído audível:** ajuste do prescaler do Timer1 para usar frequência de PWM mais alta no pino 9.
- **Leitura periódica:** sensores a cada ~100 ms e display a cada ~250 ms, exceto durante a mensagem de transição.

## Tecnologias e conceitos

Arduino Uno • Arduino/C++ • PWM • registradores AVR/Timer1 • conversão analógico-digital (ADC) • TMP36 • LCD I2C • debounce • temporização com \`millis()\` • prototipagem de circuitos.

## Componentes e pinos

| Componente | Conexão no Arduino Uno |
| --- | --- |
| Potenciômetro | A0 |
| Sensor de temperatura TMP36 | A1 |
| Controle da ventoinha (via estágio de acionamento) | D9 (PWM) |
| Botão de alternância | D4 (INPUT_PULLUP; fechamento para GND) |
| LCD I2C 16×2 | Barramento I2C (endereço 0x27; SDA=A4, SCL=A5 no Uno) |

O protótipo utilizou um estágio de acionamento com transistor e diodo de proteção, conforme o relatório do projeto. **Não ligue o motor diretamente ao pino do Arduino**; dimensione a alimentação, o transistor e o diodo conforme a ventoinha.

## Como executar

1. Abra o arquivo [\`ExaustorInteligente.ino\`](./ExaustorInteligente.ino) na Arduino IDE.
2. Selecione uma placa compatível com **Arduino Uno/AVR**.
3. Instale uma biblioteca compatível com \`LiquidCrystal_I2C.h\` e \`Wire.h\` (esta última normalmente acompanha o core).
4. Monte o circuito conforme o pinout, alimente corretamente a ventoinha e faça o upload para a placa.
5. Use o botão para trocar entre os modos.

## Demonstração

- [Vídeo: circuito completo funcionando](https://www.youtube.com/watch?v=1TZtzD2cx58)
- [Vídeo: teste do LCD durante a montagem](https://www.youtube.com/watch?v=Vv3z08aIQFU)
- [Vídeo: ruído antes do ajuste do prescaler](https://youtube.com/shorts/SOv-13Jtwnw)

## Detalhes técnicos e limitações

- O valor de **VELOCIDADE (%)** é uma estimativa da intensidade de comando PWM (*duty cycle*), **não** uma leitura real de RPM. Não há tacômetro no código.
- A conversão do TMP36 presume referência analógica de **5,0 V**; diferenças na tensão de referência podem afetar a precisão.
- A leitura de dez amostras por sensor faz uma **média** para atenuar ruídos, mas não garante maior resolução do ADC.
- A tela de transição é temporizada com \`millis()\`, porém o \`return\` usado nela suspende temporariamente a atualização do PWM e dos sensores durante até 2 segundos.
- A alteração de \`TCCR1B\` depende do hardware AVR e afeta o comportamento do Timer1. O código não foi validado aqui por compilação ou testes físicos.
- **Atenção:** este é um protótipo didático, não um equipamento de proteção respiratória certificado. Uma ventoinha sem captura, filtragem e exaustão adequadas não garante proteção contra fumos de solda.

## Contexto

Projeto acadêmico de Engenharia de Computação realizado entre abril e junho de 2026. O desenvolvimento incluiu prototipagem, montagem e programação, com diagnóstico de ruído do motor e integração de entrada analógica, controle PWM e interface em LCD.

**Autor:** Edson Costa das Neves.